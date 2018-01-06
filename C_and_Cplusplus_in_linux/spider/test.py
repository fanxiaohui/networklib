import re
import urllib

def getHtml(url):
    page = urllib.urlopen(url)
    html = page.read()
    return html

def getImg(html):
    reg = r'src="(.*?\.gif)"'
    imgre = re.compile(reg)
    imgList = re.findall(imgre,html)
    print imgList
    cnt = 1
    for imgurl in imgList:
        urllib.urlretrieve(imgurl,'%s.jpg' %cnt)
        cnt += 1

if __name__ == '__main__':
    html = getHtml('http://www.baidu.com')
    getImg(html)

