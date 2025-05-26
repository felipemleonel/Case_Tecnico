#include <zephyr/kernel.h>
#include "../inc/timers.h"


extern void timer_expiry_handler_test_connection(struct k_timer *timer);
extern void timer_expiry_handler_communication(struct k_timer *timer);

K_TIMER_DEFINE(timer_test_connection, timer_expiry_handler_test_connection, NULL);
K_TIMER_DEFINE(timer_communication, timer_expiry_handler_communication, NULL);

void start_timers(void) {
    float period_test_connection_ms = 1000.0f / 5;
    float period_communication_ms = 1000.0f / 1;

    k_timer_start(&timer_test_connection, K_NO_WAIT, K_MSEC((int)period_test_connection_ms));
    k_timer_start(&timer_communication, K_NO_WAIT, K_MSEC((int)period_communication_ms));
}
