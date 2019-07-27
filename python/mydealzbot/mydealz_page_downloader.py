import aiohttp
import requests
import asyncio
import logging
import sys

class MydealzPageDownloader(object):
    def __init__(self):
        self._session = aiohttp.ClientSession()

    def _fetch(self, url):
        return requests.get(url).content.decode("utf-8")

    def mydealz_index(self, page_num):
        return self._fetch(f"https://www.mydealz.de/?page={page_num}")

    def mydealz_group(self, group, page_num):
        return self._fetch(f"https://www.mydealz.de/gruppe/{group}?page={page_num}")

def main():
    logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)

    downloader = MydealzPageDownloader()
    for i in range(1, 6):
        html = downloader.mydealz_index(i)
        print(html)

if __name__ == "__main__":
    main()