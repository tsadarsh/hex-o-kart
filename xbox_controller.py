import xbox
from controller import Controller
import time

joy = xbox.Joystick()         #Initialize joystick
c = Controller()
c.connect()
l = time.time()

def pub(command, override=False):
    global l
    if time.time() - l > 1 or override == True:
        print(f"Publishing {command}")
        c.publish(command)
        l = time.time()

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