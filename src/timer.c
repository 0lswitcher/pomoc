// file : timer.c 
// date : 27-06-2026
// std  : c23 

#include "timer.h"
#include <stdlib.h>

// the timer tick will update the int values.
// this will return 0 on success and -1 on failure.
int timer_tick(int *hr, int *min, int *sec) {
    if (*sec > 0) {
        (*sec)--;
    } else if (*min > 0) {
        (*min)--;
        *sec = 59;
    } else if (*hr > 0) {
        (*hr)--;
        *min = 59;
        *sec = 59;
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// define the timer_load_focus function, which will load initialy the remaining time to focus_hr, min, sec.
void timer_load_focus(PomData *data) {
    data->remaining_hr = data->focus_hr;
    data->remaining_min = data->focus_min;
    data->remaining_sec = data->focus_sec;
}

// similary for break. 
// but we need to focus and not waste our time in break, so you cannot take break for hours. 

void timer_load_break(PomData *data) {
    data->remaining_hr = 0;
    data->remaining_min = data->break_min;
    data->remaining_sec = data->break_sec;
}
