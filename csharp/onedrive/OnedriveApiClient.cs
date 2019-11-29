using System;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;
using Microsoft.Graph;

namespace onedrive
{
    class OnedriveApiClient
    {
        private static readonly NLog.Logger _logger = NLog.LogManager.GetCurrentClassLogger();

        private GraphServiceClient _graphServiceClient = null;

        public OnedriveApiClient(GraphServiceClient graphServiceClient)
        {
            _graphServiceClient = graphServiceClient;
        }

        public async Task<OnedriveItem> GetOnedriveRoot()
        {
            var root = await _graphServiceClient.Me.Drive.Root.Request().GetAsync();

            var onedriveRoot = new OnedriveItem(
                root.Id,
                (root.Folder != null),
                root.Name,
                "",
                root.LastModifiedDateTime
            );

            _logger.Debug($"Onedrive root: {onedriveRoot.ToString()}");
            return onedriveRoot;
        }

        public async Task<Stream> GetFileStream(OnedriveItem item)
        {
            if (string.IsNullOrEmpty(item.Id))
            {
                throw new ArgumentException($"{nameof(item)} has no Id set.");
            }

            if (item.IsDirectory)
            {
                _logger.Debug($"{item} is a directory.");
            }

            return await _graphServiceClient.Me.Drive.Items[item.Id].Content.Request().GetAsync();

        }

        public async Task<IEnumerable<OnedriveItem>> GetOnedriveItemChildren(OnedriveItem item)
        {
            if (string.IsNullOrEmpty(item.Id))
            {
                throw new ArgumentException($"{nameof(item)} has no Id set.");
            }

            if (!item.IsDirectory)
            {
                _logger.Debug($"{item} is a directory.");
                return new List<OnedriveItem>();
            }

            _logger.Debug("Populating {0}", item.Name);

            var children = await _graphServiceClient.Me.Drive.Items[item.Id].Children.Request().GetAsync();
            var onedriveChildren = new List<OnedriveItem>();
            foreach (var child in children)
            {
                var pathFromRoot = Path.Combine(item.PathFromRoot, child.Name);
                var onedriveChild = new OnedriveItem(
                    child.Id,
                    (child.Folder != null),
                    child.Name,
                    pathFromRoot,
                    child.LastModifiedDateTime
                );
                onedriveChildren.Add(onedriveChild);
                _logger.Debug($"Populated child node: {onedriveChild.ToString()}");
            }
            return onedriveChildren;
        }
    }
}