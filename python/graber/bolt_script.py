import os
import configparser
import mysql.connector

from datetime import date, datetime, timedelta
from fixer import get_all_paths_by_level
from fixer import extract_title
from os.path import normpath, basename
from slugify import slugify
from bs4 import BeautifulSoup
from utils import graber
import uuid

# db connection config
root = os.path.dirname(os.path.abspath(__file__))
config_file = "config.ini"
config = configparser.ConfigParser()
config.read(os.path.join(root, config_file))

pages_path = '/home/dinir/Documents/git/graber_out/clean_pages/pages'
pic_subdir = 'files/2020-01/'
pic_path = os.path.join(root, pic_subdir)

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


add_article = ("INSERT INTO {table} "
              "(slug, datecreated, datechanged, ownerid, status, templatefields, title, text) " 
              "VALUES (%(slug)s, %(datecreated)s, %(datechanged)s, %(ownerid)s, %(status)s, %(templatefields)s, %(title)s, %(text)s)")
today = datetime.now().date()

# remove links on studopedia, download image, update links
def fix_img(title, text):
    # Convert text to soup
    soup = BeautifulSoup(text, 'html.parser')
    slug = slugify(title)
    os.mkdir(os.path.join(pic_path, slug))
    # For each image tag
    for img in soup.find_all('img'):
        try:
            # a) donwnload picture to specified directory
            url = img['src']
            filename = url.rsplit('/', 1)[-1]
            ext = filename.rsplit('.', 1)[-1]
            uuid_fname = str(uuid.uuid4())+'.'+ext
            f_path = os.path.join(pic_path, slug, uuid_fname)
            graber.save_pic(url, f_path)
            # b) update link
            img['src'] = '/'+os.path.join(pic_subdir, slug, filename)
        except FileExistsError:
            print("Image ", url, " already dowloaded or name collision")
            continue
        except FileNotFoundError:
            print("Image from ", url, " wasn't downloaded.")
        except KeyError:
            print("Empty image skipped")
            continue

    return str(soup)


# extract title and text
def extract_tt(d_path):
    title = ''
    text = ''

    with(open(d_path, 'r')) as f:
        k = 0
        for x in f:
            if k == 1: 
                title = extract_title(x)
            elif k > 3:
                text = text + f.read()
                break

            k = k + 1

    text = fix_img(title, text)

    return title, text


def gen_article(title, text):
    data_article = {
        'slug': slugify(title),
        'datecreated': today,
        'datechanged': today,
        'ownerid': 1,
        'status': 'published',
        'templatefields': '[]',
        'title': title,
        'text': text,
    }

    return data_article

if __name__ == "__main__":
    dir_list = get_all_paths_by_level(pages_path, 1)
    table_ex = '' # extracted table name

    # Connect to bolt_db
    cnx = mysql.connector.connect(user=config['bolt_db']['user'], password=config['bolt_db']['password'],
                              host=config['bolt_db']['host'],
                              database=config['bolt_db']['database'])
    cursor = cnx.cursor()

    for dir_path in dir_list:
        # extract table name
        with open(os.path.join(dir_path, 'table.txt'), 'r') as f:
            table_ex = f.readline() 
        doc_list = get_all_paths_by_level(dir_path, 1)
        for doc_path in doc_list:
            title, text = extract_tt(os.path.join(doc_path, 'docs.md'))
            # Insert new article
            data_article = gen_article(title, text)
            cursor.execute(add_article.format(table=table_ex), data_article)
            # break
        print(table_ex)
        break

    # Make sure data is committed to the database
    cnx.commit()

    # Close connection
    cursor.close()
    cnx.close()

