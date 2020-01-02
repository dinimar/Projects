import os
import configparser
from utils.parser import Parser
from utils import converter

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
sec_links = [] # lection links
arti_links = [] # article links


if __name__ == '__main__':
    # Load main page, process sections
    pr = Parser(host)
    sections = list(pr.soup.find_all('a', {'class': 'nav_link'}))
    categories = list(map(lambda x: x.a, pr.soup.find_all('td', {'width': '12%'})))

    # Extract links
    sec_links = pr.extract_links(sections)
    arti_links = pr.extract_links(categories)

    md = converter.html_2_md(sec_links[0])
    print(md)

    # with open(os.path.join(root, ))
    # for sec in sec_links:
    # s_pr = sec_links[0]
    # s_pr = Parser(sec[1])
    # s_links = s_pr.extract_links(list(map(lambda x: x.a, s_pr.soup.find_all('li'))))

    # pass

    # Extract section links
    # f_h = lambda x : x.attrib.get('href')
    # f_t = lambda x : x.text
    # lect_links = sections..text
    # for sec in sections:
    #     lect_links.append(host+f_h(sec))
    #     stringify_children(sec)
    # Extract article links
    # for art in articles:
    #     arti_links.append(host+f_h(art))

    # with open(os.path.join(root, art_db), 'w'):
        # Extract sublinks from article titles
        # for link in arti_links:
        #     arti_page = graber.download_page(link)
        #     tree = parser.create_tree(arti_page)
        #     a_links = parser.extract_sections(tree, config['x_path']['a_lectures'])

            # for link in a_links:




    pass