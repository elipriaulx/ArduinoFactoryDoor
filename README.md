# ArduinoFactoryDoor

## Overview
This project was composed, to allow the functionality of an existing factory roller door to be expanded, adding remote control, auto-traverse, and safety features. 

## Getting Started
This project is written for the Arduino Uno, using the Arduino IDE, and refactored into a Visual Studio Visual Micro project. This project will still open and build in the Arduino IDE, however, for the best experience Visual Micro is recommended.
 - [Arduino IDE](https://www.arduino.cc/)
 - [Visual Studio](https://www.visualstudio.com/)
 - [Visual Micro](http://www.visualmicro.com/)
 - [Fritzing](http://fritzing.org/home/)

## Existing Implementation
The existing door featured:
 - An UP button, to drive the door up. The door would continue upwards on its own until the limit switches broke the drive circuit, or the stop button was pressed.
 - A STOP button, which stopped the door from operating if auto-traversing. It also prevented any further operation of the door whilst active.
 - A DOWN button, which when held, would drive the door downward.
 - Limit Switches, to prevent the door from over-driving and damaging itself, property, or persons. 
 - Motor, to perform all movement operations.
 - Chain Drive, to use in case of emergencies or power/electrics failure. 

## New Implementation
The new system features:
 - An UP button which auto-traverses the door until its limit switch activates. 
 - A STOP button to stop the door, regardless of state.
 - A DOWN button to auto-traverse the door down untill its limit switch activates.
 - Limit switches, to ensure the door doesn't overdrive.
 - Remote Controls, which allow the door to drive up, or down, without contact by the user.
 - Reed switch, allowing the system to know when the door is closed.
 - Break Beam, ensuring door downward operation is disabled when obstructed.

## Additional Notes
 - The limit switches are not integrated with the automation system. Without extensive testing, it would be nieve to compromise the last line of defence against damage in the case of system malfunction, and assume all cases are catered for. 
 - Because limit switches are not integrated, and the system has no awareness of the position of the door, the system will attempt to drive the door in the nominated direction for an arbitrary time period, ensuring that it travels the desired distance.
 - The door must compress slightly when closed, for this reason, when the reed switch is activated, the door isn't assumed to be closed.
 - The remote button won't toggle the drive direction of the door. This was by design, but may change in the future. Instead, the remote button will attempt to drive the door upward, only if the door is currently in the down position. It will drive the door downward if the door is in any other position. If the door is traveling, or the traversal timer is still counting, the button will simply stop the operation.

## Hardware
Works should only be conducted on fixed electrical installations by trained and licensed individuals. Lack of care taken whilst working on this or similar systems has a high probability of resulting in death or injury. I did not perform the integration work for this project; my role was limited to producing the code necessary to support the desired use case. I have included a schematic file better communicate the hardware design, however this is non authoritive.

More information at [gpriaulx.co](http://gpriaulx.co)