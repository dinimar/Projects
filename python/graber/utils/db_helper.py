import os
from utils import converter

symbols = ("абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ",
           "abvgdeejzijklmnoprstufhzcss_y_euaABVGDEEJZIJKLMNOPRSTUFHZCSS_Y_EUA")
tr = {ord(a):ord(b) for a, b in zip(*symbols)}


def ru_2_en(str):
    return str.translate(tr)


def mkdir(path, name):
    section_q = "/"+ru_2_en(name)
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

