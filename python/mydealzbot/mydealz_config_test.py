import unittest

from mydealz_config import MydealzConfig

class MydealzScraperTest(unittest.TestCase):
    def test_extract_value(self):
        conf = MydealzConfig()
        self.assertEqual(conf.value("main_page.scrap_num_pages"), 5)

if __name__ == "__main__":
    unittest.main()