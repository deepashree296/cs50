from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required, lookup, usd, match
import re

# Configure application
app = Flask(__name__)


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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get user id from session
    user_id = session["user_id"]

    # Get current cash value of logged in user from session
    user_cash = session["cash"]

    # Get user stocks
    stocks = db.execute("SELECT symbol, name, SUM(shares) as total_shares from transactions where user_id = :id GROUP BY symbol HAVING total_shares > 0",
                        id=user_id)

    # Iterate over symbols to get the latest stock price
    total = user_cash
    for stock in stocks:
        desc = lookup(stock["symbol"])
        stock["price"] = desc["price"]
        stock["total_value"] = stock["total_shares"] * desc["price"]
        total += stock["total_value"]

    return render_template("index.html", stocks=stocks, user_cash=user_cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST ( submitting form )
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        user_cash = session["cash"]
        user_id = session["user_id"]

        # check for invalid input
        if not symbol:
            return apology("Invalid symbol", 400)

        if not shares:
            return apology("Invalid number of shares", 400)

        if not re.match("^[0-9]+$", shares):
            return apology("Invalid share", 400)

        # calling lookup for current value of symbol
        desc = lookup(request.form.get("symbol"))

        # check for desc null
        if not desc:
            return apology("symbol does not exist", 400)

        price = desc["price"]

        # check for sufficient amount of cash to buy share
        if user_cash < (price * int(shares)):
            return apology("can not afford", 400)

        # debit user cash ( update user table )
        user_cash = user_cash - (price * int(shares))

        db.execute("UPDATE users SET cash = :value where id = :id",
                   value=user_cash,
                   id=user_id)

        # Insert transaction in user transaction table
        db.execute("INSERT INTO transactions(\"user_id\", \"symbol\", \"name\", \"shares\", \"price\") VALUES (:id, :sym, :name, :share, :price)",
                   id=user_id,
                   sym=symbol,
                   name=desc["name"],
                   share=shares,
                   price=price)

        # update the session variables

        session["cash"] = user_cash

        flash("Bought!")
        return redirect("/")

    # User reached route via GET (redirect or clicking on link)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]
    # get rows from user transaction table
    txn = db.execute("SELECT symbol, shares, created_on as date, price from transactions where user_id = :id",
                     id=user_id)

    # pass this to render_template
    return render_template("history.html", txn=txn)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["cash"] = rows[0]["cash"]

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

    # user reached route via POST
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("invalid symbol", 400)

        desc = lookup(request.form.get("symbol"))

        if not desc:
            return apology("Invalid symbol", 400)
        return render_template("quoted.html", desc=desc)

    # user reached route via GET
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirm password was submitted
        if not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("password do not match", 400)

        valid = match(request.form.get("password"))

        if valid == False:
            return apology("Please enter password of min length 5", 400)

        # Insert in database
        result = db.execute("INSERT INTO users (\"username\", \"hash\") VALUES (:username, :password)",
                            username=request.form.get("username"),
                            password=generate_password_hash(request.form.get("password")))

        # Ensure username is different
        if not result:
            return apology("username already exists", 400)

        # Remember which user has logged in
        session["user_id"] = result
        session["cash"] = 10000
        # redirect user to login on successful registration
        flash("Registered!")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("registration.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]
    user_cash = session["cash"]
    # Get user stocks
    stocks = db.execute("SELECT symbol, name, SUM(shares) as total_shares from transactions where user_id = :id GROUP BY symbol HAVING total_shares > 0",
                        id=user_id)

    # User reaches route via POST
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure symbol is submitted
        if not request.form.get("symbol"):
            return apology("Invalid symbol", 400)

        # Ensure share is entered
        if not request.form.get("shares"):
            return apology("Invalid shares", 400)

        # Ensure user has bought that particular stock
        Found = False
        for stock in stocks:
            if stock["symbol"] == symbol:
                Found = True
                curr_shares = stock["total_shares"]
                break

        if Found == False:
            return apology("No shares bought yet!", 400)

        # Ensure user has enough share of the stock
        if int(curr_shares) < int(shares):
            return apology("Not enough shares to send", 400)

        # lookup the current price of stock
        desc = lookup(symbol)

        if not desc:
            return apology("Invalid symbol", 400)

        curr_stock_price = desc["price"]
        user_cash = user_cash + (curr_stock_price * int(shares))

        # make an entry into the transaction table
        db.execute("INSERT INTO transactions(\"user_id\", \"symbol\", \"name\", \"shares\", \"price\") VALUES (:id, :sym, :name, :share, :price)",
                   id=user_id,
                   sym=symbol,
                   name=desc["name"],
                   share=0 - int(shares),
                   price=curr_stock_price)

        # update user cash in user table
        db.execute("UPDATE users SET cash = :value where id = :id",
                   value=user_cash,
                   id=user_id)

        # update cash session variable
        session["cash"] = user_cash

        flash("Sold!")

        return redirect("/")

    # User reaches route via GET
    else:
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
