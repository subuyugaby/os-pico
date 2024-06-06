#include <stdint.h>
#include "../misc/list.h"

/*Thread status with enum*/
enum thread_status
{
    THREAD_RUNNING,
    THREAD_READY,
    THREAD_BLOCKED,
    THREAD_FINISHED
};

/*Thread struct*/
typedef struct thread
{
    int id;                    /*Thread id*/
    void (*function)(void *);  /*Thread function*/
    struct list_elem elem;     /*List elem*/
    uint64_t blocked_ticks;    /*Thread ticks for being blocked*/
    enum thread_status status; /*Thread status*/
    void *arg;                  /*Thread stack*/
    struct list_elem allelem;  /*Thread elem for all list*/
} thread_t;

thread_t *thread_current(void);
void thread_init(void);
void thread_unblock(thread_t *t);
void thread_block(void);
void thread_yield(void);
void thread_create(void (*function)(void *), void *arg);

typedef void thread_action_func(struct thread *t, void *aux);
void thread_foreach(thread_action_func *, void *);
void thread_check_blocked(struct thread *, void *aux);

void schedule(void);

void thread_tick(void);

void thread_join(void);

void lista_ready_threads(void);