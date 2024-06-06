#include <stdio.h>
#include "pico/stdlib.h"

#include "tests/tests.h"
#include "devices/timer.h"
#include "threads/thread.h"

#define BUFFER 100

static void run(char *argv);
static void os_init();

int main()
{
    os_init();
    /*Start buffer*/
    char test[BUFFER];
    int buffer_index = 0;

    /*Welcome message*/
    printf("Inicializando OS...\n");

    /*loop*/
    while (1)
    {
        /*Getting the test*/
        char c = uart_getc(uart0);

        /*Getting the*/
        if (c == '\r')
        {
            test[buffer_index] = '\0';
            /*Run*/
            run(test);
            break;
        }
        else
        {
            test[buffer_index++] = c;
        }
    }

    return 0;
}

static void os_init()
{
    /*Initializing SDK*/
    stdio_init_all();

    /*Initialiting thread structures and timer*/
    thread_init();
    timer_init();
}

static void run(char *argv)
{
    /*This function works as thread root*/
    printf("Executing '%s':\n", argv);
    run_test(argv);
    printf("Execution of '%s' complete.\n", argv);
}

