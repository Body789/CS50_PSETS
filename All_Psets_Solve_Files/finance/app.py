import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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
    user_id = session["user_id"]
    base = db.execute("SELECT symbol, SUM(shares) AS shares, price FROM 'transaction' WHERE user_id = ? GROUP BY symbol", user_id)
    cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = cash_db[0]["cash"]
    total = cash
    for row in base:
        total += float(row["shares"]) * float(row["price"])
    names = []
    for row in base:
        names.append(lookup(row["symbol"])["name"])
    tees = []
    for row in base:
        tees.append(format(float(row["price"]) * float(row["shares"]), ".2f"))
    return render_template("index.html", base=base, cash=format(cash, ".2f"), total=format(total, ".2f"), names=names, tees=tees)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not shares.isdigit():
            return apology("shares must be int")
        shares = int(request.form.get("shares"))
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("symbol not found")
        if shares < 1:
            return apology("shares number must be posotive")

        price = stock["price"]

        user_id = session["user_id"]
        user = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)
        tp = float(price) * float(shares)
        cash = float(user[0]["cash"])

        if cash < tp:
            return apology("cannot afford")
        else:
            cash = cash - tp
            db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash=cash, user_id=user_id)
            date = datetime.datetime.now()
            db.execute("INSERT INTO 'transaction' (user_id, symbol, shares, price, date) VALUES (:user_id, :symbol,:shares, :price, :date)",
                       user_id=user_id, symbol=symbol,  shares=shares, price=price, date=date)
            flash("bought")
            return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    base = db.execute("SELECT * FROM 'transaction' WHERE user_id = ?", user_id)

    return apology("history.html", base=base)


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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        if not request.form.get("symbol"):
            return apology("there isnot symbol")

        stock = lookup(request.form.get("symbol"))

        if not stock:
            return apology("symbol not found")

        return render_template("quoted.html", symbol=stock["symbol"], name=stock["name"], price=format(stock["price"], ".2f"))


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submited
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submited
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password and confirmation")

        # ensure passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match")

        # ensure username is unique
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) >= 1:
            return apology("username already exists")

        # add user to database
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"),
                   hash=generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8))

        # login user automatically and remember session
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]

        # redirect to home page
        return redirect("/")

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]
        symbols = db.execute(
            "SELECT symbol FROM 'transaction' WHERE user_id = :id GROUP BY symbol HAVING SUM(shares) > 0", id=user_id)
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols])
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not shares.isdigit():
            return apology("shares must be int")
        shares = int(request.form.get("shares"))
        stock = lookup(request.form.get("symbol"))
        price = stock["price"]
        if shares < 1:
            return apology("shares number must be posotive")

        user_id = session["user_id"]
        user = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)
        tp = float(price) * float(shares)
        cash = float(user[0]["cash"])
        usershares = db.execute("SELECT shares FROM 'transaction' WHERE user_id = ? AND symbol = ?", user_id, symbol)
        ushares = usershares[0]["shares"]
        if shares > ushares:
            return apology("too many")
        cash = cash + tp
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash=cash, user_id=user_id)
        date = datetime.datetime.now()
        db.execute("INSERT INTO 'transaction' (user_id, symbol, shares, price, date) VALUES (:user_id, :symbol, :shares, :price, :date)",
                   user_id=user_id, symbol=symbol,  shares=(-1) * shares, price=price, date=date)
        flash("sold")
        return redirect("/")

