import os

symbols = ("абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ",
           "abvgdeejzijklmnoprstufhzcss_y_euaABVGDEEJZIJKLMNOPRSTUFHZCSS_Y_EUA")
tr = {ord(a):ord(b) for a, b in zip(*symbols)}


def ru_2_en(str):
    return str.translate(tr)


def mkdir(path, name):
    res_path = path+"/"+ru_2_en(name)
    os.makedirs(res_path, exist_ok=True)