import os
import threading
import configparser
from utils.parser import Parser
from utils import converter
from utils import db_helper
import datetime
import time


# Config setup
root = os.path.dirname(os.path.abspath(__file__))
config_file = "config.ini"
config = configparser.ConfigParser()
config.read(os.path.join(root, config_file))

from pygame import mixer
mixer.init() #you must initialize the mixer
alert=mixer.Sound(root+'/bell.wav')


# DB
p_dir = '/pages/categories' # dir for out pages
# db_dir = '/link_db'
# art_db = db_dir+'/articles.txt'
# link_db = db_dir+'/links.txt'

# Site data
host = "https://studopedia.ru"
# sec_links = [] # lection links
arti_links = [] # article links
s_links = [] # ct_links
# res_path = ''

# class Counter(object):
#     def __init__(self, start = 0):
#         self.lock = threading.Lock()
#         self.value = start
#     def increment(self):
#         # logging.debug('Waiting for a lock')
#         self.lock.acquire()
#         try:
#             # logging.debug('Acquired a lock')
#             self.value = self.value + 1
#         finally:
#             # logging.debug('Released a lock')
#             self.lock.release()

# k = Counter(2)

start_time = time.time()

def process_category(sec):
    # for sec in sect_links:
    # Step 1 - create dirs
    res_path, section_q = db_helper.mkdir(root+p_dir, sec[0])

    # Step 2 - extract links from category
    s_pr = Parser(sec[1])

    # Init next_page button
    # next_page_but = s_pr.soup.find_all('a', text='Следующая')

    while True:
        try:
            s_links.extend(pr.extract_links(list(map(lambda x: x.a, filter(
                lambda x: x.a is not None, map(lambda x: x, s_pr.soup.find_all('li')))))))
        except AttributeError:
            print("S_links problem in: "+section_q)

        next_page_but = s_pr.soup.find_all('a', text='Следующая')
        if len(next_page_but) != 0:
            s_pr = Parser(host+next_page_but.pop().get('href'))
        else:
            break
    # Step 4 - create default.md
    db_helper.touch_default(res_path, sec, s_links)
    db_helper.touch_comparison_file(res_path, s_links)

    return res_path


def process_links(links, res_path):
    # Step 3 - for each link create docs.md
    # with open(res_path+'/proc_links.txt', 'w+'):
    #     pass
    for link in links:
        try:
            res_subpath, subsec_q = db_helper.touch_cat_docs(res_path, link)
        except AttributeError:
            print(link)
            pass
        # finally:

    print(time.time()-start_time)
    alert.play()
    # print('\a')



def get_last_links(res_path):
    all_links = [line.rstrip('\r\n') for line in open(res_path+'/all_links.txt')]
    proc_links = [line.rstrip('\r\n') for line in open(res_path+'/proc_links.txt')]

    return [x for x in all_links if x not in proc_links]

# start_time = time.process_time()
print(datetime.datetime.now().time())

if __name__ == '__main__':
    # Load main page, process sections
    pr = Parser(host)
    categories = list(map(lambda x: x.a, pr.soup.find_all('td', {'width': '12%'})))

    # Extract links
    cat_links = pr.extract_links(categories)
    # c_pr = Parser(arti_links[0][1])
    # cat_links = c_pr

    ct = cat_links[0]
    cat_name = 'Юриспунденкция'
    print(cat_name)

    for i in range(len(cat_links)):
        if cat_links[i][0] == cat_name:
            ct = cat_links[i]
            break

    res_path = process_category(ct)

    # process_links(res_path, ct)
    #
    # th_num = 40
    # slice = int(len(arti_links) / th_num)


    last_links = get_last_links(res_path)
    if len(last_links) != 0:
        # global s_links
        # tmp_links = s_links
        # s_links.clear()
        for x in s_links:
            if x[1] not in last_links:
                s_links.remove(x)
        # s_links([x for x in tmp_links if x not in last_links])

    th_num = 20
    slice = int(len(s_links)/th_num)

    # k = 2
    for i in range(0, th_num):
        if i == th_num-1:
            r_bound = len(s_links)
        else:
            r_bound = (i+1)*slice

        x = threading.Thread(target=process_links, args=(s_links[i * slice: r_bound], res_path,))
        x.start()
        # x.join()
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
    # pass
    # print(time.process_time() - start_time)


