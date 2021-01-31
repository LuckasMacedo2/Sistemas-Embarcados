#ifndef usart_h
#define usart_h
#include "Arduino.h"

// ------------------------------------- USART --------------------------------------------------------------------------
void cfg_USART(){
  /* Configuracao adotada
   * UCSR0A -> Habilitada a transmissao com 2 vezes mais velociadade
   * UCSR0B -> Recepcao e transmissao habilitada, habilitada a interrupcao de transmissao completa, transmissao de 8 bits
   */
  cli();
  UCSR0B = 0;   // Desabilita TX e RX parra setar o Baud Rate
  UCSR0A = 0b10000010;            // Limpa flag TXC, seleciona velocidade normal e desabilita Multi-Processamento Comum
  UCSR0C = 0b00000110;   // Modo sincrono
  UBRR0 = 207;
  UCSR0B = 0b10011001;   // Transmissao e recepcao habilitados, UCSZ02 = 1 conclui a configuracao de 8 bits
  sei();
}

void enviar_USART(unsigned char dado[]){
  while(!( UCSR0A & (1<<UDRE0)));   // Enquanto o bit 5 estiver ativado
  UDR0 = dado;                      // Coloca o valor e o envia

}

void enviar_dados_USART_ln(unsigned char c[]){
  int i = 0;
  int tam = strlen(c);
  for(int i = 0; i < tam; i++){
    enviar_USART(c[i]);
  }
  // \n -> Para sair pula linha no terminal do arduino
  // \r -> Para sair pula linha no terminal do proteus
  enviar_USART('\n');
  enviar_USART('\r');
}

void enviar_dados_USART(unsigned char c[]){
  int i = 0;
  int tam = strlen(c);
  for(int i = 0; i < tam; i++){
    enviar_USART(c[i]);
  }
}


unsigned char receber_dados_USART(){
  while(!(UCSR0A & (1<<RXC0))); //Espera o dado ser recebido
  return UDR0;                  //Lê o dado recebido e retorna
}
// ------------------------------------- USART --------------------------------------------------------------------------


#endif
