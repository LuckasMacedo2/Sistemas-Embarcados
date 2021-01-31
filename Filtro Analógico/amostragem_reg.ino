/* DDRXs -> Reg responsavel por determinar se os pinos de um PORT serao entrada ou saida
 *  0 -> Entrada
 *  1 -> Saida
 *  
 * PORTX -> Reg que define se o pino está como alto ou como baixo
 *  0 -> Baixo
 *  1 ->  Alto
 * 
 * PINX -> Guarda o estado logico do pino
 * 
 *  ------ Interrupção ------
 *  Registrador de interrupcao
 *  <7> I -> Ativa a interrupcao global, 1 -> Ativa as interrupcoes
 *  <6> T -> Bit de copia
 *  <5> 
 * 
 *  ----- Timer1 ------
 * Controlam a operação do timmer1
 *        
 * TIMSK1: Registrador de máscara de interrupcao 
 * <5> ICIE1 -> Habilita as interrupções do timmer1
 * <2> OCIE1B -> Saída do temporizador / contador1
 * <1> OCIE1A -> Saída do temporizador / contador1 Comparar a correspondência do canal A Ativar interrupção     
 * <0> TOIE1 -> Ativação de interrupção de estouro do timer / contador1.
 *    1 -> Ativa
 *    
 * TIFR1: Registrador de flag de interrupcao
 * <5> ->ICF1: Sinalizador de Captura de Entrada Temporizador / Contador1. O bit ICF1 é definido quando um evento Capture ocorre no pino ICP1.
 * <2> -> OCF1B: Saída do timer / contador1 compara o sinalizador de correspondência do canal B. O bit OCF1B é definido quando ocorre uma comparação entre o timer / contador1 e os dados no OCR1B. 
 * <1> -> OCF1A: Saída do timer / contador1 compara o sinalizador de correspondência do canal A. O bit OCF1A é definido quando ocorre uma comparação entre o Timer / Counter1 e os dados no OCR1A.
 * <0> -> TOV1: Sinalizador de estouro do temporizador / contador1. O bit TOV1 é definido quando ocorre um estouro no temporizador / contador1. 
 * 
 * TCCR1A
 * <7:6> -> 00: Operacao normal
 * <5:4> -> 00: |||
 * <1:0> -> 00: |||
 * 
 * TCCR1B
 * <7> -> ICNC1: Input Capture Noise Canceler
 * <6> -> ICES1: Seleção de borda de captura de entrada. Esse bit seleciona qual borda do pino de captura de entrada (ICP1) é usada para disparar um evento de captura.
 * <4:3> -> WGM13-2: Modo de geração de forma de onda
 * <2:0> CS12-0: Seleção de relógio.
 * 
 * ------- Conversor AD -------
 * ADMUX: Registador de seleção do multiplexador ADC
 * <7:6> -> REFS1-0: Bits de seleção de referência.
 * <5> -> ADLAR: ADC Left Adjust Result
 * <3:0> -> MUX3-0: Bits de seleção de canal analógico
 *      0000 -> ADC0
 *      0001 -> ADC1
 *      ...
 * ADCSRA -> Registro de status de controle
 * <7> -> ADEN: Ativar ADC.
 *      0 -> Desliga
 *      1 -> Liga
 * <6> -> ADSC: ADC inicia a conversão
 *      0 -> Desliga
 *      1 -> Inicia
 * <5> -> ADATE: Ativação automática do ADC, o ADC começará a converter na borda positiva
 *      0 -> Manual
 *      1 -> Automatico
 * <4> -> ADIF: Sinalizador de interrupção do ADC. Esse bit é definido quando uma conversão ADC é concluída e os registros de dados são atualizados
 * <3> -> ADIE: Ativação de interrupção ADC.
 *      0 -> Desliga
 *      1 -> Liga
 * <2:0> -> ADPS2-0: bits de seleção do ADC Pre-scaler
 *      111 -> 128 de prescaler
 * 
 * ADCH AND ADCL -> Guardam o valor da conversao
 * 
 * ADCSRB -> Controle do ADC
 * <6> -> ACME: Ativação do Multiplexador Comparador Analógico.
 * <2:0> -> ADTS2-0: Fonte de acionamento automático ADC.
 *      110 -> Timmer1 Overflow
 * 
 * <5:0> DIDR0 Registrador: ADC5D-ADC0D: Desativação da entrada digital ADC5-0. Quando esse bit é gravado na lógica um, o buffer de entrada digital no pino ADC correspondente é desativado
 * 
 * ------------- Comunicacao Serial ----------------------
 * TWI -> Interface serial de dois fios
 * 
 * TWBR -> Registrador da taxa de bit
 * <7:0> -> TWBR: Taxa de bits TWI. TWBR seleciona o fator de divisão para o gerador de taxa de bits. O gerador de taxa de bits é um divisor de frequência que gera a freqüência do relógio SCL nos modos Mestre
 * fscl = 16 M / (16 + 2 * (TWBR) * Prescaler) 
 * 
 * TWCR -> Registrador de controle TWI
 * <6> -> TWEA: TWI Ativar bit de reconhecimento. Se o bit TWEA for gravado em um, o pulso ACK será gerado no barramento TWI se as seguintes condições forem atendidas.
 *    1. O endereço escravo do dispositivo foi recebido.
 *    2. Uma chamada geral foi recebida enquanto o bit TWGCE no TWAR está definido.
 *    3. Um byte de dados foi recebido no modo Master Receiver ou Slave Receiver.
 *    0 -> Desconecta virtualmente 
 * <5> -> TWSTA: bit de condição TWI START. Deve ser resetado via software. Inicia
 * <4> -> TWSTO: TWI STOP Condição Bit. Para
 * <3> -> TWWC: bit de sinalizacao
 * <2> -> TWEN: TWI Ativar Bit. O bit TWEN habilita a operação TWI e ativa a interface TWI.
 *    1 -> Ativa
 *    0 -> Desativa
 *    
 * TWSR -> Registrador de staus
 * <7:3> -> TWS7-3: Status TWI. Esses 5 bits refletem o status da lógica TWI e do barramento serial de 2 fios.
 * <1:0> -> TWPS1-0: bits pré-dimensionadores TWI. Esses bits podem ser lidos e gravados e controlam o pré-dimensionador da taxa de bits.
 * 
 * TWDR -> Registrador de dados
 * <7:0> -> TWD7-0: dados TWI. No modo de transmissão, o TWDR contém o próximo byte a ser transmitido. No modo de recebimento, o TWDR contém o último byte recebido.
 *   
 * TWAR -> Registrador de enderecos da interface escrava
 * <7:1> -> TWA6-0: Endereço do Escravo TWI. O TWAR deve ser carregado com o endereço escravo de 7 bits ao qual o TWI responderá quando programado como transmissor ou receptor escravo, e não é necessário nos modos mestre.
 * <0> -> TWGCE: Bit de ativação do reconhecimento geral de chamadas TWI. Este bit é usado para habilitar o reconhecimento do endereço de chamada geral (0x00).
 * 
 * TWAMR -> Registrador de mascara de endereco do escravo da interface
 * <7:0> -> TWAM6-0: máscara de endereço TWI. O TWAMR pode ser carregado com uma máscara de endereço escravo de 7 bits.
 * 
 * SPCR -> Registrador de controle SPI
 * <7> -> SPE: SPI ativado. 
 *    0 -> Desativado
 *    1 -> Ativado
 * <5> -> DORD: Pedido de Dados. Quando o bit WORD é gravado em um, o LSB da palavra de dados é transmitido primeiro. Quando o bit DORD é gravado em zero, o MSB da palavra de dados é transmitido primeiro.    
 * <4> -> MSTR: Seleção Master / Escravo.Este bit seleciona o modo Master SPI quando gravado em um, e o modo Slave SPI quando gravado em zero lógico.
 * <3> -> CPOL: Polaridade do relógio. Quando esse bit é gravado em um, o SCK fica alto quando ocioso. Quando o CPOL é gravado em zero, o SCK fica baixo quando ocioso
 * <2> -> CPHA: Fase do Relógio. As configurações CPHA determinam se os dados são amostrados na borda inicial (primeira) ou à direita (última) do SCK. Quando o CPHA é gravado em zero, os dados são amostrados na borda principal. Quando o CPHA é gravado em um, os dados são amostrados na borda à direita.
 * <1:0> -> SPR1-0: Bits de seleção da taxa de clock SPI. Esses dois bits controlam a taxa SCK do dispositivo configurado como um mestre. SPR1: 0 não tem efeito no escravo.
 * 
 * 
 * SPSR registrador de status do SPI
 * <7> -> WCOL: Write COLlision Flag. O bit WCOL será definido se o SPI Data Register (SPDR) for gravado durante uma transferência de dados.
 * <0> -> SPI2X: bit de velocidade SPI duplo. Quando esse bit é escrito de uma lógica, a velocidade SPI (SCK Frequency) será dobrada quando o SPI estiver no modo Master.
 * 
 * SPDR -> Registrador de dados SPI
 * <7:0> ->SPD7-0: dados SPI. O SPI Data Register é um registro de leitura / gravação usado para transferência de dados entre o arquivo de registro e o SPI Shift Register. A gravação no registro inicia a transmissão de dados. A leitura do registro faz com que o buffer Shift Register Receive seja lido.
 * 
 * UDR0 -> Registrador de dados de E/S
 * <7:0> UD7-0: Dados USART0.O registro de buffer de dados de transmissão USART0 e o registro de buffer de dados USART0 compartilham o mesmo endereço de E / S referido como USART0 Data Register ou UDR0. O Transmit Data Buffer Register (TXB) será o destino dos dados gravados no local do Registro UDR0. A leitura do local de registro UDR0 retornará o conteúdo do registro de buffer de dados de recebimento (RXB).
 * 
 * UCSR0A -> Registrador de estado e controle do USART0 A
 * <7> -> FE0: Erro de quadro. Esse bit é definido se o próximo caractere no buffer de recebimento tiver um erro de quadro quando recebido
 * <3> -> DOR0: Excesso de dados. Este bit é definido se uma condição de Excesso de dados for detectada.
 * <2> -> UPE0: USART0 Erro de paridade. Esse bit é definido se o próximo caractere no buffer de recebimento tiver um erro de paridade quando recebido e a verificação de paridade estiver ativada nesse ponto (UPM01 = 1). Este bit é válido até que o buffer de recebimento (UDR0) seja lido. Sempre defina esse bit como zero ao gravar em UCSR0A.
 * <1> -> U2X0: Dobra a velocidade de transmissão USART0.Este bit só tem efeito para a operação assíncrona
 * <0> -> MPCM0: Modo de comunicação multiprocessador. Este bit ativa o modo de comunicação multiprocessador. 
 * 
 * UCSR0B -> Registrador de estado e controle do USART0 B
 * <4> -> RXEN0: USART0 Ativar receptor. Escrever este bit em um habilita o receptor USART0.
 * <3> -> TXEN0: USART0 Transmissor ativado. Escrever este bit em um habilita o transmissor USART0.
 * <2> -> UCSZ02: USART0 Tamanho do caractere. O bit UCSZ02 combinado com os bits UCSZ01: 0 no UCSR0C define o número de bits de dados (caractere SiZe) em um quadro usado pelo receptor e pelo transmissor.
 * <1> -> RXB80: USART0 Recebe o bit de dados 8. O RXB80 é o nono bit de dados do caractere recebido ao operar com quadros seriais com nove bits de dados. Ele deve ser lido antes de ler os bits baixos do UDR0.
 * <0> -> TXB80: USART0 Transmitir bit de dados 8. TXB80 é o nono bit de dados no caractere a ser transmitido ao operar com quadros seriais com nove bits de dados. Ele deve ser escrito antes de gravar os bits baixos em UDR0.
 * 
 * UCSR0C -> Registrador de estado e controle do USART0 C
 * <7:6> -> UMSEL01-0: USART0 Seleciona bits de modo. Esses bits selecionam o modo de operação do USART0
 * <5:4> -> UPM01-0: USART0 Modo de paridade. Esses bits permitem e definem o tipo de geração e verificação de paridade. Se ativado, o transmissor irá gerar e enviar automaticamente a paridade dos bits de dados transmitidos dentro de cada quadro. O receptor irá gerar um valor de paridade para os dados recebidos e compará-lo com a configuração UPM0. Se uma incompatibilidade for detectada, o sinalizador UPE0 no UCSR0A será definido.
 * <3> -> USBS0: USART0 Stop Bit Select. Este bit seleciona o número de bits de parada a serem inseridos pelo transmissor. O receptor ignora essa configuração. Se USBS0 for apagado, haverá 1 bit de parada. Se USBS0 estiver definido, existem 2 bits de parada.
 * <2:1> -> UCSZ01-0: USART0 Tamanho do caractere. Os bits UCSZ01: 0 combinados com o bit UCSZ02 no UCSR0B definem o número de bits de dados (caractere SiZe) em um quadro usado pelo receptor e pelo transmissor.
 * <0> -> UCPOL0: USART0 Polaridade do relógio. Este bit é usado apenas para o modo síncrono. Escreva esse bit em zero quando o modo assíncrono é usado. O bit UCPOL0 define o relacionamento entre a alteração na saída de dados e a amostra de entrada de dados e o relógio síncrono (XCK0).
 * 
 * UBRR0H e UBRR0L -> Registradores de baud rate
 * UBRR011-0: Bits de taxa de transmissão USART0. Este é um registro de 12 bits que contém a taxa de transmissão USART0. O UBRR0H contém os quatro bits mais significativos e o UBRR0L contém os oito bits menos significativos da taxa de transmissão USART0.
 * 
 * UCRSA -> Contem os dados dos status
 * UCRSB e UCRSA -> Contem o conjunto de configuracoes
 * 
 * 
 * 
 * ########
 *  ADCW -> Contém os valores de ADCH e ADCL corretamente
 */

