#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <zephyr/kernel.h>

#define MAX_BUFFER_SIZE 128
#define STACK_SIZE 1024
#define QUEUE_SIZE 32
/* Declarando o periférico da UART*/
extern const struct device *uart_dev;
/* Fila de mensagens para troca de mensagens entre tasks*/
extern struct k_msgq temp_queue;
/* Semáforos para sincronizar as tasks com o timer */
extern struct k_sem sem_temp_sampler;
extern struct k_sem sem_uart_sender;
/* Semáforos para entrar e sair da task de setup */
extern struct k_sem setup_complete;
extern struct k_sem setup_request;
/* Declaração dos timers usados*/
extern struct k_timer timer_temp_sampler;
extern struct k_timer timer_uart_sender;
/*Função para iniciar os timers que controlam as frequências de sample e pkg*/
void start_timers(void);

#endif
