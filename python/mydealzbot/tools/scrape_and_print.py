import time
import logging
import sys
import asyncio

import mydealz_config
import mydealz_main

async def main():
    start = time.time()
    logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)

    config = mydealz_config.Config("data/mydealz_conf.json")
    scrape_main = mydealz_main.MydealzScraperMain(config)
    articles_index = await scrape_main.scrape_index()
    group_articles = await scrape_main.scrape_groups()

    print(f"{articles_index}\r\n{group_articles}")
    print(f"Took {time.time() - start} seconds")

if __name__ == "__main__":
    asyncio.run(main())