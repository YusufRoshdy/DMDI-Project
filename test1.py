from pprint import pprint
import psycopg2
import psycopg2.extras

user = 'postgres'
password = 'password'
host = 'localhost'
port = 5432
dbname = 'hospital'

url = f'postgres://{user}:{password}@{host}:{port}/{dbname}'
conn = psycopg2.connect(url)

queries = [
    ('All doctors', 'SELECT * FROM Users;'),
    ('All patients', 'SELECT * FROM Users;'),
]

while True:
    for i, query in enumerate(queries):
        print(f'{i+1})', query[0])

    selection = -1
    while selection < 0 or selection > len(queries):
        print('Select the query you want to execute:', end=' ')
        selection = int(input())
    if selection == 0:
        break

    selection -= 1

    cur = conn.cursor()

    cur.execute(queries[selection][1])
    result = cur.fetchall()
    cur.close()

    pprint(result)
    print()

conn.close()
