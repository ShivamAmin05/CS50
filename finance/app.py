import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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
    id = session["user_id"]
    purchases = db.execute("SELECT SUM(shares) AS shares, stock, symbol, price FROM purchases WHERE id=? GROUP BY stock",id)
    cash = db.execute("SELECT cash from users WHERE id = ?", id)[0]["cash"]
    return render_template("index.html", database=purchases, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    shares = request.form.get("shares")
    id = session["user_id"]
    username = db.execute("SELECT username from users WHERE id=?", id)[0]["username"]
    cash = db.execute("SELECT cash from users WHERE id = ?", id)[0]["cash"]
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        ["shares"]
        if not stock:
            return apology("stock symbol does not exist", 400)
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("shares must be a positive integer", 400)
        if cash > (stock["price"] * int(shares)):
            db.execute("INSERT INTO purchases (id, username, stock, symbol, price, shares) VALUES (?,?,?,?,?,?)", id, username, stock["name"], stock["symbol"], stock["price"], int(shares))
            db.execute("UPDATE users SET cash=? WHERE id=?",cash-(stock["price"] * int(shares)), id)
            flash("Bought " + str(shares) + " " + stock["name"] + " stocks at " + str(stock["price"]) + " each")
        else:
            return apology("not enough cash to purchase stocks", 400)
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    id = session["user_id"]
    purchases = db.execute("SELECT shares, stock, symbol, price FROM purchases WHERE id=?", id)
    cash = db.execute("SELECT cash from users WHERE id = ?", id)[0]["cash"]
    return render_template("history.html", database=purchases, cash=cash)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

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
    if request.method == "POST":
        symbol = lookup(request.form.get("symbol"))
        if not symbol:
            return apology("Stock Symbol does not exist", 400)
        else:
            return render_template("quoted.html", name=symbol["name"],price=symbol["price"],symbol=symbol["symbol"])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        hash = generate_password_hash(request.form.get("password"))
        username_exists = db.execute("SELECT id from users WHERE username=?",username)

        if not username:
            return apology("must provide username", 400)
        if username_exists:
            return apology("username already exists", 400)
        if not password:
            return apology("must provide password", 400)
        if password != confirmation:
            return apology("confirmation does not match password", 400)

        db.execute("INSERT INTO users (username, hash) VALUES (?,?)", username, hash)
        return redirect("/login")
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    id = session["user_id"]
    if request.method == "POST":
        shares = request.form.get("shares")
        username = db.execute("SELECT username from users WHERE id=?",id)[0]["username"]
        cash = db.execute("SELECT cash from users WHERE id = ?", id)[0]["cash"]
        stock = lookup(request.form.get("symbol"))
        currShares = db.execute("SELECT shares from purchases WHERE id = ? AND symbol =? GROUP BY symbol", id,stock["symbol"])[0]["shares"]

        if not stock:
            return apology("stock symbol does not exist", 400)
        if not shares or int(shares) <= 0:
            return apology("shares must be a positive integer", 400)
        if int(shares) > currShares:
            return apology("You can not sell more shares than you have",400)
        if int(shares) < currShares:
            db.execute("UPDATE users SET cash=? WHERE id=?",cash+(stock["price"] * int(shares)),id)
            db.execute("INSERT INTO purchases (id, username, stock, symbol, price, shares) VALUES (?,?,?,?,?,?)", id, username, stock["name"], stock["symbol"], stock["price"], -int(shares))
            flash("Sold " + str(shares) + " " + stock["name"] + " stocks at " + str(stock["price"]) + " each")
        else:
            return apology("not enough cash to purchase stocks", 400)
        return redirect("/")
    else:
        symbols = db.execute("SELECT symbol from purchases WHERE id=? GROUP BY symbol",id)
        return render_template("sell.html",symbols=symbols)

@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    if request.method == "POST":
        id = session["user_id"]
        cashChange = request.form.get("cash")
        currCash = db.execute("SELECT cash from users WHERE id = ?", id)[0]["cash"]
        db.execute("UPDATE users SET cash=? WHERE id=?",currCash+float(cashChange),id)
        flash("Balance Updated!")
        return redirect("/cash")
    else:
        return render_template("cash.html")