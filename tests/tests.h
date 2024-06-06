void run_test (const char *);

typedef void test_func (void);

extern test_func test_alarm_negative;
extern test_func test_alarm_zero;
extern test_func test_one_thread;
extern test_func test_multi_thread;

void pass (void);
