from enum import Enum

class ArticleState(Enum):
    INACTIVE = 0,
    ACTIVE = 1

    def __str__(self):
        return f"{self.name}"

class Article():
    def __repr__(self):
        return f"{self.id} {self.title} {self.price} {self.temp}° [{self.state}]"