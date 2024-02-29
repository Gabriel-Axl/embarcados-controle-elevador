#ifndef CONTROLEMOTOR_H
#define CONTROLEMOTOR_H

#include <pthread.h>
#include <queue.h>

extern andar[];
extern pthread_mutex_t uartMutex; 

extern Queue* queue;

void moverMotor(int referencia);
void configuraPinos();
void controlaMotor();

#endif 
