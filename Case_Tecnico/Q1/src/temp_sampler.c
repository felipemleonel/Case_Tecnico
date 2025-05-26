#include "../inc/temp_sampler.h"
#include "../inc/temp_generator.h"
#include "../inc/communication.h"


/* Task para amostrar o sinal*/ 
void temp_sampler(void *p1, void *p2, void *p3) {
    k_sem_take(&setup_complete, K_FOREVER);
    while (1) {
        k_sem_take(&sem_temp_sampler, K_FOREVER);// Semáforo usado para controlar a frequência
        float sampled = current_temperature;
        if (k_msgq_put(&temp_queue, &sampled, K_NO_WAIT) != 0) {
            printk("Fila cheia, descartando dado\n");
        }
    }
}