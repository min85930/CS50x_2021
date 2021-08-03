import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        MONTHS = [str(i) for i in range(1, 13)]
        DAYS = [str(i) for i in range(1, 32)]

        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        message = ""
        results = db.execute("Select * FROM birthdays")

        if not name:
            message = "Please enter your name."

        elif not month or month not in MONTHS:
            message = "Please enter correct month."

        elif not day or day not in DAYS:
            message = "Please enter correct day."

        if message != "":
            return render_template("index.html", results=results, message=message)

        db.execute("INSERT INTO birthdays(name, month, day) values(?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        results = db.execute("Select * FROM birthdays")
        return render_template("index.html", results=results)

