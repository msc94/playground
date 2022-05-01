import requests as r

def download(url: str) -> bytes:
    response = r.get(url)
    response.raise_for_status()
    return response.content

if __name__ == "__main__":
    print(download("https://www.who.int/docs/default-source/coronaviruse/20200312-sitrep-52-covid-19.pdf?sfvrsn=e2bfc9c0_2"))