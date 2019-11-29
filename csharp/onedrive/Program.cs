using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.Graph;
using Microsoft.Graph.Auth;
using Microsoft.Identity.Client;
using NLog.Config;
using NLog.Targets;

namespace onedrive
{
    class Program
    {
        public static async Task Main(string[] args) {
            var config = new LoggingConfiguration();
            var consoleTarget = new ColoredConsoleTarget("target")
            {
                Layout = @"${date:format=HH\:mm\:ss} ${level} ${callsite} - ${message} ${exception}"
            };
            config.AddTarget(consoleTarget);
            config.AddRuleForAllLevels(consoleTarget);
            NLog.LogManager.Configuration = config;

            var clientId = "4ecd4a8e-a3b9-47be-a27e-3f1717b07180";
            IPublicClientApplication publicClientApplication = PublicClientApplicationBuilder
                .Create(clientId)
                .WithRedirectUri("http://localhost")
                .Build();

            var scope = new List<string>() { "Files.Read.All" };
            await publicClientApplication
                .AcquireTokenInteractive(scope)
                .WithPrompt(Microsoft.Identity.Client.Prompt.NoPrompt)
                .ExecuteAsync();

            var authenticationProvider = new InteractiveAuthenticationProvider(publicClientApplication);
            var graphServiceClient = new GraphServiceClient(authenticationProvider);
            var apiClient = new OnedriveApiClient(graphServiceClient);

            var root = await apiClient.GetOnedriveRoot();
            var downloader = new OnedriveDownloader(apiClient);
            await downloader.DownloadItemRecursive(root, "/home/marcel/Onedrive");
        }
    }
}