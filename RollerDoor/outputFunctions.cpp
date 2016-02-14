#include "outputFunctions.h"
#include <arduino.h>

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
