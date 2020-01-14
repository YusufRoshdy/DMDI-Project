import tkinter as tk
import mysql.connector
from tkinter.scrolledtext import ScrolledText

patient_id = 1
params = {
    'host': "localhost",
    'user': "root",
    'passwd': "password",
    'database': "hospital"
}

root = tk.Tk()
root.title("DMD")
root.resizable(False, False)

root.rowconfigure(0, pad=3, weight=1)
root.rowconfigure(1, pad=3, weight=1)

# To display result
text = ScrolledText(root)
text.grid(row=1, column=0, columnspan=6, rowspan=5)

queries = [f'call q{i}();' for i in range(1, 5+1)]
queries[0] = f'call q1({patient_id});'  # modify special case

# Callback function called by button


def query(num):
    conn = mysql.connector.connect(**params)
    cur = conn.cursor(dictionary=True)
    cur.execute(queries[num - 1])
    s = ''
    result = cur.fetchall()
    print(result)
    if isinstance(result, list):
        for row in result:
            s += str(row) + '\n'
    else:
        s = result
    text.delete('1.0', tk.END)
    text.insert(tk.END, s)
    cur.close()
    conn.close()


def insert():
    conn = mysql.connector.connect(**params)
    cur = conn.cursor()
    dump = open('output (6).txt').read()
    cur.execute(dump)
    conn.commit()
    text.delete('1.0', tk.END)
    text.insert(tk.END, f'{cur.rowcount} rows inserted successfully!')
    cur.close()
    conn.close()


# Buttons
query1 = tk.Button(root,
                   text="Search Doctor",
                   command=lambda: query(1))
query1.grid(row=0, column=0)

query2 = tk.Button(root,
                   text="Report",
                   command=lambda: query(2))
query2.grid(row=0, column=1)

query3 = tk.Button(root,
                   text="Patients",
                   command=lambda: query(3))
query3.grid(row=0, column=2)

query4 = tk.Button(root,
                   text="Income",
                   command=lambda: query(4))
query4.grid(row=0, column=3)

query5 = tk.Button(root,
                   text="Doctors",
                   command=lambda: query(5))
query5.grid(row=0, column=4)

insert = tk.Button(root,
                   text="Insert all",
                   command=insert)
insert.grid(row=0, column=5)


root.mainloop()
