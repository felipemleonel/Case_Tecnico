#include <zephyr/drivers/uart.h>
#include <zephyr/sys/printk.h>
#include <stdlib.h>
#include <stdio.h>

#include "../inc/setup.h"
#include "../inc/communication.h"

/*Configurações padrões do sistema*/
#define n_sample_standart 10
#define freq_sample_standart  2
#define freq_pkg_standart  1

/* Variáveis globais relacionadas a aquisição de dados*/
int n_sample_sended = 0;
float freq_pkg = freq_pkg_standart;
float freq_sample = freq_sample_standart;
int n_sample = n_sample_standart;

/* Task para configurar n_sample, freq_sample e freq_pkg*/
void setup(void *p1, void *p2, void *p3){
    if (!device_is_ready(uart_dev)) {
        printk("UART device not ready\n");
    }
    /* Variáveis que irão ser usadas para setar os períodos dos timers conforme a configuração escolhida*/
    float period_pkg_ms = 1000.0f/freq_pkg_standart;
    float period_sample_ms = 1000.0f/freq_sample_standart;
    
    while (1){
        uint8_t rx_byte;
        char input_buffer[MAX_BUFFER_SIZE];
        size_t input_index = 0;
        bool line_received = false;
        
        /* Escolha entre configuração padrão ou personalizada*/
        printk("Deseja usar as configuracoes padroes? [S/N]\n");
        line_received = false;
        input_index = 0;
        while (!line_received) {
            if (uart_poll_in(uart_dev, &rx_byte) == 0) {
                uart_poll_out(uart_dev, rx_byte);  
                if (rx_byte == '\n' || rx_byte == '\r') {
                    input_buffer[input_index] = '\0';
                    line_received = true;
                } else if (input_index < MAX_BUFFER_SIZE - 1) {
                    input_buffer[input_index++] = rx_byte;
                }
            }
        }
        if (input_buffer[0]=='S'){
            period_pkg_ms = 1000.0f/freq_pkg_standart;
            period_sample_ms = 1000.0f/freq_sample_standart;
            n_sample = n_sample_standart;
        }
        if (input_buffer[0]=='N'){
            /* Configuração de n_sample*/
            printk("Digite o numero de amostras (n_sample):\n");
            line_received = false;
            input_index = 0;
            while (!line_received) {
                if (uart_poll_in(uart_dev, &rx_byte) == 0) {
                    uart_poll_out(uart_dev, rx_byte);  
                    if (rx_byte == '\n' || rx_byte == '\r') {
                        input_buffer[input_index] = '\0';
                        n_sample = atoi(input_buffer);
                        printk("\nValor de n_sample: %d\n", n_sample);
                        line_received = true;
                    } else if (input_index < MAX_BUFFER_SIZE - 1) {
                        input_buffer[input_index++] = rx_byte;
                    }
                }
            }
            /* Configuração de freq_sample*/
            printk("Digite a frequencia de amostragem (freq_sample) em Hz:\n");
            line_received = false;
            input_index = 0;
            while (!line_received) {
                if (uart_poll_in(uart_dev, &rx_byte) == 0) {
                    uart_poll_out(uart_dev, rx_byte);  
                    if (rx_byte == '\n' || rx_byte == '\r') {
                        input_buffer[input_index] = '\0';
                        freq_sample = strtof(input_buffer, NULL);
                        printk("\nValor de freq_sample: %.2f Hz\n", (double)freq_sample);
                        line_received = true;
                    } else if (input_index < MAX_BUFFER_SIZE - 1) {
                        input_buffer[input_index++] = rx_byte;
                    }
                }
            }

            /* Configuração de freq_pkg*/
            printk("Digite a frequencia do pacote (freq_pkg) em Hz:\n");
            line_received = false;
            input_index = 0;
            while (!line_received) {
                if (uart_poll_in(uart_dev, &rx_byte) == 0) {
                    uart_poll_out(uart_dev, rx_byte);  
                    if (rx_byte == '\n' || rx_byte == '\r') {
                        input_buffer[input_index] = '\0';
                        freq_pkg = strtof(input_buffer, NULL);
                        printk("\nValor de freq_pkg: %.2f Hz\n", (double)freq_pkg);
                        line_received = true;
                    } else if (input_index < MAX_BUFFER_SIZE - 1) {
                        input_buffer[input_index++] = rx_byte;
                    }
                }
            }
            period_pkg_ms = 1000.0f / freq_pkg;
            period_sample_ms = 1000.0f / freq_sample;
        }

        printk("\n");
        printk("----//----\n");

        /* Liberação dos semáforos das outras Task*/
        for (int i = 0; i < 3; i++) {
            k_sem_give(&setup_complete);
        }

        /* Configuração dos timers relacionados a aquisição*/
        k_timer_start(&timer_uart_sender, K_SECONDS(0), K_MSEC((int)period_pkg_ms));
        k_timer_start(&timer_temp_sampler, K_SECONDS(0), K_MSEC((int)period_sample_ms));

        /* Espera pela nova chamada do setup*/
        k_sem_take(&setup_request, K_FOREVER);
        k_sem_reset(&setup_complete);
    }   
}