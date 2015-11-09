BaseStation
===========
This directory contains all of the code for the base station, including the BaseStationComms ADLC and the PayloadGUI.

**BaseStationComms**
--- Establishes and maintains a network connection between the Base Station and the Payload. Tracks changes from the PayloadGUI and transmits packets to the payload. Also accepts incoming packets from the payload and alerts the PayloadGUI.

**PayloadGUI**
--- The main interface for controlling the payload. Gives the user an intuitive graphical interface with which to establish a network connection and control critical payload functionality such as starting camera capture and ADLC. Also has the capability to scan through the images transmitted back to the Base Station.

**ADLC**
--- All of the image processing code running on the base station.

**Base Station Layout**
![Class Diagram](../Documentation/BaseStation.png?raw=true "Class Diagram")


