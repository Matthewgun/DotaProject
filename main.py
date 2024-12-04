from bs4 import BeautifulSoup
import urllib.request


class dotabuffParser:
    def __init__(self, hero):
        self.url = "http://dotabuff.com/heroes/" + str(hero) + "/matchups"
        self.hero1 = hero
        self.content = ''
        self.setContent()
        self.content_of_heroes = ''
        self.AllHeroListForDict = []
        self.HeroList = []
        self.setHeroList()
        self.dictinary_heroes = {}

    def setContent(self):
        opener = urllib.request.build_opener()
        opener.addheaders = [('User-agent',
                              'Mozilla/5.0')]
        # 'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.9; rv:45.0) Gecko/20100101 Firefox/45.0'
        response = opener.open(self.url)
        page = response.read()
        soup = BeautifulSoup(page, "lxml")
        self.content = soup.encode("utf-8")

    def setHeroList(self):
        # getData
        from lxml import html
        tree = html.fromstring(self.content)
        movie_link = tree.xpath('//table[@class="sortable"]')[0]  # table class="sortable"
        movie_link1 = movie_link[1].xpath('string()')

        self.content_of_heroes = movie_link1
        # Parsing
        listOfHeroes = movie_link1.split(',')
        listOfHeroes[0] = listOfHeroes[0][:listOfHeroes[0].find('%')]
        for i in range(1, len(listOfHeroes)):
            listOfHeroes[i] = listOfHeroes[i][3:listOfHeroes[i].find('%')]
        self.HeroList = listOfHeroes

    def getDictinary(self):
        import re
        regSymb = re.compile('[^a-zA-Z ]')
        regNum = re.compile('[^0-9.-]')

        for i in range(0, len(self.HeroList)):
            self.dictinary_heroes[regSymb.sub('', self.HeroList[i])] = regNum.sub('', self.HeroList[i])

        try:
            self.dictinary_heroes.pop('')
        except:
            print('')

        # Prepare best and worst matchups
        keys = list(self.dictinary_heroes.keys())
        if len(keys) > 10:
            best_matchups = []
            worst_matchups = []

            # Get first 5 for best_matchups
            for key in keys[:5]:
                value = self.dictinary_heroes[key]
                # Clean value before conversion
                clean_value = value.replace('--', '').strip()  # Remove double hyphens and whitespace
                best_matchups.append({
                    "hero": key,
                    "disadvantage": float(clean_value) if clean_value else 0.0  # Default to 0.0 if empty
                })

            # Get last 5 for worst_matchups
            for key in keys[-5:]:
                value = self.dictinary_heroes[key]
                clean_value = value.replace('--', '').strip()  # Remove double hyphens and whitespace
                worst_matchups.append({
                    "hero": key,
                    "disadvantage": float(clean_value) if clean_value else 0.0  # Default to 0.0 if empty
                })

            # Structure the final output
            self.dictinary_heroes = {
                "worst_matchups": best_matchups,
                "best_matchups": worst_matchups
            }

        return self.dictinary_heroes


class starter_of_parser():
    def __init__(self):
        self.DictinaryDictinary_heroes = {}
        self.hero_list = []

    def save_to_json(self):
        with open("HeroList.txt") as file_list:
            self.hero_list = file_list.readlines()

        for i in range(0, len(self.hero_list)):
            hero = self.hero_list[i].lower().replace(" ", "-").rstrip()
            print(hero.lower().replace(" ", "-").rstrip())
            parser = dotabuffParser(hero)
            self.DictinaryDictinary_heroes[hero] = parser.getDictinary()
        import json
        with open('HeroList.json', 'w') as file:
            json.dump(self.DictinaryDictinary_heroes, file, indent=2, ensure_ascii=False)


if __name__ == '__main__':
    textStarter = starter_of_parser()
    textStarter.save_to_json()
