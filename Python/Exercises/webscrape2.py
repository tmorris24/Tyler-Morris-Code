import requests
import bs4

res = requests.get('https://en.wikipedia.org/wiki/Jonas_Salk')
soup = bs4.BeautifulSoup(res.text,'lxml')

soup.select('.toctext')

first_item = soup.select('.toctext')[0]

for item in soup.select('.toctext'):
    print(item.text)