#include<stdio.h> // sprintf
#include<string.h>

// Teste
int bit = 0;
int index = 0;
int l_teste = 1;

// Frequencia do crystal do arduino UNO
long int fosc = 16000000;

// Resultado da conversao AD
volatile static char dados[16];


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

// ------------------------------------- USART --------------------------------------------------------------------------
void cfg_USART(){
  /* Configuracao adotada
   * UCSR0A -> Habilitada a transmissao com 2 vezes mais velociadade
   * UCSR0B -> Recepcao e transmissao habilitada, habilitada a interrupcao de transmissao completa, transmissao de 8 bits
   * ADCSRB -> Configurado para comersar a Conv. AD quando houver estouro do Timmer1
   */
  cli();
  UCSR0B = 0;            // Desabilita TX e RX parra setar o Baud Rate
  UCSR0A = 2;            // Limpa flag TXC, seleciona velocidade normal e desabilita Multi-Processamento Comum
  UCSR0C = 0b00000100;   // Modo sincrono
  UBRR0 = 207;
  UCSR0B = 0b11001101;   // Transmissao e recepcao habilitados, UCSZ02 = 1 conclui a configuracao de 8 bits
  sei();
}

//  Nao usado
void enviar_USART(unsigned char dado[]){
  while(!( UCSR0A & (1<<UDRE0)));   // Enquanto o bit 5 estiver ativado
  UDR0 = dado;                      // Coloca o valor e o envia

}

