import unittest
import re
import logging
import sys

from mydealz_html_scraper import MydealzHtmlScraper

class MydealzScraperTest(unittest.TestCase):
    def test_extract_articles(self):
        html = open("test_data/main.html", encoding="utf-8").read()
        scraper = MydealzHtmlScraper(html)
        articles = scraper.get_articles()
        self.assertTrue(len(articles) == 20)

    def test_temp_regular_expression(self):
        regex = "^[-]?[0-9]+°$"
        string = "765°"
        self.assertTrue(re.match(regex, string))

if __name__ == "__main__":
    unittest.main()