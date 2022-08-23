from flask import Flask,render_template,request

app = Flask(__name__)

SPORTS = [
        "Tennis",
        "Foot ball",
        "Hand ball"
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def check():
    if not request.form.get("name") or request.form.get("sport") not in SPORTS:
        return render_template("faliure.html")
    return render_template("success.html")
