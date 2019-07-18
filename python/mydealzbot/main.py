import logging
import sys

import config
import mydealz_page_scraper as pagescraper
from mydealz_article import Article, ArticleState
from mydealz_thread_db import MydealzThreadDatabase
from mydealz_message import MydealzMessage, MydealzMessageData

from telegram_bot import TelegramBot

def scrape_main_pages(conf, thread_db=None):
    num_pages = conf.value("main_page.scrap_num_pages")
    logging.info(f"Scraping first {num_pages} of mydealz")
    articles = pagescraper.scrape_first_mydealz_pages(num_pages)

    # Filter on temp
    articles = [a for a in articles if a.temp > conf.value("main_page.send_on_temp")]

    # Filter inactive
    if not conf.value("send_inactive"):
        articles = [a for a in articles if a.status == ArticleState.ACTIVE]

    # Filter already sent articles
    if thread_db is not None:
        articles = [a for a in articles if not thread_db.has_article(a.id)]

    return articles


def main():
    logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)

    conf = config.Config("data/mydealz_conf.json")
    use_db = conf.value("use_db")
    thread_db = MydealzThreadDatabase() if use_db else None

    data = MydealzMessageData()
    data.main_page_articles = scrape_main_pages(conf, thread_db)

    msg = MydealzMessage(data)
    msgtext = msg.craft_message()
    print(msgtext)

    if use_db:
        thread_db.insert_articles([a.id for a in data.main_page_articles])

    telegrambot = TelegramBot()
    telegrambot.send_message(msgtext)

if __name__ == "__main__":
    main()
