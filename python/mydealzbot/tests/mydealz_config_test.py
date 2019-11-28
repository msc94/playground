import unittest

from config import mydealz_config

class MydealzConfigTest(unittest.TestCase):
    def test_extract_values(self):
        conf = Config("data/mydealz_conf.json")
        self.assertEqual(conf.value("index_page.scrap_num_pages"), 5)

if __name__ == "__main__":
    unittest.main()