#include <stdio.h>
#include <controleMotor.h>
#include <pthread.h>
#include <queue.h>

unsigned char dadosBtn[11];

void fila() {

    lerBotoes(dadosBtn);
    for (int i = 0; i < 11; i++) {
        if(dadosBtn[i] > 1){
            break;
        }
        if (dadosBtn[i] == 1 && dadosBtn[i] < 2){
            enqueueUnique(queue, i);
        }
    }

    delay(50);
}