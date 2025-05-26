#include <zephyr/sys/printk.h>
#include "../inc/communication.h"
#include "../inc/uart_sender.h"
#include "../inc/setup.h"

/* Função para printar tempo, usada para validar freq_pkg e freq_sample*/
void print_time(void) {
    int64_t uptime_ms = k_uptime_get();

    uint32_t ms = uptime_ms % 1000;
    uint32_t seconds = (uptime_ms / 1000) % 60;
    uint32_t minutes = (uptime_ms / 1000 / 60) % 60;
    uint32_t hours = (uptime_ms / 1000 / 3600);

    printk("Hora do sistema: %02u:%02u:%02u.%03u\n", hours, minutes, seconds, ms);
}

/* Task responsável pelo envio de dados via UART*/ 
void uart_sender(void *p1, void *p2, void *p3) {
    k_sem_take(&setup_complete, K_FOREVER);
    float temp;
    while (1) {
        k_sem_take(&sem_uart_sender, K_FOREVER);
        while (k_msgq_get(&temp_queue, &temp, K_NO_WAIT) == 0) {
            
            if (n_sample_sended<n_sample){
                printk("Temperatura: %.2f C\n", (double)temp);
                //print_time(); //Interessante para validação de frequências
                n_sample_sended++;
            } else{
                n_sample_sended = 0;
                while (k_msgq_get(&temp_queue, &temp, K_NO_WAIT) == 0); // Resetar fila
                k_timer_stop(&timer_temp_sampler);
                k_timer_stop(&timer_uart_sender);
                k_sem_give(&setup_request);
                break;
            }
            
        }
    }
}