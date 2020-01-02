from utils.parser import Parser


def gen_info(title, visible):
    str = '' \
          + '---\r\n'\
          + "title: '"+title+"'\r\n"\
          + "visible: '"+visible+"'\r\n"\
          + '---\r\n'

    return str


def html_2_md(page):
    res_file = gen_info(page[0], 'true')
    # Extract paragraph
    pr = Parser(page[1])
    par = pr.soup.find('td', {'style':'border-width:1px; border:#B1DCF9'}).p
    # Update res_file
    res_file = res_file + par.string

    return res_file
