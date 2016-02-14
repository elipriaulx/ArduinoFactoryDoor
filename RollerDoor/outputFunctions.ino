#define DEBOUNCE_TIME 250
#define MAX_THRESHOLD 500
#define MIN_THRESHOLD 1

#include <arduino.h>
#include "RollerDoorTypes.h"

void UpdateOutput(Output * output)
{
	// Write the output buffer
	digitalWrite(output->pin, output->currentState == output->activeState);
}

void InitialiseOutput(Output * output)
{
	pinMode(output->pin, OUTPUT);
	UpdateOutput(output);
}

void SetOutput(Output * output, bool state)
{
	output->currentState = state;
}
