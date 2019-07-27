import logging
import sys
import asyncio

import mydealz_config
import telegram_bot
import mydealz_thread_db
import mydealz_main

async def main():
    logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)

    config = mydealz_config.Config("data/mydealz_conf.json")
    thread_db = mydealz_thread_db.MydealzThreadDatabase() \
        if config.value("use_db") else None

    scrape_main = mydealz_main.MydealzScraperMain(config)
    articles_index = await scrape_main.scrape_index()
    group_articles = await scrape_main.scrape_groups()

    filter_main = mydealz_main.MydealzFilterMain(config, thread_db)
    filtered_index = filter_main.filter_index_articles(articles_index)
    filtered_groups = filter_main.filter_group_articles(group_articles)

    message = mydealz_main.MydealzMessage()
    message.add_index(filtered_index["index"])
    message.add_look_for(filtered_index["look_for"])
    message.add_groups(filtered_groups)
    message.send_message()

    if thread_db is not None:
        sent_articles = filtered_index["index"] + filtered_index["look_for"]
        for g in filtered_groups:
            sent_articles.extend(g.articles)
        id_set = set([a.id for a in sent_articles])
        thread_db.insert_articles(id_set)

if __name__ == "__main__":
    asyncio.run(main())
