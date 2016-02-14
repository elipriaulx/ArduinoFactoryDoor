#include <arduino.h>
#include "RollerDoorTypes.h"

#define MAX_TRAVEL_TIME 25000

// State Management
enum OperationalStates
{
	Unknown,
	DoorUp,
	DoorDown,
	DoorRaising,
	DoorLowering
};

OperationalStates doorState = Unknown;

// Inputs (second last param is active state)
Input buttonUp = { 4, false, false, LOW, 0 };
Input buttonDown = { 3, false, false, LOW, 0 };
Input buttonStop = { 5, false, false, HIGH, 0 };
Input buttonRemote = { 6, false, false, LOW, 0 };
Input safetyBreakBeam = { 7, false, false, LOW, 0 };
Input closedReedSwitch = { 2, false, false, LOW, 0 };

// Outputs (last param is active state)
Output actionUp = { 8, false, HIGH };
Output actionDown = { 9, false, HIGH };
Output actionEnable = { 10, false, HIGH };
Output indicator = { 13, false, HIGH };

// Timer
unsigned long previousTime = 0;
unsigned long currentTime = 0;
unsigned long intervalTime = 0;
unsigned long travelTime = 0;

void setup() {
	InitialiseInput(&buttonUp);
	InitialiseInput(&buttonDown);
	InitialiseInput(&buttonStop);
	InitialiseInput(&buttonRemote);
	InitialiseInput(&safetyBreakBeam);
	InitialiseInput(&closedReedSwitch);

	InitialiseOutput(&actionUp);
	InitialiseOutput(&actionDown);
	InitialiseOutput(&actionEnable);
	InitialiseOutput(&indicator);
}

void Update()
{
	// Timer
	previousTime = currentTime;
	currentTime = millis();
	intervalTime = currentTime - previousTime;

	// Inputs
	UpdateInput(&buttonUp, &intervalTime);
	UpdateInput(&buttonDown, &intervalTime);
	UpdateInput(&buttonStop, &intervalTime);
	UpdateInput(&buttonRemote, &intervalTime);
	UpdateInput(&safetyBreakBeam, &intervalTime);
	UpdateInput(&closedReedSwitch, &intervalTime);

	// Outputs
	UpdateOutput(&actionUp);
	UpdateOutput(&actionEnable);
	UpdateOutput(&actionDown);
	UpdateOutput(&indicator);
}

void loop() {

	// Refresh timer, and IO
	Update();

	switch (doorState)
	{
	case DoorUp:

		travelTime = 0;

		// Stop the machines!
		SetOutput(&actionUp, false); // Don't go up.
		SetOutput(&actionDown, false); // Don't go down.
		SetOutput(&actionEnable, false); // Stop everything
		SetOutput(&indicator, false); // Indicator off.

									  // Door is in some arbitrary position that isn't down. If remote, or down is pressed, go down if beam ok. 
		if ((ButtonPressed(&buttonRemote) || ButtonPressed(&buttonDown)) && InputInactive(&safetyBreakBeam)) doorState = DoorLowering;
		if (ButtonPressed(&buttonUp)) doorState = DoorRaising;

		if (InputActive(&closedReedSwitch)) doorState = DoorDown;

		break;

	case DoorDown:

		travelTime = 0;

		// Stop the machines!
		SetOutput(&actionUp, false); // Don't go up.
		SetOutput(&actionDown, false); // Don't go down.
		SetOutput(&actionEnable, false); // Stop everything.
		SetOutput(&indicator, false); // Indicator off.

									  // Check Remote & Up Button, but ignore if stop button is being held in
		if ((ButtonPressed(&buttonRemote) || ButtonPressed(&buttonUp)) && InputInactive(&buttonStop)) doorState = DoorRaising;

		break;

	case DoorRaising:

		travelTime += intervalTime;

		// Configure switcherisers!
		SetOutput(&actionUp, true); // Go up.
		SetOutput(&actionDown, false); // Don't go down.
		SetOutput(&actionEnable, true); // Don't stop.
		SetOutput(&indicator, true); // Indicator On.

									 // Check for another button press to stop operation.
		if (ButtonPressed(&buttonDown) || ButtonPressed(&buttonStop) || ButtonPressed(&buttonRemote)) doorState = DoorUp;

		if (travelTime >= MAX_TRAVEL_TIME) doorState = DoorUp;

		break;

	case DoorLowering:

		travelTime += intervalTime;

		// Configure switcherisers!
		SetOutput(&actionUp, false); // Don't go up.
		SetOutput(&actionDown, true); // Go down.
		SetOutput(&actionEnable, true); // Don't stop.
		SetOutput(&indicator, false); // Indicator off.

									  // Check Remote & Up Button, but ignore if stop button is being held in, and check beam
		if ((ButtonPressed(&buttonRemote) || ButtonPressed(&buttonUp) || ButtonPressed(&buttonStop)) || InputActive(&safetyBreakBeam)) doorState = DoorUp;

		if (travelTime >= MAX_TRAVEL_TIME) doorState = DoorDown;

		break;

	default:
		// Unknown location, determine... Must be UP (or half way) because otherwise the reed switch would have put us in a down state automagically!
		doorState = DoorUp;

		break;
	}
}
