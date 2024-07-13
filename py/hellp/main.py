import flask

if __name__ == '__main__':
    app = flask.Flask(__name__)

    @app.route('/')
    def index():
        return 'Hello, World!'

    app.run()
