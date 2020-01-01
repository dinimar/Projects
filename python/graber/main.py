import os
import configparser
from utils import graber
from utils import parser

# Config setup
root = os.path.dirname(os.path.abspath(__file__))
config_file = "config.ini"
config = configparser.ConfigParser()
config.read(os.path.join(root, config_file))

# Site data
host = "https://studopedia.ru"
sect_links = [] # section links

if __name__ == '__main__':
    # Load main page, process sections
    page_html = graber.download_page(host)
    tree = parser.create_tree(page_html)
    sections = parser.extract_sections(tree, config['x_path']['sections'])
    # Extract section links
    x = lambda a : a.attrib.get('href')
    for sec in sections:
        sect_links.append(host+x(sec))

    pass