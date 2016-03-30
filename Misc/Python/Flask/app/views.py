from flask import render_template, flash, redirect
from app import app
from .forms import LoginForm, SignUpForm

@app.route('/')
@app.route('/index/')
def index():
    user = {'name' : 'Francis'}
    events = [
        {
            'name' : 'DevCamp',
            'venue' : 'UP AECH',
            'desc' : 'A camp for developers'
        },
        {
            'name' : 'HackUP',
            'venue' : 'GT Toyota',
            'desc' : 'A hackathon'
        },
        {
            'name' : 'Culmi',
            'venue' : 'UP AECH',
            'desc' : 'A teambuilding activity'
        }
    ]
    return render_template('index.html', title='Home', user=user, events=events)

@app.route('/login/', methods=['GET', 'POST'])
def login():
    form = LoginForm()
    if form.validate_on_submit():
        flash('Login requested for Username="%s", Password=%s, remember_me=%s' %
              (form.username.data, form.password.data, str(form.remember_me.data)))
        return redirect('/index')
    return render_template('login.html', title='Sign In', form=form)

@app.route('/signup/', methods=['GET', 'POST'])
def signup():
    form = SignUpForm()
    if form.validate_on_submit():
        flash('Signup requested for Username="%s", Password=%s' %
              (form.username.data, form.password.data))
        return redirect('/index')
    return render_template('signup.html', title='Sign Up', form=form)
