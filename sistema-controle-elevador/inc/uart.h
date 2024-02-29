#ifndef UART_H_
#define UART_H_

int iniciarUart();
void fecharUart();
void lerBotoes(unsigned char *dados);
int lerEncoder1();
void apagarBtn(int base);
void enviarPWM(int pwm);
void enviarTemperatura(float temperatura);
#endif 
