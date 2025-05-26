#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <zephyr/kernel.h>
#include <stdbool.h>
/*Canais onde a comunicação irá ocorrer*/
extern struct k_msgq S_M_channel_communication;//Canal onde o sistema de lançamento envia mensagens para o míssil
extern struct k_msgq M_S_channel_communication;//Canal onde o míssil envia mensagens para o sistema de lançamento
/*Semáforos*/
extern struct k_sem sem_test_connection;//Controla a frequência do teste de comunicação
extern struct k_sem sem_communication;//Controla a frequência da comunicação
extern struct k_sem sem_missile_init;//Indica lançamento do míssil
extern struct k_sem sem_communication_init;//Indica início da comunicação
/*Variáveis globais de controle*/
extern bool self_destruction;
extern bool connection_established;
/*Função para printar tempo e validar frequências*/
void print_time(void);
/*Funções de callback para os timers*/
/*Estão aqui pois se utilizam dos semáforos*/
void timer_expiry_handler_test_connection(struct k_timer *timer);
void timer_expiry_handler_communication(struct k_timer *timer);

#endif