using System;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;
using NLog;

namespace onedrive
{
    public class OnedriveItem
    {
        private static readonly NLog.Logger _logger = NLog.LogManager.GetCurrentClassLogger();

        public string Id { get; } = "";
        public bool IsDirectory { get; } = false;
        public string Name { get; } = "";
        public string PathFromRoot { get; } = "";
        public DateTimeOffset? LastModifiedDateTime { get; } = null;

        public OnedriveItem(string id, bool isDirectory, string name, string pathFromRoot, DateTimeOffset? lastModifiedDateTime)
        {
            Id = id;
            IsDirectory = isDirectory;
            Name = name;
            PathFromRoot = pathFromRoot;
            LastModifiedDateTime = lastModifiedDateTime;
        }
        
        public override string ToString()
        {
            var type = "";

            if (IsDirectory)
            {
                type = "d";
            }
            else
            {
                type = "f";
            }

            return $"OnedriveItem: {Id} {type} {PathFromRoot}";
        }
    }
}