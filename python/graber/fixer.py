import os, glob
import re
from utils import db_helper
from os.path import normpath, basename
from os import rename

root = os.path.dirname(os.path.abspath(__file__))
p_dir = 'out/pages'
pattern = "'.*'"


def get_all_paths_by_level(dir, level):
   pattern = dir + level * '/*'
   return [d for d in glob.glob(pattern) if os.path.isdir(d)]


def extract_title(str):
    pattern = "'.*'"
    return re.findall(pattern, str)[0][1:-1]


def sort_by_default(d_ls):
    sections = []

    for dir in d_ls:
        try:
            with open(os.path.join(dir, 'default.md'), 'r') as f:
                f.readline()
                sections.append({'name': extract_title(f.readline()), 'path': dir})
        except FileNotFoundError:
            # os.remove(dir)
            print(dir)
            pass

    sections.sort(key=lambda x: x['name'])

    return sections

    # pass
    # d_ls.sort(key=lambda x: x['name'])
    # pass


def rename_sections(secs):
    for i in range(0, len(secs)):
        k = ''
        if i < 10:
            k = k.join('0')

        orig_path = secs[i]['path']
        sub_dir = basename(normpath(orig_path))
        upd_sub_dir = k+str(i+2)+'.'+db_helper.fix_str(secs[i]['name'])
        upd_path = orig_path.replace(sub_dir, upd_sub_dir)
        rename(orig_path, upd_path)


if __name__ == '__main__':
    # tmp_dir = os.path.join(root, p_dir)
    dir_list = get_all_paths_by_level(os.path.join(root, p_dir), 1)
    secs = sort_by_default(dir_list)

    rename_sections(secs)
    # [x[0] for x in os.walk(os.path.join(root, p_dir))]
    # dir_l = os.walk(os.path.join(root, p_dir))
    pass
