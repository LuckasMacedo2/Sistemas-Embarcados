#include "timmer.h"
#include "USART.h"
#include "conversao_AD.h"

// FIR
//#include "fir_lp.h" // Filtro FIR passa baixa
//#include "fir_hp.h"   // Filtro FIR passa alta

// IIR
//#include "iir_lp.h" // Filtro FIR passa baixa
#include "iir_hp.h"   // Filtro FIR passa alta
char * dados = new char[16];
/*  0 -> Esperando o tamanho do vetor x
 *  1 -> Entrando com todos os valores de x
 *  2 -> Esperando o tamanho do vetor h
 *  3 -> Entrando com todos os valores de h
 *  4 -> Calcula e mostra a convolucao
 */
const int idxMax = 10;
float x[idxMax];

int tamX = 0;
int indX = 0;
int index = 0;


// ------------------------------------- Interrupcoes -------------------------------------------------------------------
// Tratamento de interrupcao
ISR(TIMER1_OVF_vect){               // Overflow Timmer1
  // Houve um overflow em timmer1
  timmer1_reset();                  // Reseta o Timmer1
  //ADCSRA |= (1 << ADSC);          // Mantem o valor de ADCSRA e desloca ADSC em 1, ou seja, seta ADSC para um da inicio a conversao
}

void imprimi_valor_lido(double w, double y){
  char aux[5];
  dtostrf(y, 5, 5, dados);
  enviar_dados_USART_ln(dados);
}

ISR (ADC_vect){                     // Conversao AD
  double w = ADCW * 5.0 / 1024.0 - 2;
  double y = iir(w);
  
  unsigned char * aux = new unsigned char[5];
  //char aux2[5];
  
  dtostrf(y, 5, 5, aux);
  enviar_dados_USART(aux);
  aux = new unsigned char[5];
  //char aux2[5];
  enviar_dados_USART(" ");
  dtostrf(w, 5, 5, aux);
  enviar_dados_USART_ln(aux);
  
  //aux = new char[5];
  //dtostrf(w, 5, 5, aux);
  
  //enviar_dados_USART(" ");
  //enviar_dados_USART_ln(aux);
//  imprimi_valor_lido(w);
}
// ------------------------------------- Interrupcoes -------------------------------------------------------------------


void setup() {
 cfg_USART();
 cfg_Timer1();
 cfg_convAD();
//inicializa_buffer();
//circ_init() ;
 SREG = 0b10000000;
}

void loop() {
// put your main code here, to run repeatedly:

}
