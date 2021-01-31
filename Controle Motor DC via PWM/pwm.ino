int st = 0;
char * dados = new char[16];
int num_RPM = 0;
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

// ------------------------------------ PWM -----------------------------------------------------------------------------
void cfg_PWM(){
  TCCR1A = 0b10000000;  /*0C1A habilitado, modo nao inversor, TOP = ICR1*/
  TCCR1B = 0b00010100;  /*Prescaler de 256*/
  ICR1 = 1875000;       /*Valor maximo da contagem, periodo de 1 minuto*/
  ciclo_ativo(1000);
  //TIMSK1 = 0b00000010;/*Habilita a interrupcao na compracao com OC1A*/
}

void ciclo_ativo(int n){
  OCR1A = n*1875000;
}
// ------------------------------------ PWM -----------------------------------------------------------------------------

// ------------------------------------ Outros --------------------------------------------------------------------------
void interacao(){
   if (st == 0){
      int escolha = atoi(dados);

      //enviar_dados_USART("Opcao Escolhida: ");
      enviar_dados_USART_ln(dados);
            
      if (escolha == 1)     // Esquerda
        PORTD = 0b10000000;
      else                  // Direita
        PORTD = 0b00000000;
      enviar_dados_USART("Informe a velocidade em RPM: ");
      st++;
   }else{
    if(st == 1){
      num_RPM = atoi(dados);
      cfg_PWM();
      //enviar_dados_USART("Velocidade Recebida: ");
      enviar_dados_USART_ln(dados);
      ciclo_ativo(num_RPM);
      st = 0;
      enviar_dados_USART_ln("Informe a direcao [1] Para esquerda ou [2] Para a direita");
      enviar_dados_USART("Opcao: ");
    }
   }
}

// ------------------------------------ Interruocao ---------------------------------------------------------------------
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
// ------------------------------------ Interruocao ---------------------------------------------------------------------


void cfg_PORTS(){
  /*
   * Modo PWM com correcao de fase
   */
  // D -> Controla a direcao do motor
  PORTD = 0b00000000;
  DDRD = 0b11111111;
  DDRB = 0b00000110; //pinos OC1B e OC1A (PB2 e PB1) como saída
  PORTB = 0b11111001; //zera saídas e habilita pull-ups nos pinos não utilizados
}

void setup() {
  // put your setup code here, to run once:
  cfg_PORTS();
  //cfg_PWM();
  cfg_USART();
  enviar_dados_USART_ln("Informe a direcao [1] Para esquerda ou [2] Para a direita");
  enviar_dados_USART("Opcao: ");
}

void loop() {
}
