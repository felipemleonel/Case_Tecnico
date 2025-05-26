#ifndef GENERATOR_H
#define GENERATOR_H

#define QUEUE_SIZE 11
/*Fila para troca de mensagens*/
extern struct k_msgq temp_queue;
/*Task para gerar valores aleatórios*/
void generator(void *p1, void *p2, void *p3);

#endif
