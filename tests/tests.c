#include <stdio.h>
#include <string.h>

#include "tests.h"

static const char *test_name;
/*Structure for threads*/
struct test {
    const char *name;
    test_func *function;
};

/*Array of test that exists*/
static const struct test tests[] = {
    {"alarm", test_alarm_negative},
    {"zero-alarm", test_alarm_zero},
    {"single-thread", test_one_thread},
    {"multi-thread", test_multi_thread}
};

void run_test(const char *name){
    const struct test *t;

    for (t = tests; t < tests + sizeof tests / sizeof *tests; t++){
        if (!strcmp (name, t->name)){
            test_name = name;
            printf("(%s) Begin\n", test_name);
            t->function();
            printf("(%s) End\n", test_name);
            return;
        }
    }
    
}

void pass (void){
  printf ("(%s) PASS\n", test_name);
}