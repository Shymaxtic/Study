import gevent
from gevent import pywsgi
import socketio, traceback
from pprint import pprint

class ServerApplication:
    """
        Server Application monitoring data from vps client.
    """
    __instance              = None
    sio = socketio.Server(async_mode='gevent')
    app = socketio.WSGIApp(sio)

    def __init__(self):
        if ServerApplication.__instance is not None: raise Exception('Sigleton Error')
        else:
            ServerApplication.__instance    = self

    @staticmethod
    def instance():
        if ServerApplication.__instance is None: ServerApplication()
        return ServerApplication.__instance


    @staticmethod
    def background_check_waiting_client():
        """
            Check state of wating client, reject the client if it waits too long.
            This is background task
        """
        while True:
            ServerApplication.sio.sleep(60)

    @staticmethod
    @sio.event
    def connect(sid, environ):
        """
            event occurs when client has connected.
        """
        print('client connected:', sid)
        pprint(environ)

    @staticmethod
    @sio.event
    def disconnect(sid):
        """
            event occurs when client has disconnected
        """
        print('disconnected', sid)

    @staticmethod
    @sio.event
    def on_client_message(sid, data):
        """
            event occurs when client has sent a message
        """
        #print('on_client_message', sid, data)
        print(data)

    def start(self, **kwargs):
        print('started local server')
        pywsgi.WSGIServer(('', 5000), ServerApplication.app, log=None).serve_forever()
        
        
