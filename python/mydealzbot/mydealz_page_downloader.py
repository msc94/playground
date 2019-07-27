import aiohttp
import asyncio
import logging
import sys

class MydealzPageDownloader(object):
    def __init__(self):
        self._session = aiohttp.ClientSession()

    async def _fetch(self, url):
        async with self._session.get(url) as response:
            return await response.text()

    async def mydealz_index(self, page_num):
        return await self._fetch(f"https://www.mydealz.de/?page={page_num}")

    async def mydealz_group(self, group, page_num):
        return await self._fetch(f"https://www.mydealz.de/gruppe/{group}?page={page_num}")

async def main():
    logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)

    downloader = MydealzPageDownloader()
    for i in range(1, 6):
        html = await downloader.mydealz_index(i)
        print(html)

if __name__ == "__main__":
    asyncio.run(main())