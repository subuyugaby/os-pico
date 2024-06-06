#include <stdio.h>
#include "../devices/timer.h"
#include "../threads/thread.h"

void imprimir_multiple(void *arg){
    int id = *((int*)arg);
    printf("Running thread: %d\n", id);
}

void test_multi_thread(void){
    int args[10];
    for(int i = 9; i >= 0; i--){
        args[i] = i;
        thread_create(imprimir_multiple, &args[i]);
    }
    thread_join();
}