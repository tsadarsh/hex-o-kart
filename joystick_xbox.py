import requirements.xbox as xbox
from requirements.mqtt_client import Client
import time

joy = xbox.Joystick()         #Initialize joystick
c = Client()
c.connect()
last_time = time.time()
last_cmd = '00'

def pub(command, override=False):
    global last_time, last_cmd
    if time.time() - last_time > 1 or override == True or command != last_cmd:
        print(f"Publishing {command}")
        c.publish(command)
        last_time = time.time()
        last_cmd = command

while not joy.Back():
    if joy.A():                   #Test state of the A button (1=pressed, 0=not pressed)
        pub('01')
    if joy.Y():
        pub('10')


pub('00', override=True)

# x_axis   = joy.leftX()        #X-axis of the left stick (values -1.0 to 1.0)
# (x,y)    = joy.leftStick()    #Returns tuple containing left X and Y axes (values -1.0 to 1.0)
# trigger  = joy.rightTrigger() #Right trigger position (values 0 to 1.0)

joy.close()