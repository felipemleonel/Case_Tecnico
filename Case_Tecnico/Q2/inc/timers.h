#ifndef TIMERS_H
#define TIMERS_H

#include <zephyr/kernel.h>

#define freq_generator 10
#define freq_sender    1
/*Semáforos para controle de frequência*/
extern struct k_sem sem_generator;
extern struct k_sem sem_sender;
/*Funções de callback dos timers*/
void timer_expiry_handler_generator(struct k_timer *timer);
void timer_expiry_handler_sender(struct k_timer *timer);
/*Função para iniciar timers*/
void start_timers();

#endif
