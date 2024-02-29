#include <wiringPiI2C.h>
#include <controleBME.h>
#include <controleLCD.h>
#include <pthread.h>
#include <uart.h>

struct bme280_dev devin;
struct bme280_data sensor_data;

void setup(){
    fd = wiringPiI2CSetup(0x27);
    lcd_init();
    int fd_bme = wiringPiI2CSetup(0x76);
    devin =  setup_bme280(fd_bme);
}

void escrever(char estado[]){
    int fd_bme = wiringPiI2CSetup(0x76);
    devin =  setup_bme280(fd_bme);
    sensor_data = read_and_print_temperature(&devin);
    delay(200);
    fd = wiringPiI2CSetup(0x27);
    lcd_init();
    delay(400);
    ClrLcd();
    lcdLoc(LINE1);
    typeln(estado);
    lcdLoc(LINE2);
    char tempString[20];
    if(sensor_data.temperature > 0){
        snprintf(tempString, sizeof(tempString), "Temp: %.2fC", sensor_data.temperature);
        typeln(tempString);
    }
    delay(400);
}