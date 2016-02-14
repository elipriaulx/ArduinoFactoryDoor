#ifndef _INPUTFUNCTIONS_H_
#define _INPUTFUNCTIONS_H_

#define DEBOUNCE_TIME 250
#define MAX_THRESHOLD 500
#define MIN_THRESHOLD 1

#include "rollerDoorTypes.h"

void UpdateInput(Input * input, unsigned long * interval);
bool ButtonPressed(Input * input);
bool ButtonReleased(Input * input);
bool InputActive(Input * input);
bool InputInactive(Input * input);
void InitialiseInput(Input * input);

#endif