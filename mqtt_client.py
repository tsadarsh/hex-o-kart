import paho.mqtt.client as mqtt
from random import randint
import time


class Client:
	"""Class to publish message to MQTT broker

	First connect to server by calling `connect` method. Then publish
	Publish message by calling `publish` method and passing the message 
	as argument. 
	"""

	def __init__(self):
		self.left_encoder = 0
		self.right_encoder = 0

	def connect(self):
		"""Create a client and connects to MQTT broker"""
		self.client = mqtt.Client(client_id=self._create_unique_client_id())
		self.client.connect("broker.mqttdashboard.com")

	def _create_unique_client_id(self):
		"""Creates unique client ID to connect to MQTT broker"""
		client_id = 'user_'+str(randint(1, 1000000000))+'_tsa'
		return client_id

	def loop_start(self):
		self.client.loop_start()

	def publish(self, message):
		self.client.publish("/swa/commands", message)
		# Loop needed as per https://stackoverflow.com/a/47726934/12808184
		self.client.loop(.1)

		#print(f"publishing: {message}")
		#time.sleep(0.1)

	def subscribe(self, topics: list):
		"""Subscribes to topics in `topics` argument"""
		for topic in topics:
			self.client.subscribe(topic)
		self.client.on_message = self._on_message
		self.client.loop(.1)

	def _on_message(self, client, userdata, message):
		"""Callback function of `client.subscribe`"""
		if message.topic == "/swa/encoder/left":
			#print(message.payload)
			self.left_encoder = message.payload.decode("utf-8")

		if message.topic == "/swa/encoder/right":
			#print(message.payload)
			self.right_encoder = message.payload.decode("utf-8")
			

