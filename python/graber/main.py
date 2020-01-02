import os
import configparser
from utils import graber
from utils import parser

# Config setup
root = os.path.dirname(os.path.abspath(__file__))
config_file = "config.ini"
config = configparser.ConfigParser()
config.read(os.path.join(root, config_file))

# DB
# db_dir = '/link_db'
# art_db = db_dir+'/articles.txt'
# link_db = db_dir+'/links.txt'

# Site data
host = "https://studopedia.ru"
lect_links = [] # lection links
arti_links = [] # article links


# def stringify_children(node):
#     from lxml.etree import tostring
#     from itertools import chain
#     parts = ([node.text] +
#             list(chain(*([c.text, tostring(c), c.tail] for c in node.getchildren()))) +
#             [node.tail])
#     # filter removes possible Nones in texts and tails
#     return ''.join(filter(None, parts))


if __name__ == '__main__':
    # Load main page, process sections
    page_html = graber.download_page(host)
    tree = parser.create_tree(page_html)
    sections = parser.extract_sections(tree, config['x_path']['sections'])
    articles = parser.extract_sections(tree, config['x_path']['categories'])

    # Extract section links
    f_h = lambda x : x.attrib.get('href')
    # f_t = lambda x : x.text
    for sec in sections:
        lect_links.append(host+f_h(sec))
    # Extract article links
    for art in articles:
        arti_links.append(host+f_h(art))

    # with open(os.path.join(root, art_db), 'w'):
        # Extract sublinks from article titles
        # for link in arti_links:
        #     arti_page = graber.download_page(link)
        #     tree = parser.create_tree(arti_page)
        #     a_links = parser.extract_sections(tree, config['x_path']['a_lectures'])

            # for link in a_links:




    pass