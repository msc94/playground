import logging

import mydealz_html_scraper
import mydealz_page_downloader
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
        if articles is None:
            return {"index": [],
                    "look_for": []}

        index_articles = self._filter_articles(
            articles=articles,
            temp=self._config.value("index_page.send_on_temp"),
            send_only_active=self._config.value("index_page.send_only_active"),
            keywords=None
        )

        look_for_articles = self._filter_articles(
            articles=articles,
            temp=self._config.value("look_for.send_on_temp"),
            send_only_active=self._config.value("look_for.send_only_active"),
            keywords=self._config.value("look_for.keywords")
        )

        return {"index": index_articles,
                "look_for": look_for_articles}

    def filter_group_articles(self, groups):
        filtered_groups = []

        for group in groups:
            filtered_articles = self._filter_articles(
                articles=group.articles,
                temp=self._config.value("groups.send_on_temp"),
                send_only_active=self._config.value("groups.send_only_active"),
                keywords=None
            )

            filtered_group = mydealz_article.GroupArticles()
            filtered_group.group_name = group.group_name
            filtered_group.articles = filtered_articles
            filtered_groups.append(filtered_group)

        return filtered_groups

    def _filter_articles(self, articles, temp, send_only_active, keywords):
        articles = filter(lambda x: x.temp > temp, articles)

        # Filter inactive
        if send_only_active:
            articles = filter(lambda x: x.state ==
                              mydealz_article.ArticleState.ACTIVE, articles)

        # Filter already sent articles
        if self._thread_db is not None:
            articles = filter(
                lambda x: not self._thread_db.has_article(x.id), articles)

        # Filter on keywords
        if keywords is not None:
            articles = filter(lambda x: _string_contains_any_keyword(
                x.title, keywords), articles)

        return list(articles)


class MydealzScraperMain(object):
    def __init__(self, config):
        self._config = config
        self._page_downloader = mydealz_page_downloader.MydealzPageDownloader()

    async def scrape_index(self):
        articles = []
        num_pages = self._config.value("index_page.scrap_num_pages")
        logging.info(f"Scraping first {num_pages} of mydealz")
        for i in range(1, num_pages + 1):
            page_html = await self._page_downloader.mydealz_index(i)
            page_articles = mydealz_html_scraper.MydealzHtmlScraper(page_html).get_articles()
            articles.extend(page_articles)
        return articles

    async def scrape_groups(self):
        groups = []

        for group in self._config.value("groups.names"):
            group_articles = mydealz_article.GroupArticles()
            group_articles.group_name = group
            group_articles.articles = await self._scrape_group(group)
            groups.append(group_articles)

        return groups

    async def _scrape_group(self, name):
        num_pages = self._config.value("groups.scrape_num_pages")
        articles = []
        for i in range(1, num_pages + 1):
            page_html = await self._page_downloader.mydealz_group(name, i)
            page_articles = mydealz_html_scraper.MydealzHtmlScraper(page_html).get_articles()
            articles.extend(page_articles)
        return articles


class MydealzMessage(object):
    def add_index(self, index):
        self._index = index

    def add_look_for(self, look_for):
        self._look_for = look_for

    def add_groups(self, groups):
        self._groups = groups

    def send_message(self):
        messages = self._create_messages()
        telegrambot = telegram_bot.TelegramBot()
        for msg in messages:
            telegrambot.send_html(msg)

    def _create_messages(self):
        messages = []

        if self._index is not None and len(self._index) > 0:
            logging.info("There is main page data. Adding to message")

            str_list = []
            str_list.append(f"-------------------------------------")
            str_list.append("Ergebnisse Hauptseite:")
            str_list.append(f"-------------------------------------")
            for a in self._index:
                str_list.append(a.to_html())

            messages.append(
                "\r\n".join(str_list[0:20])
            )

        if self._groups is not None:
            logging.info("There is group data. Adding to message")

            for g in self._groups:
                if len(g.articles) == 0:
                    continue

                str_list = []
                str_list.append(f"-------------------------------------")
                str_list.append(f"Gruppe {g.group_name}:")
                str_list.append(f"-------------------------------------")
                for a in g.articles:
                    str_list.append(a.to_html())
                messages.append(
                    "\r\n".join(str_list[0:20])
                )



        if self._look_for is not None and len(self._look_for) > 0:
            logging.info("There is look for data. Adding to message")

            str_list = []
            str_list.append(f"-------------------------------------")
            str_list.append("Gesuchte Ergebnisse:")
            str_list.append(f"-------------------------------------")
            for a in self._look_for:
                str_list.append(a.to_html())

            messages.append(
                "\r\n".join(str_list[0:20])
            )

        return messages
