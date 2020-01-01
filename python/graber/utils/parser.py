from lxml import etree


def create_tree(page):
    # parser = etree.HTMLParser()
    html_code = str(page, encoding="utf-8", errors="ignore")
    tree = etree.HTML(html_code)

    return tree


def extract_sections(tree, query):
    sections = tree.xpath(query)

    return sections
