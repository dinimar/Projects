from urllib3 import connection_from_url


def download_page(url):
    http_pool = connection_from_url(url)
    res = http_pool.urlopen('GET',url)

    print(res.data)