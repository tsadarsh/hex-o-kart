from math import ceil
import requirements.xbox as xbox
from requirements.mqtt_client import Client
import time

joy = xbox.Joystick()         #Initialize joystick
c = Client()
c.connect()
last_time = time.time()
last_pos = (0, 0)
mode = 1

def pub(command, override=False):
    global last_time, last_cmd
    if time.time() - last_time > 1 or override == True or command != last_cmd:
        print(f"Publishing {command}")
        c.publish(command)
        last_time = time.time()
        last_cmd = command

while not joy.Back():
    if joy.rightStick() != last_pos:
        right_joy = tuple(str(int(i)+1) for i in joy.rightStick())
        cmd = ''.join(right_joy)
        last_pos = joy.rightStick()
        print("cmd: ", cmd)
        c.publish("/motor", cmd)


c.publish("/motor", "11")
# x_axis   = joy.leftX()        #X-axis of the left stick (values -1.0 to 1.0)
# (x,y)    = joy.leftStick()    #Returns tuple containing left X and Y axes (values -1.0 to 1.0)
# trigger  = joy.rightTrigger() #Right trigger position (values 0 to 1.0)

joy.close()