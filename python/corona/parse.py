import typing
import re

class Data:
    country: str
    confirmed: int
    dead: int

    def __str__(self):
        return f"{self.country}: {self.confirmed} {self.dead}"

def parse(text:str):
    entries = typing.List[Data]

    country_regex = re.compile(r"<p>(\D)+ (\d)+ (\d)+ (\d)+ (\d)+ (\D)+ (\d)+")
    
    tablefound = False
    for line in text.splitlines():
        if line.startswith("<p>Table 2. Countries, territories or areas outside China"):
            tablefound = True
        
        if not tablefound:
            continue

        if line.startswith("<p>Subtotal for all"):
            break

        match = country_regex.match(line)
        if match:
            new = Data()
            new.country = match.group(1)
            new.country = match.group(2)
            new.country = match.group(4)
            print(new)

    return entries



if __name__ == "__main__":
    from download import download
    from extract import extract
    d = download("https://www.who.int/docs/default-source/coronaviruse/20200312-sitrep-52-covid-19.pdf?sfvrsn=e2bfc9c0_2")
    o = extract(d)
    print(parse(o))