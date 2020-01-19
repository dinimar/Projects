import os
import ast

root = os.path.dirname(os.path.abspath(__file__))

def upload_dict(f_dict, f_path):
    with open(f_path, 'w+') as f:
        f.write(str(f_dict))

def read_dict(f_path):
    with open(f_path) as f:
        s = f.read()
    
    return eval(s)

# if __name__ == "__main__":
#     f_path = os.path.join(root, 'img_list.txt')

#     l_dict = {'f_name1': 'link',
#               'f_name2': 'link'}
    
#     upload_dict(l_dict, f_path)
#     read_dict = read_dict(f_path)
#     # img_list_fpath = os.path.join(root, 'img_list.txt')
#     # img = open(img_list_fpath, 'w+')
#     pass