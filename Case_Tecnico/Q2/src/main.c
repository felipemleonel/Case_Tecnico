#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "../inc/timers.h"
#include "../inc/generator.h"
#include "../inc/uart_sender.h"

/*Iniciando tasks*/
K_THREAD_DEFINE(generator_id, 1024, generator, NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(sender_id,    1024, uart_sender,    NULL, NULL, NULL, 5, 0, 0);

int main(void) {
    printk("Sistema iniciado\n");

    start_timers();

    return 1;
}
