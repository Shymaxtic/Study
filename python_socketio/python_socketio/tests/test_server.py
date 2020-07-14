import sys, pprint, os
sys.path.append(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
# pprint.pprint(sys.path)
from python_socketio.application.server_application import ServerApplication


if __name__ == '__main__':
    ServerApplication.instance().start()