//  Nao usado
void enviar_dados_USART(char c[]){
  int i = 0;
  int tam = strlen(c);
  for(int i = 0; i < tam; i++){
    enviar_USART(c[i]);
  }
}
// ------------------------------------- USART --------------------------------------------------------------------------


// ------------------------------------- Interrupcoes -------------------------------------------------------------------
// Tratamento de interrupcao
ISR(TIMER1_OVF_vect){               // Overflow Timmer1
  // Houve um overflow em timmer1
  timmer1_reset();                  // Reseta o Timmer1
  //ADCSRA |= (1 << ADSC);          // Mantem o valor de ADCSRA e desloca ADSC em 1, ou seja, seta ADSC para um da inicio a conversao
}

ISR (ADC_vect){                     // Conversao AD
    //while (ADCSRA & (1 << ADSC));
    float v = ADCW * 5.0 / 1024.0;  // ADCW -> Fornecida pelo compilador
    char c[16];
    v = v - 2;
    dtostrf(v, 6, 2, dados);
    UCSR0B |= (1 << UDRIE0);        // Ativa a flag de envio
}

ISR(USART_UDRE_vect){
  // Transmite os dados
  int tam = strlen(dados);
  for(int i = 0; i < tam; i++){
      while(!( UCSR0A & (1<<UDRE0)));   // Enquanto o bit 5 estiver ativado
      UDR0 = dados[i];                  // Coloca o valor e o envia 
  }
  
  UCSR0B &= ~(1 << UDRIE0);
}
// ------------------------------------- Interrupcoes -------------------------------------------------------------------

void cfg_ports(){
  DDRD = 0b11111111;
  PORTD = 0;
}

void setup() {
  // Configuracoes
  cfg_Timer1();
  cfg_ports();
  cfg_convAD();
  
  cfg_USART();
  SREG|=0x80;                             //Activa as interrupções globais
  
}

void loop() {
  // put your main code here, to run repeatedly:
}
