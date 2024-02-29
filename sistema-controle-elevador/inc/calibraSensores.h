#ifndef CALIBRASENSORES_H
#define CALIBRASENSORES_H

#include <wiringPi.h>
#include <pthread.h>

#define TER  1
#define AND1  4
#define AND2  5
#define AND3  6
#define DIR_1 28
#define DIR_2 29
#define POTM  26

void sensorCallback0();
void sensorCallback1();
void sensorCallback2();
void sensorCallback3();

void* lerEncode(void* arg);
void calibraSensorAndar();

#endif 