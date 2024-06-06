#include <stdio.h>
#include "../devices/timer.h"

void test_alarm_negative(void){
    timer_sleep(-1);
    pass();
}