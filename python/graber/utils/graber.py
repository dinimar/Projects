from urllib3 import connection_from_url
import urllib.request
import os


def download_page(url):
    http_pool = connection_from_url(url)
    page_html = http_pool.urlopen('GET',url)

    return page_html.data

def save_pic(url, s_path):
    urllib.request.urlretrieve(url, s_path)
    # wait until file completely downloaded
    while not os.path.exists(s_path):
        time.sleep(1)
