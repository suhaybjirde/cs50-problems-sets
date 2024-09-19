
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True
app.secret_key = "secretkey"

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_reqest(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

def is_exists_in_db(id):
    row = db.execute("SELECT id FROM birthdays WHERE id = ?", id)
    return (True if len(row) == 1 else False)

def valide_data(name, month, day, id=None): 
    if not isinstance(name, str):
        return False
    if not (1 <= month <= 12):
        return False
    if not (1 <= day <= 31):
        return False
    if id is not None:
        if not isinstance(id, int):
            return False
        if not is_exists_in_db(id):
            return False
    return True
    

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        try:
            name = request.form.get('name')
            month = int(request.form.get("month"))
            day = int(request.form.get("day"))
            valide_data(name=name, month=month, day=day)
            if valide_data(name=name, month=month, day=day): 
                db.execute("INSERT INTO birthdays(name, month, day) VALUES(?,?,?)",name, month, day)
                flash("successfully Added.", 'success')
            else:
                flash("you provided inviled data", 'error')
            return redirect("/")
        except ValueError:
            flash("type Error")
            return redirect('/')

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)

@app.route('/delete', methods=['POST'])
def delete_birthday():
    if request.is_json:
        data = request.get_json()
        try:
            id = int(data.get('id'))
            if is_exists_in_db(id):
                db.execute("DELETE FROM birthdays WHERE id = ?", id)
            else:
                return jsonify({'error': 'provide valid id'}), 400
        except ValueError:
            return jsonify({'error': 'provide valid id'}), 400
        response = {
            'success': 'deleted successfully',
            'id': id
        }
        return jsonify(response), 200
    else:
        return jsonify({'error': 'request must be json'}), 400


@app.route('/update', methods=['POST'])
def update(): 

    if request.is_json:
        try:
            data = request.get_json()
            id = int(data.get('id'))
            name = data.get('name')
            month = int(data.get('month'))
            day = int(data.get('day'))

            if valide_data(name=name, month=month, day=day, id=id):
                db.execute("UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?", name, month, day, id)
                response = {
                    'success': 'updated successfully',
                    'id': id
                }
                return jsonify(response), 200
            else:
                return jsonify({'error': 'you provided inviled data'}), 400
        except ValueError:
                response = {
                    'error': 'inviled Date',
                }
                return jsonify(response), 400
    else:
        return jsonify({'error': 'request must be json'}), 400

if __name__ == '__main__':
    app.run(debug=True)     