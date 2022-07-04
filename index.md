## Introduction
HEX-O-CART(HOC) is a two-wheeled hexagonal-shaped robot capable of performing autonomous navigation and lidar mapping. HOC can be a DIY project for any hobbyist with basic electronics and coding knowledge. This guide explains the build process and serves as documentation for the HEX-O-CART.

## TL;DR
The body of HOC can be 3d printed. The STL files for HOC are contained in the `body/` directory in the Github [repository](https://github.com/tsadarsh/hex-o-kart). Other components that are required to build the bot are listed below:

| Component | Quantity | Buy            |
| ------------ | --------- | ---------- |
| ESP-8266 | 1 | [affliates] |
| L298n Motor driver | 1 | [affiliate] |
| Connecting wires |  | [affliate]|
| 3S battery | 1 | [affliate] |

These are the following parts that need to be 3D-printed. If you do not have access to a 3D printed you can request a printed model from us [here]. You can also go with other vendors; we recommend [affliates]

The following C++ code contains the logic to drive the motor when messages are received and also counts the number of wheel ticks. Messages are transmitted and received using the MQTT subscriber-receiver model. You will be using a joystick connected to your laptop/computer and be able to control the HOC.

[Code]

Upload the code to the ESP8266 microcontroller. The brain of HOC is ready now. Now we need to wire up the motor driver with the microcontroller. Follow the circuit diagram given below:

[Image - circuit diagram]

Next, let us place the motors and wire up the encoder feedback to the microcontroller. The circuit diagram is given below:

[Image - circuit diagram]

Fix the motor clamps and hot-glue the motor driver and microcontroller. Your HOC is now lacking only a power supply. Attach a 3s battery and wrooomm...

## Detailed Guide

### Basics
#### Why an ESP8266 microcontroller?
#### 3.3V and 5V logic
#### Communication - MQTT
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

### Circuit
#### Tools required
#### Stripping wires
#### Soldering
#### Making the circuit on a dot board
#### Power supply
#### Common grounding

### Testing
### Additional goals
 
