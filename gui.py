import PySimpleGUI as sg


class Gui:
	def __init__(self):
		sg.theme('DarkAmber')
		self.FORWARD = '10'
		self.STOP    = '00'
		self.REVERSE = '01'
		self.MESSAGE = '00'
		self.READY = False
		self.left_encoder = 0
		self.right_encoder = 0

	def create_window(self):
		layout = [
			[
				sg.Text('0', key='left_encoder'),
				sg.Text('0', key='right_encoder'),
				sg.Button(self.FORWARD),
				sg.Button(self.STOP),
				sg.Button(self.REVERSE),
			]
		]

		self.window = sg.Window('GUI', layout)
		self.READY = True

		return self.window

	def event_loop(self, window):
		event, values = window.read(timeout = 10)
		if event == sg.WIN_CLOSED or event == 'Cancel':
			self.kill(window)
			self.MESSAGE = self.STOP
			self.READY = False
		else:
			if event != "__TIMEOUT__":
				self.MESSAGE = event
			self.window['left_encoder'].update(self.left_encoder)
			self.window['right_encoder'].update(self.right_encoder)
	
	def kill(self, window):
		window.close()