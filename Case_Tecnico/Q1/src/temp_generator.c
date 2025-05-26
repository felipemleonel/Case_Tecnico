#include "../inc/temp_generator.h"
#include "../inc/communication.h"
#include <stdlib.h>

/* Task para gerar valores aleatórios de temperatura*/
float current_temperature = 26.25;
void temp_generator(void *p1, void *p2, void *p3) {
    k_sem_take(&setup_complete, K_FOREVER);
    while (1) {
        float delta = ((float)(rand() % 500) / 2000.0f) - 0.25f; 
        if (((current_temperature + delta) > 26.5f|| (current_temperature + delta) < 26.0f)){
            delta = delta * -1;
        }
        current_temperature += delta;
        k_sleep(K_MSEC(500));
    }
}