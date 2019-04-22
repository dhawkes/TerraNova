# TerraNova

![terra_nova_logo](/Images/terranova.png)

Welcome to TerraNova's repository ! This project was made by a team of Mechanical engineering and Robotic's student in collaboration with NASA at the University of Pennsylvania.  
  
The objective of the TerraNova project is to enable the exploration of uncharted lunar subterranean spaces. TerraNova developed a hybrid a jumping and wheeled mechanical robot to spring over boulder fields and efficiently navigate dark caverns.  
TerraNova’s spring-based jumping mechanism exerts 215 lbs to launch the robot to a height of 1 meter under lunar gravity. TerraNova has four-wheel drive and front wheel differential steering. An active rocker suspension system, a novel application of advanced motor control, ensures that all four wheels remain in even contact with the surface. This functionality all fits within a robot weighing less than 20 lbs.

![moon_rover](/Images/moon_rover.jpg)

## Overview

The TerraNova system involves an extensive software suite, including the custom embedded libraries onboard the robot, the desktop GUI and a data processing system. The embedded side was written in C++ for the teensy 3.6 using the Arduino IDE while the desktop side was developed in C# with the .NET framework and Windows Forms.  

### Embedded Software

The embedded software side includes libraries for controlling and reading data from each of the electronic components of the rover using a teensy 3.6. It also handles the custom data processing and communication system on the rover side by interfacing with a Xbee radio module.

### Desktop Software

The desktop software deals with sending commands and receiving data from the robot, as well as processing, displaying, logging and visualizing this data. This includes processing communication with an XBee module and reading commands from and Xbox One controller. Windows Forms and the .NET framework was used to develop a graphical user interface (GUI).


## Can I Use This Code

Unfortunatly this code was designed and tested to work with our TerraNova robot and is not meant to work with any other system. But feel free to take any part of it that you may found useful !

## Authors

* **Dylan Hawkes** - *Initial work* - [dhawkes36](https://github.com/dhawkes36)

* **Raphael Van Hoffelen** - *Initial work* - [dskart](https://github.com/dskart)


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
