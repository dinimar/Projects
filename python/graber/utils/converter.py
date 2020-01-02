from utils.parser import Parser


def gen_info(title, visible):
    str = '' \
          + '---\r\n'\
          + "title: '"+title+"'\r\n"\
          + "visible: '"+visible+"'\r\n"\
          + '---\r\n'

    return str


def html_2_md(page):
    file_content = ""

    # pr = Parser(page[1])
    # doc = pr.soup.find('td', {'style': 'border-width:1px; border:#B1DCF9'})

    file_content = gen_info(page[0], 'true')

    return file_content
