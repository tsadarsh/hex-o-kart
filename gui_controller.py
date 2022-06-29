from mqtt_client import Client

from gui import Gui

gui = Gui()
window = gui.create_window()

c = Client()
c.connect()


while gui.READY:
	gui.event_loop(window)
	message = gui.MESSAGE
	c.publish(message)
	c.subscribe(
		[
			"/swa/encoder/left",
			"/swa/encoder/right"
		]
	)
	gui.left_encoder = c.left_encoder
	gui.right_encoder = c.right_encoder