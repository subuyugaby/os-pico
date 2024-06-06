#include <stdio.h>
#include "pico/stdlib.h"

#include "thread.h"

/*Threads lists*/
static struct list ready_list;
static struct list all_list;

/*Threads counter id*/
static int next_id = -1;

/*Current id*/
static thread_t *current_thread;

#define TIME_SLICE 4
static unsigned thread_ticks;

static bool all_threads_finished;

/*Thread */
void lista_ready_threads(){
    if(!list_empty(&ready_list)){
        struct list_elem *iter = list_begin(&ready_list);
        printf("Thread list - STATUS: READY\n");
        printf("-> ");
        while(iter != list_end(&ready_list) ){
            printf("%d, ", list_entry(iter, struct thread, elem)->id);
            iter = list_next(iter);
        }
        printf("\n");
    }
}

thread_t *thread_current(void) {
    return current_thread;
}

void thread_init(void) {
    list_init(&ready_list);
    lista_ready_threads();
    list_init(&all_list);
    all_threads_finished = false;
    current_thread = NULL;
}

void thread_yield(void) {
    current_thread->status = THREAD_READY;
    schedule();
}

void schedule(void) {
    if(!list_empty(&ready_list)){
        struct list_elem *e = list_begin(&ready_list);
        thread_t *t = list_entry(e, thread_t, elem);

        /*Run the thread, change the current thread*/
        t->status = THREAD_RUNNING;
        current_thread = t;

        t->function(t->arg);
        
        t->status = THREAD_FINISHED;
        list_remove(&t->elem);
        free(t);

        
        if (list_empty(&ready_list)) {
            all_threads_finished = true;
        }
    }
}

void thread_unblock(thread_t *t) {
    t->status = THREAD_READY;
    list_push_front(&ready_list, &t->elem);
}


/*Creating a thread*/
void thread_create(void (*function)(void *), void *arg) {
    thread_t *t = (thread_t *)malloc(sizeof(thread_t));
    if (t == NULL) {
        printf("Error al crear el proceso: memoria insuficiente.\n");
    }
    t->id = ++next_id;
    t->status = THREAD_READY;
    t->function = function;
    t->arg = arg;
    list_push_back(&all_list, &t->allelem);
    thread_unblock(t);
}

void thread_block (void){
  thread_current ()->status = THREAD_BLOCKED;
  schedule ();
}

void thread_foreach (thread_action_func *func, void *aux){
  struct list_elem *e;

  for (e = list_begin (&all_list); e != list_end (&all_list);
       e = list_next (e))
    {
      struct thread *t = list_entry (e, struct thread, allelem);
      func (t, aux);
    }
}

void thread_check_blocked (struct thread *t, void *aux){
  if (t->status == THREAD_BLOCKED && t->blocked_ticks > 0){
    t->blocked_ticks--;
	if (t->blocked_ticks == 0) {
		thread_unblock(t);
    }
  }
}

void thread_tick(void) {
    struct thread *t = thread_current();
    if (++thread_ticks >= TIME_SLICE) {
        thread_ticks = 0;
        thread_yield();
    }
}

void thread_join(void) {
    while (!all_threads_finished) {
        thread_yield();
    }
}