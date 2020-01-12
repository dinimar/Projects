from urllib3 import connection_from_url
import wget


def download_page(url):
    http_pool = connection_from_url(url)
    page_html = http_pool.urlopen('GET',url)

    return page_html.data

def save_pic(url, s_path):
    wget.download(url, s_path)