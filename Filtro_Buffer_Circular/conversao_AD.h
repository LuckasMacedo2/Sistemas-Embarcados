
#ifndef conversao_AD_h
#define conversao_AD_h
#include "Arduino.h"
// ------------------------------------- Conversao AD -------------------------------------------------------------------
void cfg_convAD(){
  /* Configuracao adotada
   * ADMUX -> Referencia em Avcc e canal ADC0 escolhido
   * ADCSRA -> Conv. AD habilitado, selecionado o auto trigger, interrupcao ativada, prescaler de 128
   * ADCSRB -> Configurado para comersar a Conv. AD quando houver estouro do Timmer1
   */
  cli();
  ADCSRA = 0b10101111;  // Habilita o conversor AD prescaler de 128, interrupcao habilitada
  ADCSRB = 0b00000110;
  ADMUX = 0b01000000; 
  sei();
}
// ------------------------------------- Conversao AD -------------------------------------------------------------------


#endif