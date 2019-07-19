import logging

import mydealz_page_scraper
import mydealz_article
import mydealz_thread_db
import telegram_bot

class MydealzScraperResult(object):
    def __init__(self):
        pass
    
def _string_contains_any_keyword(string, keywords):
    lower_string = string.lower()

    for w in keywords:
        lower_w = w.lower()
        if lower_w in lower_string:
            return True

    return False

class MydealzFilterMain(object):
    def __init__(self, config, thread_db):
        self._config = config
        self._thread_db = thread_db

    def filter_index_articles(self, articles):
        index_articles = self._filter_articles(
            articles=articles,
            temp=self._config.value("index_page.send_on_temp"),
            send_only_active=self._config.value("send_only_active"),
            keywords=None
        )

        look_for_articles = self._filter_articles(
            articles=articles,
            temp=self._config.value("look_for.send_on_temp"),
            send_only_active=self._config.value("send_only_active"),
            keywords=self._config.value("look_for.articles")
        )
        
        return {"index": list(index_articles), 
            "look_for": list(look_for_articles)}

    def _filter_articles(self, articles, temp, send_only_active, keywords):
        articles = filter(lambda x: x.temp > temp, articles)

        # Filter inactive
        if send_only_active:
            articles = filter(lambda x: x.status ==
                              mydealz_article.ArticleState.ACTIVE, articles)

        # Filter already sent articles
        if self._thread_db is not None:
            articles = filter(
                lambda x: not self._thread_db.has_article(x.id), articles)

        # Filter on keywords
        if keywords is not None:
            articles = filter(lambda x: _string_contains_any_keyword(
                x.title, keywords), articles)

        return articles


class MydealzScraperMain(object):
    def __init__(self, config):
        self._config = config

    def scrape_index(self):
        num_pages = self._config.value("index_page.scrap_num_pages")
        logging.info(f"Scraping first {num_pages} of mydealz")
        return mydealz_page_scraper.scrape_first_mydealz_pages(num_pages)

    def scrape_groups(self):
        pass


class MydealzMessage(object):
    def add_index(self, index):
        self._index = index

    def add_look_for(self, groups):
        self._groups = groups

    def send_message(self):
        msgtext = self._create_message()
        print(msgtext)
        telegrambot = telegram_bot.TelegramBot()
        telegrambot.send_html(msgtext)

    def _create_message(self):
        str_list = []

        if self._index is not None:
            logging.info("MessageData has main page data. Adding to message")

            str_list.append("<i>Main page results</i>")
            for a in self._index:
                str_list.append(a.to_html())
                # Safety measure...
                if len(str_list) > 30:
                    break

        return "\r\n".join(str_list)