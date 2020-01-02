from bs4 import BeautifulSoup
from utils import graber


class Parser:
    def __init__(self, host):
        self.host = host
        self.soup = self.create_tree()

    def create_tree(self):
        soup = BeautifulSoup(graber.download_page(self.host), 'html.parser')

        return soup

    def extract_links(self, list):
        links = []
        for el in list:
            href = el.get('href')
            if href[0] != '/':
                href = '/'+href
            links.append((el.string, self.host+href))

        return links
