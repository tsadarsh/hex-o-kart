from math import ceil
import requirements.xbox as xbox
from requirements.mqtt_client import Client
import time

joy = xbox.Joystick()         #Initialize joystick
c = Client()
c.connect()
last_time = time.time()
last_left = 0
last_right = 0
mode = 1

def pub(command, override=False):
    global last_time, last_cmd
    if time.time() - last_time > 1 or override == True or command != last_cmd:
        print(f"Publishing {command}")
        c.publish(command)
        last_time = time.time()
        last_cmd = command

while not joy.Back():
    if ceil(joy.rightTrigger()) != last_right:
        cmd = ceil(joy.rightTrigger()) + mode
        print("right: ", ceil(joy.rightTrigger() + mode))
        last_right = ceil(joy.rightTrigger())
        c.publish("/right_motor", cmd)

    if ceil(joy.leftTrigger()) != last_left:
        cmd = ceil(joy.leftTrigger()) + mode
        print("left: ", ceil(joy.leftTrigger() + mode))
        last_left = ceil(joy.leftTrigger())
        c.publish("/left_motor", cmd)


c.publish("/right_motor", cmd)
c.publish("/left_motor", cmd)

# x_axis   = joy.leftX()        #X-axis of the left stick (values -1.0 to 1.0)
# (x,y)    = joy.leftStick()    #Returns tuple containing left X and Y axes (values -1.0 to 1.0)
# trigger  = joy.rightTrigger() #Right trigger position (values 0 to 1.0)

joy.close()