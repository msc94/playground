import sqlite3 as sql

def main():
    conn = sql.connect("data/articles.sqlite")
    result = conn.execute("SELECT id FROM article")

    result_list = []
    for result in result:
        result_list.append(result[0])
    
    print(result_list)


if __name__ == "__main__":
    main()
