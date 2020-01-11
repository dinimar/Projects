import os
from fixer import get_all_paths_by_level
from os.path import normpath, basename

root = os.path.dirname(os.path.abspath(__file__))
pages_path= '/home/dinir/Documents/git/graber_out/clean_pages/pages'

def get_sec_name(s_path):
    start = s_path.find('.')
    return s_path[start+1:]

if __name__ == '__main__':
    # tmp_dir = os.path.join(root, p_dir)
    dir_list = get_all_paths_by_level(pages_path, 1)
    # secs = sort_by_default(dir_list)
    secs = {}
    # for each category create table(update config.yml int a+ mode)
    # and add file table.txt
    for dir_path in dir_list:
        secs[get_sec_name(sub_dir)] = dir_path
        # category

    # rename_sections(secs)
    # [x[0] for x in os.walk(os.path.join(root, p_dir))]
    # dir_l = os.walk(os.path.join(root, p_dir))
    pass
