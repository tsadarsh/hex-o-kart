from math import ceil
import requirements.xbox as xbox
from requirements.mqtt_client import Client
import time

def map_range(x, in_min, in_max, out_min, out_max):
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

def normalise(x):
    return format(int(abs(map_range(x, -2, 2, -1023, 1023))), '04d')

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
        jR = joy.rightStick()
        speed = jR[1]
        offset = jR[0]
        if speed > 0:
            diR = 2
            lM = normalise(speed + offset)
            rM = normalise(speed - offset)
        elif speed < 0:
            diR = 0
            lM = normalise(speed - offset)
            rM = normalise(speed + offset)
        else:
            diR = 1
            lM = format(0, '04d')
            rM = format(0, '04d')
        cmd = f'{diR},{lM},{rM}'
        last_pos = jR
        print("cmd: ", cmd)
        c.publish("/motor", cmd)


c.publish("/motor", "1,00,00")
# x_axis   = joy.leftX()        #X-axis of the left stick (values -1.0 to 1.0)
# (x,y)    = joy.leftStick()    #Returns tuple containing left X and Y axes (values -1.0 to 1.0)
# trigger  = joy.rightTrigger() #Right trigger position (values 0 to 1.0)

joy.close()