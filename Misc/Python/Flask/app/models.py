from app import db

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    user_name = db.Column(db.String(64), index=True, unique=True)
    user_pass = db.Column(db.String(64), index=True)

    def __repr__(self):
        return '<User %r>' % (self.user_name)
