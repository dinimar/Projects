import os
from utils import converter
# import regex
import re
# pattern = re.compile('[\W_]+')

symbols = ("абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ",
           "abvgdeejzijklmnoprstufhzcss_y_euaabvgdeejzijklmnoprstufhzcss_y_eua")
tr = {ord(a):ord(b) for a, b in zip(*symbols)}

# def ru_2_en_upd(str):
#     return str.translate(tr)

def fix_str(str):
    # stripped_text = ''
    # for c in str:
    #     stripped_text += c if len(c.encode(encoding='utf_8')) == 1 else ''
    # str = re.sub(r'[^\x00-\x7F\x80-\xFF\u0100-\u017F\u0180-\u024F\u1E00-\u1EFF]', '', ru_2_en(str))
    str = re.sub(r'[^\x00-\x7f]',r'', ru_2_en(str)) # remove all non-latin chars
    str = re.sub(r"[^a-zA-Z0-9]+", ' ', str) # remove all special chars

    return str.replace(' ', '-')

def ru_2_en(str):
    return str.translate(tr)


def mkdir(path, name):
    section_q = "/"+ru_2_en(name)
    if len(section_q) > 255:
        section_q = section_q[0:100]
    res_path = path+section_q
    os.makedirs(res_path, exist_ok=True)

    return res_path, section_q


def touch_default(path, page, links):
    with open(path+"/default.md", 'w+') as f:
        f.write(converter.html_2_md_def(page, links))


def touch_docs(path, page):
    r_path, sub_sec = mkdir(path, page[0])


    with open(r_path+"/docs.md", 'w+') as f:
        f.write(converter.html_2_md(page))

    return r_path, sub_sec


def touch_cat_docs(path, page):
    r_path, sub_sec = mkdir(path, page[0])


    with open(r_path+"/docs.md", 'w+') as f:
        f.write(converter.html_2_md_cat(page))

    if os.path.exists(r_path + '/docs.md'):
        with open(path + '/proc_links.txt', 'a+') as f:
            f.write(page[1] + '\r\n')

    return r_path, sub_sec


def links_2_str(links):
    str = ''
    for link in links:
        str += link[1]+'\r\n'

    return str

def touch_comparison_file(path, links):
    with open(path+"/all_links.txt", 'w+') as f:
        f.write(links_2_str(links))

    # f = open(path+'/proc_links.txt', 'w')
    # f.close()
    with open(path+'/proc_links.txt', 'w+'):
        pass

# if __name__ == '__main__':
#     str = '!"№;%:?*()_)(*_  хорошая "№;%:музы%:?*ка%: かあふ>>'
#     print(fix_str(str))