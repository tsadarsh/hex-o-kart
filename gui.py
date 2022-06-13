import PySimpleGUI as sg


class Gui:
	def __init__(self):
		sg.theme('DarkAmber')
		self.FORWARD = '10'
		self.STOP    = '00'
		self.REVERSE = '01'
		self.STATUS = '00'
		self.READY = False

	def create_window(self):
		layout = [
			[
				sg.Button(self.FORWARD),
				sg.Button(self.STOP),
				sg.Button(self.REVERSE),
			]
		]

		window = sg.Window('GUI', layout)
		self.READY = True

		return window

	def event_loop(self, window):
		event, values = window.read()
		if event == sg.WIN_CLOSED or event == 'Cancel':
			self.kill(window)
			self.STATUS = self.STOP
			self.READY = False
		else:
			self.STATUS = event

	def kill(self, window):
		window.close()