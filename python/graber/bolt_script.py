import os
import configparser
import mysql.connector

from fixer import get_all_paths_by_level
from fixer import extract_title
from os.path import normpath, basename

# db connection config
root = os.path.dirname(os.path.abspath(__file__))
config_file = "config.ini"
config = configparser.ConfigParser()
config.read(os.path.join(root, config_file))

pages_path= '/home/dinir/Documents/git/graber_out/clean_pages/pages'

# {0} - must be in english cause it's name of a table
# {1} - must be in russian cause it's name of section in views
db_config_str = """{0}:
    name: {1}
    singular_name: {1}
    fields:
        title:
            type: text
            class: large
        slug:
            type: slug
            uses: title
        text:
            type: html
            height: 300px
    record_template: article.twig"""

def get_sec_name(s_path):
    start = s_path.find('.')
    return s_path[start+1:]

# DB initialization
# if __name__ == '__main__':
#     # tmp_dir = os.path.join(root, p_dir)
#     secs = [] # list contains eng[0] and rus[1] names of sections, each element is a tuple
#     dir_list = get_all_paths_by_level(pages_path, 1)
#     # secs = sort_by_default(dir_list)

#     # for each category add file table.txt
#     for dir_path in dir_list:
#         sec_name = get_sec_name(basename(normpath(dir_path)))[0:50] # name in english
        
#         # Get title from default.md
#         with open(os.path.join(dir_path, 'blog.md'), 'r') as blog_file:
#             blog_file.readline() # skip a first line
#             secs.append((sec_name.replace('-',''), extract_title(blog_file.readline())))

#         # Create table.txt with table name
#         with open(os.path.join(dir_path, 'table.txt'), 'w+') as f:
#             f.write('bolt_'+sec_name)
        
#     # Add configurations to config.yml
#     with open(os.path.join(pages_path, 'config.yml'), 'w+') as f:
#         for sec in secs:
#             f.write(db_config_str.format(sec[0], sec[1]))
#             f.write('\n\n')



if __name__ == "__main__":
    # dir_list = get_all_paths_by_level(pages_path, 1)
    
    # Connect to bolt_db
    cnx = mysql.connector.connect(user=config['bolt_db']['user'], password=config['bolt_db']['password'],
                              host=config['bolt_db']['host'],
                              database=config['bolt_db']['database'])
    cnx.close()

    pass