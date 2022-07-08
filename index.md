## Introduction
HEX-O-CART(HOC) is a two-wheeled hexagonal-shaped robot capable of autonomous navigation and lidar mapping. HOC can be a DIY project for any hobbyist with basic electronics and coding knowledge. This guide explains the build process and serves as documentation for the HEX-O-CART.

## TL;DR
The body of HOC can be 3d printed. The STL files for HOC are in the `body/` directory in the Github [repository](https://github.com/tsadarsh/hex-o-kart). Other components that are required to build the bot are listed below:

| Component | Quantity | Buy            |
| ------------ | --------- | ---------- |
| ESP-8266 | 1 | [affliates] |
| Raspberry Pi 3/3B/4 | 1 | [link] |
| L298n Motor driver | 1 | [affiliate] |
| Wheel encoders | 2 | [affiliate] |
| Battery level indicator | 1 | [affiliate] |
| Connecting wires |  | [affliate]|
| 3S battery | 1 | [affliate] |
| Lidar | 1 | [affliate] |

These are the following parts that need to be 3D-printed. If you do not have access to a 3D printed you can request a printed model from us [here]. You can also go with other vendors; we recommend [affliates]

The following C++ code contains the logic to drive the motor when messages are received and also counts the number of wheel ticks. The ESP communicates with the Raspberry Pi using the UART protocol. ROS publishes the lidar data as a `sensor_msgs` topic. We can subscribe and visualise the topic on our laptop by connecting to the [same network](ros-on-multiple-machines).

[Code for ESP]
[Code for ROS]

Upload the code to the ESP8266 microcontroller, start `roscore` and launch the `hoc_start.launch` file. The brain of HOC is ready now. Now we need to wire up the motor driver with the microcontroller. Follow the circuit diagram given below:

[Image - circuit diagram]

Next, let us place the motors and wire the encoder feedback to the microcontroller. The circuit diagram is given below:

[Image - circuit diagram]

Fix the motor clamps and hot-glue the motor driver and microcontroller. Your HOC is now lacking only a power supply. Attach a 3s battery and wrooomm...

## Detailed Guide

### Basics
#### Why an ESP8266 microcontroller?
#### Why a Raspberry Pi?
#### 3.3V and 5V logic
#### Communication - ROS on multiple machines
#### Joystick

### 3D printing
#### How to view the STL files?
#### Slicing
#### Material and bed temperature

### Coding
#### Installing ESP8266 board manager
#### Basics of setup and loop
#### Interrupts
#### Establishing Wifi connection
#### Seting up MQTT
#### Publish and subscribe to topics
#### OTA (not-required)
#### Joystick input
#### GUI output
#### Setting up ROS
#### Publishing the topics
#### Subscribing to topics
#### Feedback control

### Circuit
#### Tools required
#### Stripping wires
#### Soldering
#### Making the circuit on a dot board
#### Power supply
#### Common grounding

### Testing
### Additional goals
