import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd, validateRegister

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session['user_id']
    user_stock = db.execute("SELECT * FROM stocks WHERE user_id = ?", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ? ", user_id)
    if cash:
        cash = cash[0]['cash']

    grand_total = 0
    if user_stock:
        for stock in user_stock:
            res = lookup(stock['symbol'])
            stock['price'] = usd(res['price'])
            stock['total'] = usd(stock['shares'] * res['price'])
            grand_total += stock['shares'] * res['price']

        return render_template('index.html', stocks=user_stock, cash=usd(cash), grand_total=usd(grand_total + cash))
    return render_template('index.html', cash=usd(cash), grand_total=usd(cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == 'POST':
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        id = session['user_id']

        if symbol and shares:
            try:
                shares = int(shares)
            except ValueError:
                return apology('inviled shares')
            
            if shares <= 0:
                return apology('inviled shares')
            
            res = lookup(symbol)
            if res:
                users_current_price = db.execute('SELECT cash FROM users WHERE id = ?', session['user_id'])[0]['cash']
                stock_price = res['price']
                total_price = shares * stock_price

                if users_current_price < total_price:
                    return apology("can't afford")
                
                check = db.execute("SELECT 1 FROM stocks WHERE symbol = ? and user_id = ?", res['symbol'], id)
                if check:
                    db.execute("UPDATE stocks SET shares = shares + ? WHERE user_id = ?", shares, id)
                else:
                    db.execute("INSERT INTO stocks(user_id, symbol, shares) VALUES(?, ?, ?)", id, res['symbol'], shares)
                db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_price, id)
                db.execute("INSERT INTO transections(user_id, symbol, shares, price, date) VALUES(?, ?, ?, ?, ?)", id, res['symbol'], shares, res['price'], datetime.now())
                flash("Bought")
                return redirect('/')
            else:
                return apology("invalid symbol")
    return render_template('buy.html')


@app.route("/history")
@login_required
def history():
    transections = db.execute("SELECT * FROM transections")
    return render_template('history.html', transections=transections)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == 'POST':
        if request.form:
            symbol = request.form.get('symbol')
            res = lookup(symbol)
            if res:
                return render_template('quoted.html', stock_name=res['name'], stock_ticker=res['symbol'], stock_price=usd(res['price']))
            else:
                return apology('inviled symbol')
    return render_template('quote.html')


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == 'POST':
        if not request.form:
            return {"error": 'inviled Request'}, 400
        
        name = request.form.get('username')
        password = request.form.get('password')
        cf_passwrod = request.form.get("comfirm")
        if not (name and password and cf_passwrod):
            return apology('Fill the Form')
        
        result = validateRegister(password, cf_passwrod)
        if not result['valid']:
            return apology(result['message'])
        
        hashed_password = generate_password_hash(password)
        try:
            db.execute('INSERT INTO users(username, hash) VALUES(?, ?)', name, hashed_password)
            session['user_id'] = db.execute('SELECT id FROM users WHERE username = ?', name)[0]['id']
            flash("successfully Registered")
        except ValueError:
            return apology('USERNAME TAKEN')
        return redirect('/')
                

    return render_template('register.html')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    id = session['user_id']
    if request.method == 'POST':
        if request.form:
            symbol = request.form.get('symbol')
            shares = request.form.get('shares')

            if not (symbol and shares):
                return apology("inviled Share or Symbol")
            
            try:
                shares = int(shares)
            except ValueError:
                return apology('inviled shares')
            
            res = lookup(symbol)
            if res:

                user_stocks = db.execute("SELECT * FROM stocks WHERE user_id = ? and symbol = ?", id, symbol)

                if not user_stocks:
                    return apology("Don't Own this stock")
                
                if user_stocks[0]['shares'] < shares:
                    return apology("Don't have this many shares")
                
                sold_stock = shares * res['price']

                
                if user_stocks[0]['shares'] - shares == 0:
                    db.execute("DELETE FROM stocks WHERE user_id = ? and symbol = ?", id, symbol)
                else:
                    db.execute("UPDATE stocks SET shares = shares - ? WHERE user_id = ? and symbol = ?", shares, id, symbol)


                db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", sold_stock, id)
                db.execute("INSERT INTO transections(user_id, symbol, shares, price, date) VALUES(?, ?, ?, ?, ?)", id, res['symbol'], (shares * -1), res['price'], datetime.now())
                flash("sold")
                return redirect("/")
            else:
                return apology("inviled stock symbol")

    user_stocks = db.execute("SELECT symbol FROM stocks WHERE user_id = ?", id)
    return render_template("sell.html", stocks=user_stocks)


if __name__ == '__main__':
    app.run(debug=True)