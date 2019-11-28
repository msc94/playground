using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.Graph;
using NLog;

namespace onedrive
{
    public class OnedriveItem
    {
        private static readonly NLog.Logger _logger = NLog.LogManager.GetCurrentClassLogger();

        private GraphServiceClient _graphServiceClient = null;
        private List<OnedriveItem> _children = new List<OnedriveItem>();
        private string _id = "";
        private bool _isFolder = false;
        private string _name = "";

        public OnedriveItem(GraphServiceClient graphServiceClient) {
            _graphServiceClient = graphServiceClient;
        }

        public async Task PopulateRoot() {
            var root = await _graphServiceClient.Me.Drive.Root.Request().GetAsync();
            PopulateData(root);
        }

        public void PopulateData(DriveItem item) {
            _id = item.Id;
            _isFolder = (item.Folder != null);
            _name = item.Name;
        }

        public async Task PopulateChildren() {
            if (string.IsNullOrEmpty(_id)) {
                throw new ArgumentException($"{nameof(_id)} not set.");
            }

            if (!_isFolder) {
                _logger.Debug("{0} is no folder", _name);
                return;
            }

            _logger.Debug("Populating {0}", _name);

            var children = await _graphServiceClient.Me.Drive.Items[_id].Children.Request().GetAsync();
            foreach (var child in children) {
                var onedriveChild = new OnedriveItem(_graphServiceClient);
                onedriveChild.PopulateData(child);
                await onedriveChild.PopulateChildren();
                _children.Add(onedriveChild);
            }
        }
    }
}