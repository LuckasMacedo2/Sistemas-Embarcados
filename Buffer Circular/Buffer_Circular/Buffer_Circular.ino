#include "USART.h"
#include "buffer_circular.h"

char * dados = new char[16];
/*  0 -> Esperando o tamanho do vetor x
 *  1 -> Entrando com todos os valores de x
 *  2 -> Esperando o tamanho do vetor h
 *  3 -> Entrando com todos os valores de h
 *  4 -> Calcula e mostra a convolucao
 */
const int idxMax = 10;
float x[idxMax];

long double y = 0;

int tamX = 0;
int indX = 0;
int index = 0;


// ------------------------------------- Interrupcoes -------------------------------------------------------------------

ISR(USART_RX_vect){
  unsigned char caracter = UDR0;  // Valor lido esta aqui
  if  (caracter == '\n'){
    interacao();
    index = 0;
    dados = new char[16];         // Zera
  }else{
    dados[index] = caracter;
    index ++;
  }
}
// ------------------------------------- Interrupcoes -------------------------------------------------------------------

void interacao(){
  double valor = atoi(dados);
  //atualiza_buffer(valor);
  fir(valor);

  // ------
  enviar_dados_USART("Recebido: ");
  enviar_dados_USART_ln(dados);
  imprimir_vetor(buffer_circular, ORDEM_FILTRO - 1);
  enviar_dados_USART_ln("");
}


void imprimir_vetor(double * vetor, int tam_vetor){
  char * aux = new char[16];
  dtostrf(posicao, 6, 0, aux);
  enviar_dados_USART_ln(aux);
  enviar_dados_USART("[");
  
  
  for(int i = 0; i < ORDEM_FILTRO; i++){
    aux = new char[16];
    dtostrf(get_value(i), 6, 0, aux);
    enviar_dados_USART(aux);
    enviar_dados_USART(" ");
  }
  enviar_dados_USART("]");

  enviar_dados_USART_ln("[");
  for(int i = 0; i < ORDEM_FILTRO; i++){
    aux = new char[16];
    dtostrf(buffer_circular[i], 6, 0, aux);
    enviar_dados_USART(aux);
    enviar_dados_USART(" ");
  }
  enviar_dados_USART("]-----");
}


void setup() {
 cfg_USART();
 SREG = 0b10000000;
 enviar_dados_USART_ln("Teste do buffer circular ");
}

void loop() {
// put your main code here, to run repeatedly:

}
