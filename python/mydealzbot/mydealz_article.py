from enum import Enum
import html

class ArticleState(Enum):
    INACTIVE = 0,
    ACTIVE = 1

    def __str__(self):
        return f"{self.name}"

class Article():
    def to_html(self):
        return f"<b>{self.temp}°</b> {html.escape(self.price)}\r\n\t{html.escape(self.title)}\r\n"

    def __repr__(self):
        return f"{self.id} {self.title} {self.price} {self.temp}° [{self.state}]"