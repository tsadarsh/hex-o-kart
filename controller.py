import paho.mqtt.client as mqtt
from random import randint
import time

from gui import Gui

class Sender:
	"""Class to publish message to MQTT broker

	First connect to server by calling `connect` method. Then publish
	Publish message by calling `publish` method and passing the message 
	as argument. 
	"""

	def _create_unique_client_id(self):
		client_id = 'user_'+str(randint(1, 1000000000))+'_tsa'
		return client_id

	def connect(self):
		self.client = mqtt.Client(client_id=self._create_unique_client_id())
		self.client.connect("broker.mqttdashboard.com")

	def publish(self, message):
		self.client.publish("/swa/commands", message)
		# Loop needed as per https://stackoverflow.com/a/47726934/12808184
		self.client.loop()

		print(f"publishing: {message}")
		time.sleep(0.1)

class Receiver:
	pass