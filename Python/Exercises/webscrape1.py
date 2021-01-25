import requests
import bs4

result = requests.get("https://en.wikipedia.org/wiki/Jonas_Salk")
print(type(result))
# print(result.text)

soup = bs4.BeautifulSoup(result.text, "lxml")

# print(soup)

print(soup.select('title'))

site_paragraphs = soup.select("p")

print(site_paragraphs)
print(site_paragraphs[0])
