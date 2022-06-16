from controller import Controller

from gui import Gui

gui = Gui()
window = gui.create_window()

c = Controller()
c.connect()

c.subscribe(
	[
		"/swa/encoder/left",
		"/swa/encoder/right"
	]
)

while gui.READY:
	gui.event_loop(window)
	message = gui.MESSAGE
	c.publish(message)