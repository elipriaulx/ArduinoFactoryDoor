#ifndef _ROLLERDOOR_TYPES_H_
#define _ROLLERDOOR_TYPES_H_

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
