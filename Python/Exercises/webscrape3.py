import requests
import bs4

res = requests.get('https://en.wikipedia.org/wiki/Jonas_Salk')
soup = bs4.BeautifulSoup(res.text,'lxml')

# soup.select('img')

print(soup.select('img')[0])
