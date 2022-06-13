import paho.mqtt.client as mqtt
from random import randint

client_id = 'user_'+str(randint(1, 1000000000))+'tsa'

client = mqtt.Client(client_id=client_id)
client.connect("broker.mqttdashboard.com")

message = "python"+client_id
client.publish("/swa/commands", message)
# Loop needed as per https://stackoverflow.com/a/47726934/12808184
client.loop()

print(f"{client_id} is publishing: {message}")