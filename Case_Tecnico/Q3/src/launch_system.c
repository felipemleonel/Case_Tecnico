#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <string.h>
#include "../inc/launch_system.h"


void launch_system(void *p1, void *p2, void *p3) {
    printk("Missil lancado!\n");
    k_sem_give(&sem_missile_init);
    k_sleep(K_MSEC(3500));
    
    const char conn[] = "conn";
    char response[4];

    k_sem_give(&sem_communication_init);
    /*Teste de conexão*/
    for (int i = 0; i < 6; i++) {
        k_sem_take(&sem_test_connection, K_FOREVER);
        if (!self_destruction) {
            if (k_msgq_put(&S_M_channel_communication, &conn, K_NO_WAIT) == 0) {
                printk("Tentativa %d: comando enviado.\n", i + 1);
            } else {
                printk("Fila cheia, descartando dado\n");
            }

            k_sleep(K_MSEC(10));

            while (k_msgq_get(&M_S_channel_communication, &response, K_NO_WAIT) == 0) {
                printk("Conexao estabelecida.\n");
                connection_established = true;
            }

            if (connection_established) break;
        }
    }
    /*Comunicação*/
    if (connection_established) {
        while (1) {
            k_sem_take(&sem_communication, K_FOREVER);
            printk("Enviando dados de guiagem.\n");
            //print_time();
        }
    }
}

