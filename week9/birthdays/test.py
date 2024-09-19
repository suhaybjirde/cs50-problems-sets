from cs50 import SQL

db = SQL("sqlite:///birthdays.db")

row = db.execute("SELECT id FROM birthdays WHERE id = ?", 10)
print(len(row))