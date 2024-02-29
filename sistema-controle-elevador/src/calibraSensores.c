#include "calibraSensores.h"

int posElevador;
int sensor[] = {0,0,0,0};
void sensorCallback0() {

    int state = digitalRead(TER);
    static int value = 0; 
    if (state == HIGH) {
        printf("Sensor ativado (Elevador chegou ao %d sensor)\nposicao: %d\n", 0, posElevador);
        if(sensor[0] == 0 ){
            sensor[0] = posElevador;
        }
    } else {
        printf("Sensor desativado (Elevador saiu do %d sensor)\nposicao: %d\n", 0, posElevador);
    }
}

void sensorCallback1( ) {

    int state = digitalRead(AND1);
    static int value = 0; 
    if (state == HIGH) {
        printf("Sensor ativado (Elevador chegou ao %d sensor)\nposicao: %d\n", 1, posElevador);
         if(sensor[1] == 0 ){
            sensor[1] = posElevador;
        }
    } else {
        printf("Sensor desativado (Elevador saiu do %d sensor)\nposicao: %d\n", 1, posElevador);  
    }
  
}

void sensorCallback2( ) {

    int state = digitalRead(AND2);

    if (state == HIGH) {
        printf("Sensor ativado (Elevador chegou ao %d sensor)\nposicao: %d\n", 2, posElevador);
        if(sensor[2] == 0 ){
            sensor[2] = posElevador;
        }
    } else {
        printf("Sensor desativado (Elevador saiu do %d sensor)\nposicao: %d\n", 2, posElevador);
    }
}

void sensorCallback3( ) {

    int state = digitalRead(AND3);

    if (state == HIGH) {
        printf("Sensor ativado (Elevador chegou ao %d sensor)\nposicao: %d\n", 3, posElevador);
        if(sensor[3] == 0 ){
            sensor[3] = posElevador;
        }
        
    } else {
        printf("Sensor desativado (Elevador saiu do %d sensor)\nposicao: %d\n", 3, posElevador);
    }
}

void* lerEncode(void* arg) {
    while (1) {
        int posicao = lerEncoder1();
        if(posicao >= 0 && posicao <= 25500){
            posElevador = posicao;
        } 
    }

    return NULL;
}

void calibraSensorAndar(){

    pthread_t  threadEncoder;

    pthread_create(&threadEncoder, NULL, lerEncode, NULL);
    delay(200);
    pinMode(TER, INPUT);
    pinMode(AND1, INPUT);
    pinMode(AND2, INPUT);
    pinMode(AND3, INPUT);
    pinMode (DIR_1, OUTPUT); 
    pinMode (DIR_2, OUTPUT);
    pinMode(POTM, OUTPUT);
    softPwmCreate(POTM, 0, 100);

    pullUpDnControl(TER, PUD_UP);
    pullUpDnControl(AND1, PUD_UP);
    pullUpDnControl(AND2, PUD_UP);
    pullUpDnControl(AND3, PUD_UP);

    wiringPiISR(TER, INT_EDGE_BOTH, &sensorCallback0);
    wiringPiISR(AND1, INT_EDGE_BOTH, &sensorCallback1);
    wiringPiISR(AND2, INT_EDGE_BOTH, &sensorCallback2);
    wiringPiISR(AND3, INT_EDGE_BOTH, &sensorCallback3);
    while(1){
        if(posElevador < 21691){
            digitalWrite(DIR_1, 1);
            digitalWrite(DIR_2, 0);
            softPwmWrite(POTM, 3);
        }else if(posElevador > 21695){
            digitalWrite(DIR_1, 0);
            digitalWrite(DIR_2, 1);
            softPwmWrite(POTM, 3);
        }else{
            digitalWrite(DIR_1, 1);
            digitalWrite(DIR_2, 1);

        }

    }
    // -----pegar valor dos sensores
    /*
    while(posElevador < 25000){
        digitalWrite(DIR_1, 1);
        digitalWrite(DIR_2, 0);
        softPwmWrite(POTM, 5);
    }*/

    digitalWrite(DIR_1, 1);
    digitalWrite(DIR_2,1);


    printf("0 - %d\n", sensor[0]);
    printf("1 - %d\n", sensor[1]);
    printf("2 - %d\n", sensor[2]);
    printf("3 - %d\n", sensor[3]);
    
}