import unittest

import mydealz_main
import mydealz_config

import mydealz_article

class MydealzMainTest(unittest.TestCase):
    def _create_article(self, title, temp, price, state):
        a = mydealz_article.Article()
        a.title = title
        a.temp = temp
        a.price = price
        a.state = state
        return a


    def _create_test_data(self):
        return [
            self._create_article("Article one", 500, "12,99", "active"),
            self._create_article("Article two", 800, "12,99", "active"),

            self._create_article("Article mx518", 100, "12,99", "inactive"),
            self._create_article("mx518 four", 300, "12,99", "active"),
            self._create_article("MX518 four", 300, "12,99", "active"),
        ]

    def test_filter_main_articles(self):
        filter = mydealz_main.MydealzFilterMain(
            config=mydealz_config.Config("data/test_conf.json"),
            thread_db=None)
        filtered = filter.filter_index_articles(self._create_test_data())
        print(filtered)

if __name__ == "__main__":
    unittest.main()