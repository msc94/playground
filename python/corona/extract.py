import requests as r

def extract(data: bytes) -> str:
    response: r.Response = r.put(
            f"http://localhost:9998/tika",
            headers={"Accept": "text/html", "Content-Type": "application/pdf"},
            data=data,
            timeout=600
        )
    response.raise_for_status()
    return response.text

if __name__ == "__main__":
    from download import download
    d = download("https://www.who.int/docs/default-source/coronaviruse/20200312-sitrep-52-covid-19.pdf?sfvrsn=e2bfc9c0_2")
    o = extract(d)
    print(o)
    with open("data.html", "w") as f:
        f.write(o)