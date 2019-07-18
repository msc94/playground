import requests as re
import logging
import sys

from mydealz_html_scraper import MydealzHtmlScraper

def scrape_mydealz_main(page):
    url = f"https://www.mydealz.de/?page={page}"

    logging.debug(f"Downloading url {url}")
    html = re.get(url).content.decode("utf-8")

    scraper = MydealzHtmlScraper(html)
    return scraper.get_articles()

def scrape_first_mydealz_pages(num):
    articles = []
    for i in range(1, num + 1):
        articles.extend(scrape_mydealz_main(i))
    return articles

def scrape_group(name):
    url = f"https://www.mydealz.de/gruppe/{name}"

    logging.debug(f"Downloading url {url}")
    html = re.get(url).content.decode("utf-8")

    scraper = MydealzHtmlScraper(html)
    return scraper.get_articles()

if __name__ == "__main__":
    logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)

    logging.debug("Scraping a mydealz group")
    scrape_group("brillen")

    # logging.debug("Scraping the first five pages of mydealz main site")
    # for i in range(1, 6):
    #     scrape_mydealz_main(i)

