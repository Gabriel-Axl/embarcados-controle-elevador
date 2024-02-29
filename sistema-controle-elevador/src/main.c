#include <stdio.h>
#include <wiringPi.h>
#include <controleMotor.h>
#include <filaEventos.h>
#include <uart.h>
#include <queue.h>
#include <controleLCD.h>
#include <i2c.h>
#include <calibraSensores.h>

int main(){
    if (wiringPiSetup () == -1){
        return 1 ;
    }
    if (iniciarUart() == -1) {
        return -1; 
    }
    queue = createQueue();
   
    //calibraSensorAndar();
    controlaMotor();
    return 0;
}
