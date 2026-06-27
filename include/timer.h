#ifndef TIMER_H 
#define TIMER_H 

#include "state.h"

// a function for decrement the time.
int timer_tick(int *hr, int *min, int *sec);

// a function for updating the data structure of PomData remaining time for focus. 
void timer_load_focus(PomData *data);

// a function for updating the data structure of PomData remaining time for break. 
void timer_load_break(PomData *data);

#endif 
