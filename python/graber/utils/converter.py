from utils.parser import Parser

from tempfile import mkstemp
from shutil import move, copymode
from os import fdopen, remove

def replace_text(file_path, text):
    k = 0
    #Create temp file
    fh, abs_path = mkstemp()
    with fdopen(fh,'w') as new_file:
        with open(file_path) as old_file:
            for line in old_file:
                if k < 4:
                    new_file.write(line)
                    k = k + 1
                else:
                    new_file.write(text)
    #Copy the file permissions from the old file to the new file
    copymode(file_path, abs_path)
    #Remove original file
    remove(file_path)
    #Move new file
    move(abs_path, file_path)

def gen_info(title, visible):
    str = '' \
          + '---\r\n'\
          + "title: '"+title+"'\r\n"\
          + "visible: '"+visible+"'\r\n"\
          + '---\r\n'

    return str


def fix_img(host, pr):
    for img in pr.soup.find_all('img'):
        if 'http' not in img['src']:
            img['src'] = host+img['src']


def find_nth(haystack, needle, n):
    start = haystack.find(needle)
    while start >= 0 and n > 1:
        start = haystack.find(needle, start+len(needle))
        n -= 1
    return start


def html_2_md(page):
    res_file = gen_info(page[0], 'true')
    # Extract paragraph
    pr = Parser(page[1])
    host = page[1][0:find_nth(page[1], "/", 3)+1]
    fix_img(host, pr)
    par = pr.soup.find(lambda tag:tag.name == "table" and
                len(tag.attrs) == 2 and
                tag["width"] == "100%" and
                tag["border"] == "0")
    [x.extract() for x in par.findAll('script')] # remove script tags
    [x.extract() for x in par.findAll('ins')]
    # remove bottom table
    # [x.extract for x in par.findAll(lambda tag: tag.name == "table" and
    #          len(tag.attrs) == 5 and
    #          tag["width"] == "900" and
    #          tag["cellspacing"] == "0" and
    #          tag["cellpadding"] == "0" and
    #          tag["border"] == "0" and
    #          tag["align"] == "center")]
    [x.extract() for x in par.findAllNext('table', {'width': '900'})]
    # for x in par.findAllNext('noindex'):
    #     x.findAllNext('table').extract()

    return res_file + par.__str__()

def html_2_md_cat(page):
    res_file = gen_info(page[0], 'true')
    # Extract paragraph
    pr = Parser(page[1])
    host = page[1][0:find_nth(page[1], "/", 3)+1]
    fix_img(host, pr)
    par = pr.soup.find(lambda tag:tag.name == "td" and
                len(tag.attrs) == 3 and
                tag["style"] == "border-width:1px; border:#B1DCF9" and
                tag["width"] == "100%" and
                tag["valign"] == "top")

    [x.extract() for x in par.findAll('script')] # remove script tags
    [x.extract() for x in par.findAll('noindex')]
    [x.extract() for x in par.findAll('center')]
    [x.extract() for x in par.findAll('p', {'class': 'viewinfo'})]
    [x.extract() for x in par.findAll('p', {'class': 'red'})]
    [x.extract() for x in par.findAll('div', {'class': 'ya-site-form'})]
    [x.extract() for x in par.findAll('div', {'class': 'pagelink'})]
    [x.extract() for x in par.findAllNext('table', {'width': '900'})]

    return res_file + par.__str__()


def html_2_md_def(page, links):
    res_file = gen_info(page[0], 'true')
    # Extract paragraph
    pr = Parser(page[1])
    par = pr.soup.find('p')
    try:
        res_file = res_file + par.text + '\r\n'
    except TypeError:
        print("Paragraph extraction problem: "+page[0])
    # Add links
    for i in range(0, len(links)):
        try:
            res_file = res_file+str(i+1)+'. '+links[i][0]+'\r\n'
        except TypeError:
            pass
    return res_file