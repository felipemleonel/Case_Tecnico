#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <stdlib.h>
#include "../inc/generator.h"
#include "../inc/timers.h"

static float value = 50.0f;
/*Definição da fila*/
K_MSGQ_DEFINE(temp_queue, sizeof(float), QUEUE_SIZE, 4);

void generator(void *p1, void *p2, void *p3) {
    while (1) {
        k_sem_take(&sem_generator, K_FOREVER);
        float delta = ((float)(rand() % 1000) / 100.0f) - 5.0f;

        if (((value + delta) > 100.0f || (value + delta) < 0.0f)) {
            delta *= -1;
        }

        value += delta;
        /*Envio dos valores gerados*/
        if (k_msgq_put(&temp_queue, &value, K_NO_WAIT) != 0) {
            printk("Fila cheia, descartando dado\n");
        }
    }
}