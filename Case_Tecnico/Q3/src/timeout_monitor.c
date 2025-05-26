#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "../inc/timeout_monitor.h"

void timeout_monitor(void *p1, void *p2, void *p3) {
    k_sem_take(&sem_communication_init, K_FOREVER);
    k_sleep(K_MSEC(3000));

    /*Mensagem de auto destruição*/
    if (!connection_established) {
        printk("Missil se autodestruiu.\n");
        self_destruction = true;
    }
}

