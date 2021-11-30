CAN VEHICLE EMULATOR
========
## Description
This project simulates an engine and a gearbox. The user can start/stop the engine, gas, change gear pindle position etc. The information will be sent on CAN to the transmission (called reo in this project) in which the engine and gearbox will be emulated. The output of the engine/gearbox will be sent over CAN to an AVIC which displays the information in nice way.

- AVIC: Alten Virtual Instrument Cluster
- Inputhandler: Takes inputs from keyboard, and sensd it over CAN.
- REO: Read Emulator Output, reads data through CAN from Inputhandler, emulates engine and gearbox and outputs it over CAN to AVIC.
- hal: Hardware Abstraction Layer, abstracts hardware e.g. CAN from applications.

## Coding Convention
- Google Style
- Volvo Cars coding guide line.

## Running project

#### 1. Install dependecy
```
apt install 
    qt5-default
    qtdeclarative5-dev
    qtquickcontrols2-5-dev
    libgles2-mesa-dev
    qml-module-qtquick-controls
    qml-module-qtquick-extras
```

#### 2. Run build script from tools folder
```
./build.sh
```

#### 3. Then start up VCAN0 from tools folder
```
./set_up_vcan.sh
```
#### 4. Run the binaries located in build folder 
```
./input_handler.out
./reo.out
./avic.out -c vcan0
```