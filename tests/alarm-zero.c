#include <stdio.h>
#include "../devices/timer.h"

void test_alarm_zero(void){
    timer_sleep(0);
    pass();
}