import logging

class MydealzMessageData():
    pass

class MydealzMessage():
    def __init__(self, data):
        self._data = data

    def craft_message(self):
        str_list = []
        main_page_articles = self._data.main_page_articles
        if  main_page_articles is not None:
            logging.info("MessageData has main page data. Adding to message")
            str_list.append("Main page results")
            str_list.append("----------------------------------------------")
            for a in main_page_articles:
                str_list.append(str(a))
        return "\r\n".join(str_list)