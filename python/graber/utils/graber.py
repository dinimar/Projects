from urllib3 import connection_from_url
import urllib.request
import os
import ssl
import time

try:
    _create_unverified_https_context = ssl._create_unverified_context
except AttributeError:
    # Legacy Python that doesn't verify HTTPS certificates by default
    pass
else:
    # Handle target environment that doesn't support HTTPS verification
    ssl._create_default_https_context = _create_unverified_https_context

def download_page(url):
    http_pool = connection_from_url(url)
    page_html = http_pool.urlopen('GET',url)

    return page_html.data

def save_pic(url, s_path):
    urllib.request.urlretrieve(url, s_path)
    # wait until file completely downloaded
    # while not os.path.exists(s_path):
    # time.sleep(3)
