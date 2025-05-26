#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>

#include "../inc/communication.h"

/* Declarando o periférico da UART*/
#define UART_DEVICE_NODE DT_CHOSEN(zephyr_shell_uart)
const struct device *uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);

/* Fila de mensagens para troca de mensagens entre tasks*/
K_MSGQ_DEFINE(temp_queue, sizeof(float), QUEUE_SIZE, 4);

/* Semáforos para sincronizar as tasks com o timer */
K_SEM_DEFINE(sem_temp_sampler, 0, 1);
K_SEM_DEFINE(sem_uart_sender, 0, 1);

/* Semáforos para entrar e sair da task de setup */
K_SEM_DEFINE(setup_complete, 0, 3);
K_SEM_DEFINE(setup_request, 0, 1);  

/* Funções chamadas quando o timer expira */
void timer_expiry_handler_sampler(struct k_timer *timer) {
    k_sem_give(&sem_temp_sampler);  // Acorda a task
}
void timer_expiry_handler_sender(struct k_timer *timer) {
    k_sem_give(&sem_uart_sender);  // Acorda a task
}

/* Definição dos timers usados*/
K_TIMER_DEFINE(timer_temp_sampler, NULL, NULL);
K_TIMER_DEFINE(timer_uart_sender, NULL, NULL);

// Inicialização dos timers
void start_timers(void) {
    k_timer_init(&timer_temp_sampler, timer_expiry_handler_sampler, NULL);
    k_timer_init(&timer_uart_sender, timer_expiry_handler_sender, NULL);
}
