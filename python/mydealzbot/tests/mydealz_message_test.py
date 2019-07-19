import unittest

from mydealz_article import Article, ArticleState
from telegram_bot import TelegramBot

class MydealzMessageTest(unittest.TestCase):
    def _create_article(self, title, temp, price, state):
        a = Article()
        a.title = title
        a.temp = temp
        a.price = price
        a.state = state
        return a


    def _create_test_data(self):
        return [
            self._create_article("Article one", 500, "12,99", ArticleState.ACTIVE),
            self._create_article("Article two", 500, "12,99", ArticleState.ACTIVE),
            self._create_article("Article three", 500, "12,99", ArticleState.INACTIVE),
            self._create_article("Article four", 500, "12,99", ArticleState.ACTIVE),
            self._create_article("Article five", 500, "12,99", ArticleState.ACTIVE),
            self._create_article("Article six", 500, "12,99", ArticleState.ACTIVE),
        ]

    def test_article_to_markdown(self):
        articles = self._create_test_data()    
        markdown = articles[0].to_html()
        self.assertTrue(len(markdown) > 0)

    def test_send_article(self):
        articles = self._create_test_data()    
        html = articles[0].to_html()
        tb = TelegramBot()
        tb.send_html(html)

if __name__ == "__main__":
    unittest.main()