# ArduinoFactoryDoor
An Arduino sketch to retrofit a remote control and break beam to an existing factory roller door. 

This code was written to suit a door which featured three buttons, and implements limit switches, which break the drive circuit to the motor. Three buttons controlled the door in its original implementation. The Up button would drive the door up automatically untill the limit switch was engaged, the down button would only drive the door down if held, and the stop button would stop the door from travelling upwards. 

These consequently were replaced with 3 relays; one to action each button. Note that the STOP button was normally closed, and broke the 'enable' circuit when actuated. This translated to an 'Enable' relay which is activated to perform any operation, in addition to the direction of desired travel. 

See the Fritzing diagram for more perspective on how the implementation is put together. 

Care should be taken when working with high voltages.