#include <Wire.h>
#include <QueueArray.h>

int meu_endereco = 0;

static const int escravos[] = {2, 3, 4, 5};
static const int num_escravos = sizeof(escravos)/ sizeof(escravos[0]);
int queue[num_escravos]; // Armazena os enderecos em espera
int idx = 0;
volatile int tempo_espera = 0;
int escravo_atual = -1; // Indica o escravo que esta "conversando com o mestre"


static int * vetor_requisicoes = new int[num_escravos]; // Armazena a quantidade de vezes que foi perguntado para um escravo, se exceder MAX_REQUISICOES vezes aquele escravo se encontra offline*/
const int MAX_REQUISICOES = 2;                          // Indica a quantidade maxima de requisicoes a serem feitas antes de aquele escravo ser considerado offline

// Inicia o vetor de requisicoes
void init_requisicoes(){
  for(int i = 0; i < 0; i++){
    vetor_requisicoes[i] = 0;
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Mestre iniciando ...");
  
  Wire.begin(); 
  
  Wire.onReceive(receiveEvent);     

  init_requisicoes();
}

void transmitir(char msg[], int endereco){
    Serial.println("Mestre -> Enviando " + String(msg) + " para " + String(endereco));
    /*Transmissao dos dados*/
    Wire.beginTransmission(endereco); 
    Wire.write(msg);       
    Wire.endTransmission();    
    
    //delay(400);
    Serial.println();
    Serial.println("Mestre -> Transmissao para "+  String(endereco) + " finalizada");
    Serial.println();
}




void loop() {
  int relogio = 0;
  Serial.println("Mestre -> Relogio iniciado em " + String(relogio));

  // Passando tempo
  while(1){
    idx = 0;
    for (int i = 0; i < 50; i++){
      Serial.println("Mestre -> Relogio: " + String(relogio));
      relogio ++;
      if(relogio >= 10000)
         relogio = 0;
    }
    
    // Requisita o valor dos relogios
    Serial.println("Mestre -> Iniciando sincronizacao");
  
    for(int i = 0; i < num_escravos; i++){
      if (vetor_requisicoes[i] != MAX_REQUISICOES){ // Verifica se o escravo nao esta offline
        // Envia a solicitacao
        transmitir("A1", escravos[i]);
    
        // Espera ...
        for(tempo_espera; tempo_espera < 250; tempo_espera++)
          delay(2);
    
        // Mestre recebeu a resposta
        if(tempo_espera <= 251){  // Escravo nao respondeu
          vetor_requisicoes[i] ++;
        }
      }
    }
    Serial.println("Mestre -> Fim das requisicoes pelo valor do relogio");
  
    // Calcula a media dos valores dos relogios
    int media = 0;
    media += relogio;
  
    int i = 1, j;
    for (int k = 0; k < idx; k++){
      j = queue[k];
      media  += j;
      i ++;
      Serial.println("Mestre -> Valor: " + String(j));
    }
    relogio = media / i;
    Serial.println("Mestre -> Resultado: " + String(media / i));
    Serial.println("Mestre -> Valor: " + String(relogio));
    Serial.println("Mestre -> Quantidade de nos: " + String(i));
    Serial.println("Mestre -> Valor do relogio foi atualizado");
    Serial.println("Mestre -> Novo Valor: " + String(relogio));
    delay(50);
    // Atualiza o valor dos relogios
    for(int i = 0; i < num_escravos; i++){
      if (vetor_requisicoes[i] != MAX_REQUISICOES){ // Verifica se o escravo nao esta offline
        // Envia a solicitacao
        String tempo = String(relogio);
        char * msg = new char[5];
        tempo.toCharArray(msg, 5);
        transmitir(msg, escravos[i]);
      }
    }
    Serial.println("Mestre -> Fim da transmissao do relogio");
  }
}

void receiveEvent(int howMany) {
  int i = 0;
  char * msg =  new char[5];
  while (Wire.available()) { // loop through all but the last    
    msg[i] = Wire.read(); // receive byte as a character
    i ++;
  }
  int tempo = atoi(msg);
  queue[idx] = tempo;
  idx++;
  Serial.println("Mestre -> Quadro Recebido: " + String(msg));
  Serial.println();
  tempo_espera = 500;  
}
