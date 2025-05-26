#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include "../inc/setup.h"
#include "../inc/temp_generator.h"
#include "../inc/temp_sampler.h"
#include "../inc/uart_sender.h"
#include "../inc/communication.h"

/* Inicialização das tasks*/
K_THREAD_DEFINE(setup_id, STACK_SIZE, setup, NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(generator_id, STACK_SIZE, temp_generator, NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(sampler_id,   STACK_SIZE, temp_sampler,   NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(sender_id,    STACK_SIZE, uart_sender,    NULL, NULL, NULL, 5, 0, 0);

int main(void) {
    printk("Sistema iniciado\n");

    /* Inicialização dos timers*/
    start_timers();
    return 1;
}