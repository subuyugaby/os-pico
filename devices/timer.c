#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"

#include "timer.h"
#include "../threads/thread.h"

static struct repeating_timer timer;
static int ticks;

/**/
bool timer_callback(struct repeating_timer *t) {
  
  ticks++;
  thread_tick();
  thread_foreach(thread_check_blocked, NULL);
  return true; // Mantener el temporizador activo
}

void timer_init (void){
  if (!add_repeating_timer_ms(100, timer_callback, NULL, &timer)) {
    printf("Error al iniciar el temporizador\n");
  }
}

void timer_sleep (int ticks){
  if(ticks > 0){
	  struct thread *t = thread_current();
	  t->blocked_ticks = ticks;
	  thread_block();
  }
}