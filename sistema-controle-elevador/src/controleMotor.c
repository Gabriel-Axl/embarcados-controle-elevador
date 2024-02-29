#include <unistd.h>  //Used for UART
#include <fcntl.h>   //Used for UART
#include <termios.h> //Used for UART
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <pthread.h>
#include <wiringPiI2C.h>

#include <controleBME.h>
#include <i2c.h>
#include <filaEventos.h>
#include <uart.h>
#include <queue.h>
#include <controleLCD.h>
#include <pid.h>
#include <crc16.h>

#define DIR_1 28
#define DIR_2 29
#define POTM  26

pthread_mutex_t uartMutex = PTHREAD_MUTEX_INITIALIZER;

Queue* queue;
int andar[] = { 2161 - 20, 6461 - 40, 12321 - 45, 21701 - 65};

//rasp40 
//térreo ->> 2151 - 2171
//1° andar ->> 6451 - 6471
//2° andar ->> 12311 - 12331
//3° andar ->> 21691 - 21711

int requisicao;
int posicao__elevador = 0;
int deve_terminar = 0;
unsigned char dados[11];
char estado[15] = "Parado";
int sinalPWM = 0;

void* LCD(void* arg) {
    fd = wiringPiI2CSetup(0x27);
    lcd_init();
    int fd_bme = wiringPiI2CSetup(0x76);
    struct bme280_dev devin =  setup_bme280(fd_bme);
    float temp;
    while (deve_terminar != 1){
        escrever(estado);
        delay(500);
        if(sensor_data.temperature > 0){
            enviarTemperatura(sensor_data.temperature);
        }
        delay(500);
    }
    
    return NULL;
}

void* lerBotoesThread(void* arg) {
    while (deve_terminar != 1) {
        fila();
    } 
    return NULL;
}

void* lerEncoderThread(void* arg) {
    while (deve_terminar != 1) {
        int posicao = lerEncoder1();
        if(posicao >= 0 && posicao <= 25500){
            posicao__elevador = posicao;
        }
        usleep(150000);  
    }

    return NULL;
}

void* escreverPWMThread(void* arg) {
    while(deve_terminar != 1) {
        if(sinalPWM < 0){
           enviarPWM(sinalPWM * (-1)); 
        }else{
           enviarPWM(sinalPWM);
        }
       
        delay(1500);
    }
    return NULL;
}

void configuraPinos(){
    pinMode (DIR_1, OUTPUT); 
    pinMode (DIR_2, OUTPUT);
    pinMode(POTM, OUTPUT);
    softPwmCreate(POTM, 0, 100);
}

void moverMotor(int referencia){
    
    pid_configura_constantes(0.005, 0.00002, 20);
    pid_atualiza_referencia((double) referencia );
    if (referencia > posicao__elevador)
        {
            strcpy(estado, "Subindo");
            while(posicao__elevador <= referencia){
                int dado = posicao__elevador;
                int potencia;
                if (dado >= 0 && dado < 25500)
                {
                    potencia = (int) pid_controle((double) dado);
                    sinalPWM = potencia;
                }
                if( potencia > 0){
                    digitalWrite(DIR_1, 1);
                    digitalWrite(DIR_2, 0);
                    softPwmWrite(POTM, potencia);
                }else{
                    digitalWrite(DIR_1, 0);
                    digitalWrite(DIR_2, 1);
                    softPwmWrite(POTM, (potencia * (-1)));
                }
            }
        }else{
            strcpy(estado, "Descendo");
            while(posicao__elevador >= referencia + 85){
                int dado = posicao__elevador;
                int potencia;
                if (dado >= 0 && dado < 25500)
                {
                    potencia = (int) pid_controle((double) dado);
                    sinalPWM = potencia;

                }
                if( potencia < 0){
                    digitalWrite(DIR_1, 0);
                    digitalWrite(DIR_2, 1);
                    softPwmWrite(POTM, (potencia * (-1)) );
                }else{
                    digitalWrite(DIR_1, 1);
                    digitalWrite(DIR_2, 0);
                    softPwmWrite(POTM, potencia);
                }
            }
        }
    sinalPWM = 0;
    strcpy(estado, "Parado");
    digitalWrite(DIR_1, 1);
    digitalWrite(DIR_2, 1);
    softPwmWrite(POTM, 100);
    apagarBtn(requisicao);
    dequeue(queue);
    delay(10000);
}

int decodificaAndar(int i ){
    if(i == 0 || i == 7){
        return 0;
    }
    if(i == 1 || i == 2 || i == 8){
        return 1;
    }
    if(i == 3 || i == 4 || i == 9){
        return 2;
    }
    if(i == 5 || i == 10){
        return 3;
    }
    return -1;
}

void controlaMotor(){
    enqueueUnique(queue, 0);
    pthread_t threadBotoes, threadEncoder, threadLCD, threadPWM;

    configuraPinos();

    pthread_create(&threadBotoes, NULL, lerBotoesThread, NULL);
    pthread_create(&threadEncoder, NULL, lerEncoderThread, NULL);
    pthread_create(&threadLCD, NULL, LCD, NULL);
    pthread_create(&threadPWM, NULL, escreverPWMThread, NULL);
    
    delay(300);

    int i;
    while(1){
        requisicao = peek(queue);
        if(requisicao != -1 ){
            delay(10);
            int pos = decodificaAndar(requisicao);
            if(pos == -1){
                strcpy(estado, "Emergencia");
                digitalWrite(DIR_1, 1);
                digitalWrite(DIR_2, 1);
                apagarBtn(6);
                delay(1000);
                exit(0);
            }
            moverMotor(andar[pos]);

        }
    }
    deve_terminar = 1; // sinaliza para a thread terminar
}