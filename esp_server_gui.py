import controller

from gui import Gui

gui = Gui()
window = gui.create_window()

s = controller.Sender()
s.connect()
while gui.READY:
	gui.event_loop(window)
	message = gui.MESSAGE
	s.publish(message)