import os
import configparser
import mysql.connector
import mysql.connector.errors

from datetime import date, datetime, timedelta
from fixer import get_all_paths_by_level
from fixer import extract_title
from os.path import normpath, basename
from slugify import slugify
from bs4 import BeautifulSoup
from utils import graber
from urllib import error
import uuid
from datetime import datetime

# db connection config
root = os.path.dirname(os.path.abspath(__file__))
config_file = "config.ini"
config = configparser.ConfigParser()
config.read(os.path.join(root, config_file))

pages_path = '/pages/final'
pic_subdir = 'files/2020-01/'
public_dir = '/var/www/vashotvet.com/bolt/public'
pic_path = os.path.join(public_dir, pic_subdir)

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

bug_f_p = os.path.join(root, 'log/imgs_500.txt') #  imgs with status 500
if os.path.exists(bug_f_p):
    bug_f = open(bug_f_p, 'w') 
else:
    bug_f = open(bug_f_p, 'w+')
bug_f.write("{")

proc_f_p = os.path.join(root, 'log/proc_dirs.txt') # proc_dirs.txt filepath
if os.path.exists(proc_f_p):
    proc_f = open(proc_f_p, 'w') # processed dirs
else:
    proc_f = open(proc_f_p, 'w+') # processed dirs


# remove links on studopedia, download image, update links
def fix_img(title, text):
    # Convert text to soup
    soup = BeautifulSoup(text, 'html.parser')
    # Check image appearance
    imgs = soup.find_all('img')
    if len(imgs) != 0: 
        # For each image tag
        for img in imgs:
            try:
                # a) donwnload picture to specified directory
                url = img['src']
                filename = url.rsplit('/', 1)[-1]
                ext = filename.rsplit('.', 1)[-1]
                uuid_fname = str(uuid.uuid4())+'.'+ext
                f_path = os.path.join(pic_path, uuid_fname)
                graber.save_pic(url, f_path)
                # b) update link
                img['src'] = '/'+os.path.join(pic_subdir, uuid_fname)
            except FileExistsError:
                continue
            except FileNotFoundError:
                bug_f.write("'"+url+"': '"+f_path+"',\n\n")
            except KeyError:
                continue
            except error.HTTPError as e:
                if e.code == 500:
                    bug_f.write("'"+url+"': '"+f_path+"',\n\n")
                else:
                    print('\n', url, e.code)
            except http.client.InvalidUrl:
                bug_f.write("'"+url+"': '"+f_path+"',\n\n")

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
    slug = slugify(title)
    if len(slug) > 128:
       	slug = slug[0:128]
    data_article = {
        'slug': slug,
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
    k = 0 # number of processed tables

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
            try:
                title, text = extract_tt(os.path.join(doc_path, 'docs.md'))
                # Insert new article
                data_article = gen_article(title, text)
                cursor.execute(add_article.format(table=table_ex), data_article)
            except FileNotFoundError:
                continue
                # print('No docs.md file for ', doc_path)
                # print(datetime.now())
            except error.URLError as e:
                continue
                # bug_f.write('table: '+table_ex)
                # bug_f.write('path: '+dir_path)
                # bug_f.write('---')
                # print('ex: ', e)
                # print('table: ', table_ex)
                # print('path: ', doc_path)
                # print(datetime.now())
                # print('---')
            except ValueError as e:
                continue
                # print('ex: ', e)
                # print('table: ', table_ex)
                # print('path: ', doc_path)
                # print(datetime.now())
                # print('---')
            except mysql.connector.errors.DatabaseError as e:
                # print('data: ', data_article)
                # print(datetime.now())
                continue
            
        # break
        k = k+1
        proc_f.write(str(k)+', '+table_ex+', '+dir_path+', '+'\n\n')
        # Make sure data is committed to the database
        cnx.commit()

    # Close connection
    cursor.close()
    cnx.close()
    bug_f.write("OK, ALL PAGES UPLOADED!")
    # Close files
    bug_f.write("}")
    bug_f.close()
    proc_f.close( )

