import PySimpleGUI as sg

sg.theme('DarkAmber')

FORWARD = '^'
STOP    = 'O'
REVERSE = 'v'

layout = [
	[
		sg.Button(FORWARD),
		sg.Button(STOP),
		sg.Button(REVERSE),
		sg.Button('Cancel')	
	]
]

window = sg.Window('GUI', layout)

while True:
	event, values = window.read()
	if event == sg.WIN_CLOSED or event == 'Cancel':
		break
	if event == FORWARD:
		print("Going forward")
	if event == STOP:
		print("Stopping")
	if event == REVERSE:
		print("Going reverse")

window.close()