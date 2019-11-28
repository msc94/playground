import aiohttp
import asyncio
import logging
import sys
import time

class MydealzPageDownloader(object):
    def __init__(self):
        self._session = aiohttp.ClientSession()
        self._total_time = 0.0

    async def _fetch(self, url):
        start = time.time()
        async with self._session.get(url) as response:
            result = await response.text()

            request_time = (time.time() - start)
            self._total_time += request_time
            logging.debug(f"It took {request_time} to get {url}. Total time up to now: {self._total_time}")
            
            return result

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