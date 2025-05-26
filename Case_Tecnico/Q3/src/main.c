#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include "../inc/missile.h"
#include "../inc/launch_system.h"
#include "../inc/timeout_monitor.h"
#include "../inc/timers.h"
#include "../inc/communication.h"

/*Iniciando as tasks*/
K_THREAD_DEFINE(launch_system_id, 1024, launch_system, NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(missile_id, 1024, missile, NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(timeout_monitor_id, 1024, timeout_monitor, NULL, NULL, NULL, 5, 0, 0);

int main(void) {
    printk("Sistema iniciado\n");

    start_timers(); // Chamada de função do módulo de timers

    return 1;
}