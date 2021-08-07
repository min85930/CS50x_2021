import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Query database for stocks
    rows = db.execute(
        "SELECT symbol, name, SUM(shares) as shares FROM stocks WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

    total = 0

    for item in rows:
        quote = lookup(item['symbol'])
        item['price'] = usd(quote['price'])
        item['total'] = quote['price']*item['shares']
        total += quote['price']*item['shares']

    # Query database for cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
    total += cash

    return render_template("index.html", rows=rows, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure symbol was submitted
        if not symbol:
            return apology("must provide symbol")

        # Ensure shares was submitted
        elif not shares:
            return apology("must provide shares")

        # Ensure shares was not fractional
        try:
            if int(shares) < 1:
                return apology("must provide shares")
        except:
            return apology("must provide shares")

        quote = lookup(symbol)

        if quote is None:
            return apology("must provide correct symbol")

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']

        if cash >= quote['price']*int(shares):
            db.execute("INSERT INTO stocks(user_id, symbol, name, shares, price, transacted) values (?, ?, ?, ?, ?, ?)",
                       session["user_id"], quote['symbol'], quote['name'], shares, quote['price'], datetime.datetime.now())
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash-quote['price']*int(shares), session["user_id"])
            flash("Bought!")
            return redirect("/")
        else:
            return apology("must hava enough cash")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    results = db.execute("SELECT * FROM stocks WHERE user_id = ?", session["user_id"])

    return render_template("history.html", results=results)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must provide symbol")

        quote = lookup(symbol)

        if quote is not None:
            return render_template("quoted.html", symbol=quote['symbol'], companyName=quote['name'], price=usd(quote['price']))
        else:
            return apology("must provide symbol")

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username")

        # Ensure password was submitted
        elif not password:
            return apology("must provide password")

        # Ensure confirmation was submitted
        elif not confirmation:
            return apology("must provide password")

        # Ensure confirmation was same as password
        elif password != confirmation:
            return apology("must provide same password")

        duplicate = db.execute("SELECT COUNT(*) as duplicate FROM users WHERE username = ?", username)[0]['duplicate']

        # Ensure username was not duplicate
        if duplicate:
            return apology("username already existed")

        # Insert database for new user
        db.execute("INSERT INTO users(username, hash) values(?, ?)", username, generate_password_hash(password))

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # Ensure symbol was submitted
        if not symbol:
            return apology("must provide symbol")

        # Ensure shares was submitted
        elif not shares:
            return apology("must provide shares")

        Quantity = db.execute("SELECT symbol, SUM(shares) as Quantity FROM stocks WHERE user_id = ? AND symbol = ? GROUP BY symbol",
                              session["user_id"], symbol)[0]['Quantity']

        # Ensure shares was greater than Quantity
        if shares > Quantity:
            return apology("you don't have enough shares")
        else:
            quote = lookup(symbol)
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
            db.execute("INSERT INTO stocks(user_id, symbol, name, shares, price, transacted) values (?, ?, ?, ?, ?, ?)",
                       session["user_id"], quote['symbol'], quote['name'], -shares, quote['price'], datetime.datetime.now())
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash+quote['price']*shares, session["user_id"])

        flash("Sold!")
        return redirect("/")
    else:
        rows = db.execute(
            "SELECT * FROM (SELECT symbol, SUM(shares) as Quantity FROM stocks WHERE user_id = ? GROUP BY symbol) WHERE Quantity > 0", session["user_id"])
        return render_template("sell.html", rows=rows)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
