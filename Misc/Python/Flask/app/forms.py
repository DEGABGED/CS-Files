from flask.ext.wtf import Form
from wtforms import StringField, PasswordField, BooleanField, validators

class LoginForm(Form):
    username = StringField('username', [validators.Length(min=8, max=25), validators.Required()])
    password = PasswordField('password', [validators.Length(min=8), validators.Required()])
    remember_me = BooleanField('remember_me', default=False)

class SignUpForm(Form):
    username = StringField('Username', [validators.Length(min=8, max=25)])
    password = PasswordField('New Password', [
        validators.Length(min=8),
        validators.Required(),
        validators.EqualTo('confirm', message='Passwords must match')
    ])
    confirm = PasswordField('Repeat Password')
