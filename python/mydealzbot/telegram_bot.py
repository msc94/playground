import telegram

import mydealz_config

class TelegramBot(object):
    def __init__(self):
        conf = mydealz_config.Config("data/secrets_conf.json")
        self._bot = telegram.Bot(conf.value("secrets.bot_token"))
        self._chat_id = conf.value("secrets.chat_id")

    def send_message(self, msg):
        self._bot.send_message(chat_id=self._chat_id, text=msg)

    def send_html(self, msg):
        self._bot.send_message(chat_id=self._chat_id, text=msg, parse_mode="html")

if __name__ == "__main__":
    bot = TelegramBot()
    bot.send_message("Hallo!")