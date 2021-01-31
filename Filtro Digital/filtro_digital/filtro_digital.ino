char * dados = new char[16];
/*  0 -> Esperando o tamanho do vetor x
 *  1 -> Entrando com todos os valores de x
 *  2 -> Esperando o tamanho do vetor h
 *  3 -> Entrando com todos os valores de h
 *  4 -> Calcula e mostra a convolucao
 */
const int idxMax = 10;
float x[idxMax];

float h[] = {
-0.0039479588039812519,
0.020265964382985422, 
-0.056673697806016526, 
0.10937295136286738,   
-0.15851869967276119,  
0.1787878355169861,    
-0.15851869967276119,  
0.10937295136286738,  
-0.056673697806016526, 
0.020265964382985422, 
-0.0039479588039812519
};
int tamX = 0;
int indX = 0;
int indH = 0;
int tamH = 11;
int index = 0;

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

void enviar_dados_USART_ln(char c[]){
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

void enviar_dados_USART(char c[]){
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
  TCNT1 = 65536 - (16000000)/ (f * 256) - 1;
}

void cfg_Timer1(){
  /* Configuracao adotada
   * TCCR1A -> Operacao normal
   * TCCR1B -> Prescaler de 256
   * TIMSK1 -> Interrupcao de overflow ativada
   */
  cli();  
  TCCR1A = 0;             // Configura o modo de operacao do Timmer para modo de operacao normal, contador neste caso
  TCCR1B = 0b00000100;    // Configura o prescaler como 256

  // Habilita a interrupcao de estouro
  TIMSK1 = 0b00000001;

  timmer1_reset();        // Resta o tempo
  sei();
}
// ------------------------------------- Timmer -------------------------------------------------------------------------

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


// ------------------------------------- Convolucao ---------------------------------------------------------------------
float * soma_convolucao(float x[], int tamX, float h[], int tamH){
    int tamanho = tamX + tamH - 1;
    float * resposta = new float[tamanho];// Vetor de resposta
    int inicio = 0;                       // Inicio do vetor
   // int limite = -tamH - 1;               // "Inverte" o vetor h
    for (int k = 0; k < tamanho; k ++){   // Preenche o vetor de resposta
        float sum = 0;
        int count = 0;
        for (int n = inicio; n >= 0; n--) // Multiplica os dois vetores
        {
            if (count < tamX){            // Garante que so serao pegos valores existentes em ambos os vetores
                if (n >= tamH)            // Se n for maior que o tamanho de H pega 0
                    sum += x[count] * 0;
                else                      // Senao multiplca, existem valores para os dois numeros
                    sum += x[count] * h[n];
                count++;
            }
        }
        resposta[k] = sum;
        inicio += 1;
    }
    return resposta;
}
// ------------------------------------- Convolucao ---------------------------------------------------------------------

// ------------------------------------- Outros -------------------------------------------------------------------------

void imprimir_vetor(float * vetor, float tam_vetor){
  char * aux = new char[16];
  for(int i = 0; i < tam_vetor; i++){

    aux = new char[16];
    dtostrf(vetor[i], 6, 10, aux);
    enviar_dados_USART_ln(aux);
  }
}
// ------------------------------------- Outros -------------------------------------------------------------------------



// ------------------------------------- Interrupcoes -------------------------------------------------------------------
// Tratamento de interrupcao
ISR(TIMER1_OVF_vect){               // Overflow Timmer1
  // Houve um overflow em timmer1
  timmer1_reset();                  // Reseta o Timmer1
  //ADCSRA |= (1 << ADSC);          // Mantem o valor de ADCSRA e desloca ADSC em 1, ou seja, seta ADSC para um da inicio a conversao
}

ISR (ADC_vect){                     // Conversao AD
   
    x[index] =  ADCW * 5.0 / 1024.0 - 2;  // ADCW -> Fornecida pelo compilador
    index ++;
    tamX++;
    if (index == idxMax){
    imprimir_vetor(soma_convolucao(x, tamX, h, tamH), tamX + tamH - 1);
      index = 0;
      tamX = 0;
    }
    
}
// ------------------------------------- Interrupcoes -------------------------------------------------------------------

void setup() {
 cfg_USART();
 cfg_Timer1();
 cfg_convAD();
}


void loop() {
 
}
