import logging
import json

class Config(object):
    def __init__(self, config):
        logging.debug("Loading config")
        with open(config) as f:
            self._json = json.load(f)

    def value(self, key):
        keys = key.split(".")
        j = self._json
        for key in keys:
            j = j[key]
        return j