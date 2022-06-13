import paho.mqtt.client as mqtt
from random import randint
import time

from gui import Gui

gui = Gui()
w = gui.create_window()

def create_unique_client_id():
	client_id = 'user_'+str(randint(1, 1000000000))+'_tsa'
	return client_id

client = mqtt.Client(client_id=create_unique_client_id())
client.connect("broker.mqttdashboard.com")

while gui.READY:
	gui.event_loop(w)
	message = gui.STATUS
	client.publish("/swa/commands", message)
	# Loop needed as per https://stackoverflow.com/a/47726934/12808184
	client.loop()

	print(f"publishing: {message}")
	time.sleep(0.1)