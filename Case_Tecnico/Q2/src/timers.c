#include <zephyr/kernel.h>
#include "../inc/timers.h"

K_SEM_DEFINE(sem_generator, 0, 1);
K_SEM_DEFINE(sem_sender, 0, 1);

K_TIMER_DEFINE(timer_generator, NULL, NULL);
K_TIMER_DEFINE(timer_uart_sender, NULL, NULL);

void timer_expiry_handler_generator(struct k_timer *timer) {
    k_sem_give(&sem_generator);
}

void timer_expiry_handler_sender(struct k_timer *timer) {
    k_sem_give(&sem_sender);
}

void start_timers() {
    k_timer_init(&timer_generator, timer_expiry_handler_generator, NULL);
    k_timer_init(&timer_uart_sender, timer_expiry_handler_sender, NULL);

    float period_sender_ms = 1000.0f / freq_sender;
    float period_gen_ms    = 1000.0f / freq_generator;

    k_timer_start(&timer_uart_sender, K_SECONDS(0), K_MSEC((int)period_sender_ms));
    k_timer_start(&timer_generator, K_SECONDS(0), K_MSEC((int)period_gen_ms));
}
