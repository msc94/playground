import bs4
import re
import logging
import sys

from mydealz_article import Article, ArticleState

class MydealzHtmlScraper(object):
    def __init__(self, html):
        self._thread_id_re = re.compile("thread_([0-9]+)")
        self._bs = bs4.BeautifulSoup(html, "html.parser")

    def get_articles(self):
        articles = self._bs.find_all("article", id=self._thread_id_re)
        articles_parsed = [
            self._parse_article(a) for a in articles
        ]
        return articles_parsed

    def _parse_article(self, article):
        # Parse thread id
        id_match = self._thread_id_re.search(article.attrs["id"])

        # Parse data
        title_elements = article.find_all("a", class_="thread-title--list")
        temp_elements = article.find_all("span", text=re.compile("[-]?[0-9]+°"))
        price_elements = article.find_all("span", class_="thread-price")
        inactive_elements = article.find_all("span", text="Abgelaufen")

        # Create article
        article = Article()
        if id_match:
            article.id = id_match.group(1)
        else:
            raise RuntimeError("Erroring matching thread id regex")

        article.price = self._get_if_unique(price_elements, "?")

        if len(title_elements) == 1:
            article.title = self._strip_whitespace(title_elements[0].text)
            article.url = title_elements[0].attrs["href"]
        else:
            article.title = article.url = "?"

        temp = self._get_if_unique(temp_elements, "?")
        article.temp = 0 if temp == "?" else int(temp[:-1]) # Remove °

        article.state = ArticleState.INACTIVE if len(inactive_elements) == 1 else ArticleState.ACTIVE

        logging.debug(f"Parsed article: {article}")
        return article

    def _strip_whitespace(self, string):
        return string.replace("\t", "") \
            .replace("\n", "")

    def _get_if_unique(self, elements, not_unique_str):
        if len(elements) == 1:
            return self._strip_whitespace(elements[0].text)
        else:
            return not_unique_str