import PySimpleGUI as sg


class Gui:
	def __init__(self):
		sg.theme('DarkAmber')
		self.FORWARD = '10'
		self.STOP    = '00'
		self.REVERSE = '01'
		self.STATUS = '00'

	def start(self):
		layout = [
			[
				sg.Button(self.FORWARD),
				sg.Button(self.STOP),
				sg.Button(self.REVERSE),
				sg.Button('Cancel')
			]
		]

		window = sg.Window('GUI', layout)

		while True:
			event, values = window.read()
			if event == sg.WIN_CLOSED or event == 'Cancel':
				self.kill(window)
				break
			else:
				self.STATUS = event
				print(self.STATUS)

	def kill(self, window):
		window.close()