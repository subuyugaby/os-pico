#include <stdio.h>
#include "../devices/timer.h"
#include "../threads/thread.h"

void imprimir(void *args){
    printf("Se ejecuto la funcion...\n");
}

void test_one_thread(void){
    int args[1];
    thread_create(imprimir, &args);
    thread_join();
}