int valor_recebido = 0;
char * dados = new char[16];
int st = 0;
/*  0 -> Esperando o tamanho do vetor x
 *  1 -> Entrando com todos os valores de x
 *  2 -> Esperando o tamanho do vetor h
 *  3 -> Entrando com todos os valores de h
 *  4 -> Calcula e mostra a convolucao
 */
int * x;
int * h;
int tamX = 0;
int indX = 0;
int indH = 0;
int tamH = 0;
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

// ------------------------------------- Convolucao ---------------------------------------------------------------------
int * soma_convolucao(int x[], int tamX, int h[], int tamH){
    int tamanho = tamX + tamH - 1;
    int * resposta = new int[tamanho];    // Vetor de resposta
    int inicio = 0;                       // Inicio do vetor
    int limite = -tamH - 1;               // "Inverte" o vetor h
    for (int k = 0; k < tamanho; k ++){   // Preenche o vetor de resposta
        int sum = 0;
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

void imprimir_vetor(int * vetor, int tam_vetor){
  enviar_dados_USART_ln("Vetor: ");
  char * aux = new char[16];
  for(int i = 0; i < tam_vetor; i++){
    enviar_dados_USART("Vetor[");
    dtostrf(i, 6, 0, aux);
    enviar_dados_USART(aux);
    enviar_dados_USART("] = ");
    aux = new char[16];
    dtostrf(vetor[i], 6, 0, aux);
    enviar_dados_USART_ln(aux);
    //enviar_dados_USART_ln("");
  }
}

void interacao(){
  //char aux[16];

 //
    if (st == 0){     // Esperando o tamanho de X
      tamX = atoi(dados);
      x = new int[tamX];
      // ------
      enviar_dados_USART("Tamanho de x recebido: ");
      //dtostrf(tamX, 6, 0, aux);
      enviar_dados_USART_ln(dados);
      // ------
      st ++;
      enviar_dados_USART_ln("Informe os valores dos elementos: ");
      
    }  
    
    else if (st == 1){ // Recebendo os valores que compoem o vetor
      int valor = atoi(dados);
      enviar_dados_USART("Recebido: ");
       //dtostrf(valor, 6, 0, aux);
      enviar_dados_USART_ln(dados);

      x[indX] = valor;
      indX ++;

      if (indX == tamX) // Recebido todos os valores de x
      {
        st ++;
        indX = 0;
        enviar_dados_USART_ln("Vetor x recebido: ");
        imprimir_vetor(x, tamX);
        enviar_dados_USART_ln("Informe o tamanho de h: ");
      }
    }

    else if(st == 2){   // Esperando o valor do tamanho de h
      tamH = atoi(dados);
      h = new int[tamH];
      // ------
      enviar_dados_USART("Tamanho de h recebido: ");
      //dtostrf(tamX, 6, 0, aux);
      enviar_dados_USART_ln(dados);
      // ------
      st ++;
      enviar_dados_USART_ln("Informe os valores dos elementos: ");
     
    }

    else if (st == 3){
      int valor = atoi(dados);
      enviar_dados_USART("Recebido: ");
       //dtostrf(valor, 6, 0, aux);
      enviar_dados_USART_ln(dados);

      h[indH] = valor;
      indH ++;

      if (indH == tamH) // Recebido todos os valores de x
      {
        st ++;
        indH = 0;
        enviar_dados_USART_ln("Vetor h recebido: ");
        imprimir_vetor(h, tamH);
        enviar_dados_USART_ln("Calculando a convolucao ...");
      }
    }
    if (st == 4){
      int * resposta;
      resposta = soma_convolucao(x, tamX, h, tamH);
      imprimir_vetor(resposta, tamX + tamH - 1);
    }
}
// ------------------------------------- Outros -------------------------------------------------------------------------

// ------------------------------------- Interrupcao --------------------------------------------------------------------
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
// ------------------------------------- Interrupcao --------------------------------------------------------------------



char * ler_valor_serial (){
  char * valor = new char[16];
  int i = 0;
  char caracter = "";

  
  enviar_dados_USART("Valor Recebido: ");
  enviar_dados_USART(valor);
  valor_recebido = atoi(valor);
}

void receber_valor_vetor(int * vetor, int tam_vetor){
  int mostrar = 0;
  for(int i = 0; i < tam_vetor;){
    //if (mostrar == 0 && i != 0){
      enviar_dados_USART("Valor ");
      dtostrf(i+1, 6, 2, dados);
      enviar_dados_USART(dados);
      enviar_dados_USART(" do vetor: ");
      mostrar ++;
  }

}

void setup() {
 cfg_USART();
 enviar_dados_USART_ln("Informe o tamanho do vetor 1: ");
}


void loop() {
 
}
