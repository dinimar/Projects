from utils.parser import Parser


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
    par = pr.soup.find('sape_index')
    [x.extract() for x in par.findAll('script')] # remove script tags
    # Fix image src
    par.f

    return res_file + par.__str__()


def html_2_md_def(page, links):
    res_file = gen_info(page[0], 'true')
    # Extract paragraph
    pr = Parser(page[1])
    par = pr.soup.find('p')
    res_file = res_file + par.string + '\r\n'
    # Add links
    for i in range(0, len(links)):
        res_file = res_file+str(i+1)+'. '+links[i][0]+'\r\n'

    return res_file