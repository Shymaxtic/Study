import sys
import sys, pprint, os
sys.path.append(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
from python_socketio.application.client_application import ClientApplication

client = ClientApplication.instance()


client.start('http://localhost:5000')