#ifndef Types_h
#define Types_h

typedef struct {
  int pin;
  bool currentState; 
  bool previousState;
  bool activeState;
  int debounce;
} Input;

typedef struct {
  int pin;
  bool currentState;
  bool activeState;
} Output;

#endif
