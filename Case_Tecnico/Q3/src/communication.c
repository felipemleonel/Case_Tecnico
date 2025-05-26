#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/*Fila de mensagens*/ 
K_MSGQ_DEFINE(S_M_channel_communication, sizeof(float), 11, 4);
K_MSGQ_DEFINE(M_S_channel_communication, sizeof(float), 11, 4);

/*Semáforos*/ 
K_SEM_DEFINE(sem_test_connection, 0, 1);
K_SEM_DEFINE(sem_communication, 0, 1);
K_SEM_DEFINE(sem_missile_init, 0, 2);

bool self_destruction = false;
bool connection_established = false;

void print_time(void) {
    int64_t uptime_ms = k_uptime_get();
    uint32_t ms = uptime_ms % 1000;
    uint32_t sec = (uptime_ms / 1000) % 60;
    uint32_t min = (uptime_ms / 60000) % 60;
    uint32_t hr = uptime_ms / 3600000;
    printk("Hora do sistema: %02u:%02u:%02u.%03u\n", hr, min, sec, ms);
}

/*Timer callbacks*/
void timer_expiry_handler_test_connection(struct k_timer *timer) {
    k_sem_give(&sem_test_connection);
}
void timer_expiry_handler_communication(struct k_timer *timer) {
    k_sem_give(&sem_communication);
}
