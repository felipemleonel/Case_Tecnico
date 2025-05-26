#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/missile.h"

void missile(void *p1, void *p2, void *p3) {
    k_sem_take(&sem_missile_init, K_FOREVER);
    char received[4];
    char response[4] = "conn";

    k_sleep(K_MSEC(3500));

    /*Rotina de resposta*/
    while (!self_destruction) {
        if (k_msgq_get(&S_M_channel_communication, &received, K_NO_WAIT) == 0) {
            if ((rand() % 100) < 50) {//Definir aqui a probabilidade do míssil conseguir responder
                k_msgq_put(&M_S_channel_communication, &response, K_NO_WAIT);
            }
        }
    }
}

