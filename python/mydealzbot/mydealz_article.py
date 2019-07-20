from enum import Enum
import html

class ArticleState(Enum):
    INACTIVE = 0,
    ACTIVE = 1

    def __str__(self):
        return f"{self.name}"

class Article():
    def __init__(self):
        self.temp = ""
        self.price = ""
        self.title = ""
        self.id = ""
        self.url = ""
        self.state = ArticleState.INACTIVE

    def to_html(self):
        return f"<b>{self.temp}°</b> {html.escape(self.price)}\r\n<a href=\"{self.url}\">{html.escape(self.title)}</a>\r\n"

    def __repr__(self):
        return f"{self.id} {self.title} {self.price} {self.temp}° [{self.state}]"

class GroupArticles():
    def __init__(self):
        self.articles = []
        self.group_name = ""