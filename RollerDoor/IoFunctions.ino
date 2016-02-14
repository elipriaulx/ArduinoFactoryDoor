#define DEBOUNCE_TIME 250
#define MAX_THRESHOLD 500
#define MIN_THRESHOLD 1

#include "Types.h"

// --------------------------------------------------------------------------------
// Output Functions
// --------------------------------------------------------------------------------

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

// --------------------------------------------------------------------------------
// Input Functions
// --------------------------------------------------------------------------------

void UpdateInput(Input * input, unsigned long * interval)
{
  input->previousState = input->currentState;
    
  // Check if a debounce is underway
  if (input->debounce <= 0)
  {
    // If not, update inputs
    input->currentState = digitalRead(input->pin) == input->activeState;

    // If state changed, so start a debounce
    if (input->previousState != input->currentState) input->debounce = DEBOUNCE_TIME;
  }
  else
  {
    // This accounts for irregularities in the time taken to loop through the main program
    int dTime = (int) (*interval);
    if (dTime > MAX_THRESHOLD || dTime < MIN_THRESHOLD) dTime = MIN_THRESHOLD;

    // Count the loop time towards the debounce
    input->debounce -= dTime;
  }
}

bool ButtonPressed(Input * input)
{
  return (!input->previousState) && input->currentState;
}

bool ButtonReleased(Input * input)
{
  return (!input->currentState) && input->previousState;
}

bool InputActive(Input * input)
{
  return input->currentState;
}

bool InputInactive(Input * input)
{
  return !(input->currentState);
}

void InitialiseInput(Input * input)
{
  pinMode(input->pin, INPUT);
  
  input->currentState = digitalRead(input->pin) && input->activeState;
  input->previousState = input->currentState;
}
