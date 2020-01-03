import os
import threading
import configparser
from utils.parser import Parser
from utils import converter
from utils import db_helper

# Config setup
root = os.path.dirname(os.path.abspath(__file__))
config_file = "config.ini"
config = configparser.ConfigParser()
config.read(os.path.join(root, config_file))

# DB
p_dir = '/pages/categories' # dir for out pages
# db_dir = '/link_db'
# art_db = db_dir+'/articles.txt'
# link_db = db_dir+'/links.txt'

# Site data
host = "https://studopedia.ru"
# sec_links = [] # lection links
arti_links = [] # article links

class Counter(object):
    def __init__(self, start = 0):
        self.lock = threading.Lock()
        self.value = start
    def increment(self):
        # logging.debug('Waiting for a lock')
        self.lock.acquire()
        try:
            # logging.debug('Acquired a lock')
            self.value = self.value + 1
        finally:
            # logging.debug('Released a lock')
            self.lock.release()

k = Counter(2)

def process_categories(sect_links):
    for sec in sect_links:
        # Step 1 - create dirs
        res_path, section_q = db_helper.mkdir(root+p_dir, '0'+str(k.value)+'.'+sec[0])
        k.increment()
        # Step 2 - extract links from category
        s_pr = Parser(sec[1])
        s_links = []

        # Init next_page button
        next_page_but = s_pr.soup.find_all('a', text='Следующая')

        while len(next_page_but) != 0:
            try:
                s_links.extend(pr.extract_links(list(map(lambda x: x.a, filter(
                    lambda x: x.a is not None, map(lambda x: x, s_pr.soup.find_all('li')))))))
            except AttributeError:
                print("S_links problem in: "+section_q)
            s_pr = Parser(host+next_page_but.pop().get('href'))
            next_page_but = s_pr.soup.find_all('a', text='Следующая')
            break
        # Step 3 - for each link create docs.md
        for link in s_links:
            try:
                res_subpath, subsec_q = db_helper.touch_cat_docs(root+p_dir+section_q, link)
            except AttributeError:
                pass
        # Step 4 - create default.md
        db_helper.touch_default(root+p_dir+section_q, sec, s_links)
        # i = i+1


if __name__ == '__main__':
    # Load main page, process sections
    pr = Parser(host)
    categories = list(map(lambda x: x.a, pr.soup.find_all('td', {'width': '12%'})))

    # Extract links
    arti_links = pr.extract_links(categories)
    # c_pr = Parser(arti_links[0][1])
    # cat_links = c_pr

    process_categories(arti_links)

    # th_num = 40
    # slice = int(len(arti_links) / th_num)

    # k = 2
    # for i in range(0, th_num):
    #     if i == th_num-1:
    #         r_bound = len(arti_links)
    #     else:
    #         r_bound = (i+1)*slice
    #
    #     x = threading.Thread(target=process_categories, args=(arti_links[i * slice: r_bound], i,))
    #     x.start()
        # k = k+1
        # break

    # create dir for section
    # k = 2
    # for sec in sec_links:
    #     # Step 1 - create dirs
    #     res_path, section_q = db_helper.mkdir(root+p_dir, '0'+str(k)+'.'+sec[0])
    #     k = k + 1
    #     # Step 2 - extract links from section
    #     s_pr = Parser(sec[1])
    #     s_links = pr.extract_links(list(map(lambda x: x.a, s_pr.soup.find_all('li'))))
    #     # Step 3 - for each link create docs.md
    #     def_links = []
    #     for link in s_links:
    #         res_subpath, subsec_q = db_helper.touch_docs(root+p_dir+section_q, link)
    #     # Step 4 - create default.md
    #     db_helper.touch_default(root+p_dir+section_q, sec, s_links)
    #     break


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