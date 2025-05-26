#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "../inc/generator.h"
#include "../inc/timers.h"

void uart_sender(void *p1, void *p2, void *p3) {
    float data;
    while (1) {
        k_sem_take(&sem_sender, K_FOREVER);
        while (k_msgq_get(&temp_queue, &data, K_NO_WAIT) == 0) {
            printk("Aquisicao: %.2f\n", (double)data);
        }
    }
}