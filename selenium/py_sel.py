from selenium import webdriver
import time

#PATH = "./geckodriver/geckodriver.exe"
PATH = "./chromedriver/chromedriver.exe"
driver = webdriver.Chrome(PATH)
#subject = 'five hundred divided by 10'
subject = '10 factorial'
#subject = '900*13'

url = 'https://www.google.com/search?q='
url += subject
driver.get(url)
time.sleep(1)
search_text = driver.find_element("id","search").text
search_text = search_text.split("=")[1].split("Du")[0].strip()
print(f"Result: {search_text}")
