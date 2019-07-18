import logging

import sqlite3 as sql

class MydealzThreadDatabase(object):
    def __init__(self):
        try:
            self._conn = sql.connect("data/articles.sqlite")
            self._ensure_table_exists()
        except sql.Error as e:
            logging.error("Failed connecting to sql database.")
            raise e

    def _ensure_table_exists(self):
        self._conn.execute(
            r"""
                CREATE TABLE IF NOT EXISTS article (
                    id TEXT PRIMARY KEY
                )
            """
        )

    def insert_articles(self, ids):
        for id in ids:
            self._conn.execute(
                r"""
                    INSERT INTO article(id) VALUES (?)
                """,
                (id,)
            )
        self._conn.commit()

    def has_article(self, id):
        return self._conn.execute(
            r"""
                SELECT COUNT(*) FROM article WHERE id = ?
            """,
            (id,)
        ).fetchone()[0] > 0