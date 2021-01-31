#ifndef timmer_h
#define timmer_h
#include "Arduino.h"

// ------------------------------------- Timmer -------------------------------------------------------------------------
int f = 4;    // Frequencia de amostragem

void timmer1_reset(){
  // Reseta o Timmer1

  // TCNT1 = 65536 - (Fosc)/ (f * prescaler) - 1
  // O valor inicial de TCNT1 indicara a quantos segundos ele estourara
  // Para defini-lo usa-se
  // TCNT1 = 2^16 - (Fosc)/ (f * prescaler) - 1
  // 2^16 -> Valor maximo de TCNT1
  // Fosc -> Frequencia do oscilador, neste caso 16 MHz
  // f -> Frequência em que ocorrerá o estouro
  // prescaler -> prescaler definido

  /* Configuracao adotada
   * Timmer configurado para estourar a cada 250 ms, 25 ms e 2.5 ms
   */
  TCNT1 = 65536 - (16000000)/ (f * 64) - 1;
}

void cfg_Timer1(){
  /* Configuracao adotada
   * TCCR1A -> Operacao normal
   * TCCR1B -> Prescaler de 256
   * TIMSK1 -> Interrupcao de overflow ativada
   */
  cli();  
  TCCR1A = 0;             // Configura o modo de operacao do Timmer para modo de operacao normal, contador neste caso
  TCCR1B = 0b00000011;    // Configura o prescaler como 256

  // Habilita a interrupcao de estouro
  TIMSK1 = 0b00000001;

  timmer1_reset();        // Resta o tempo
  sei();
}
// ------------------------------------- Timmer -------------------------------------------------------------------------
#endif
