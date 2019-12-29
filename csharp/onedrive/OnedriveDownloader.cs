
using System;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;

namespace onedrive
{
    class OnedriveDownloader
    {
        private static readonly NLog.Logger _logger = NLog.LogManager.GetCurrentClassLogger();

        private readonly OnedriveApiClient _apiClient;

        public OnedriveDownloader(OnedriveApiClient apiClient)
        {
            this._apiClient = apiClient;
        }

        public async Task DownloadItem(OnedriveItem item, string rootPath)
        {
            if (item.IsDirectory)
            {
                return;
            }

            var filePath = Path.Combine(rootPath, item.PathFromRoot);
            if (File.Exists(filePath))
            {
                var localModifiedTime = File.GetLastWriteTimeUtc(filePath);
                var remoteModifiedTime = item.LastModifiedDateTime;
                _logger.Debug($"{item.ToString()}: {localModifiedTime} (local) {remoteModifiedTime} (remote)");
                if (localModifiedTime > remoteModifiedTime)
                {
                    _logger.Debug($"{item.ToString()}: Not downloading because local is newer");
                    return;
                }
            }

            _logger.Debug($"Downloading item {item.ToString()} to {filePath}");

            try
            {
                var stream = await _apiClient.GetFileStream(item);
                var path = Path.GetDirectoryName(filePath);
                Directory.CreateDirectory(path);
                using (var fileStream = File.Create(filePath))
                {
                    await stream.CopyToAsync(fileStream);
                }
            }
            catch (Exception e)
            {
                _logger.Error(e, $"Error downloading item {item.ToString()}");
            }
        }

        public async Task DownloadItemRecursive(OnedriveItem item, string rootPath)
        {
            if (!item.IsDirectory)
            {
                return;
            }

            _logger.Debug($"Downloading directory {item.ToString()}");

            var children = await _apiClient.GetOnedriveItemChildren(item);
            foreach (var child in children)
            {
                await DownloadItem(child, rootPath);
            }

            var tasks = new List<Task>();
            foreach (var child in children)
            {
                tasks.Add(
                    Task.Run(() => DownloadItemRecursive(child, rootPath))
                );
            }
            Task.WaitAll(tasks.ToArray());
        }
    }
}