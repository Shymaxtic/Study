import socketio, random, sys, time, threading
from collections import deque

class ClientApplication:
    __instance              = None
    sio                     = socketio.Client()

    def __init__(self):
        if ClientApplication.__instance is not None: raise Exception('Sigleton Error')
        else:
            super().__init__()
            self.mPrivateKey                = None
            self.mIsRunning                 = False 
            self.mDataQueueLocker           = threading.Lock()
            self.mDataQueue                 = deque()
            ClientApplication.__instance    = self

    @staticmethod
    def instance():
        if ClientApplication.__instance is None: ClientApplication()
        return ClientApplication.__instance

    @staticmethod
    @sio.event
    def connect():
        """
            client connect to server
        """
        print('connection established')
        # ClientApplication.sio.emit(event='on_client_message', 
                                    # data=data_pkg)

    @staticmethod
    @sio.event
    def disconnect():
        """
            client disconnect from server
        """
        print('disonnected from server')
        #TODO: disconnect handler

    @staticmethod
    @sio.event
    def on_server_message(data):
        """
            server send message to this client
        """
        print(data)

    def start(self, server_address, **kwargs):
        print('start', threading.get_ident())
        self.mIsRunning = True
        ClientApplication.sio.connect(server_address)
        # ClientApplication.sio.wait()

    def stop(self, **kwargs):
        #TODO: disconnect
        self.mIsRunning = False
        ClientApplication.sio.disconnect()

    def background_task(self):
        # print('background_task', threading.get_ident())
        while self.mIsRunning:
            time.sleep(1)
