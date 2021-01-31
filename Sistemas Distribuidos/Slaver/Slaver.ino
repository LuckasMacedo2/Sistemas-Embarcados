#include <Wire.h>

#define LED 13

int meu_endereco = 5;
const int END_MESTRE = 0;
volatile int relogio; // Relogio que marca o tempo

void setup() {
  randomSeed(4);
  Serial.begin(9600);
  Serial.println("ESCRAVO " + String(meu_endereco) + " -> iniciando...");
  Wire.begin(meu_endereco);                
  Wire.onReceive(receiveEvent); 
  pinMode(LED, OUTPUT); 
  relogio = random(9999);
  Serial.println("ESCRAVO " + String(meu_endereco) + " -> Relogio iniciado em " + String(relogio));
  Serial.println();      
}

void transmitir(char msg[]){
  Serial.println("ESCRAVO " + String(meu_endereco) + " -> Enviando " + String(msg) + " ao mestre");
  
  Wire.beginTransmission(END_MESTRE); 
  Wire.write(msg);       
  Wire.endTransmission();    
  delay(200);
  
  Serial.println("ESCRAVO " + String(meu_endereco) + " -> Transmissao terminada");
  Serial.println();   
}



volatile int enviar_receber = -1; // 0 = Enviar  
                         // 1 = Receber

void loop() {
  if (enviar_receber == 0){
    String tempo = String(relogio);
    char * msg = new char[5];
    tempo.toCharArray(msg, 5);
    transmitir(msg);
    enviar_receber = 1;
  }else{
      if (enviar_receber == -1){
        delay(1);
        relogio++;
        if(relogio >= 10000)
          relogio = 0;
        Serial.println("ESCRAVO " + String(meu_endereco) + " -> Relogio: " + String(relogio));
      }
  }   
}

void receiveEvent(int howMany) {
  int i = 0;
  char * msg = new char[5];

  // Recebe os dados do barramento
  while (Wire.available()) {
    msg[i] = Wire.read(); 
    i ++;
  }
  Serial.println("ESCRAVO " + String(meu_endereco) + " -> Recebido " +  String(msg));

  // Verifica as mensagens
  /*  MSG -> Significado
   * 'A1' -> Qual o seu relogio?
   */
  Serial.println();
  if (msg[0] == 'A' && msg[1] == '1')   // Enviar o valor do relogio
    enviar_receber = 0;
  else{                                  // Atualiza o relogio
    Serial.println("ESCRAVO " + String(meu_endereco) + " -> Atualizado o valor do relogio a partir do mestre");
    relogio = atoi(msg);
    Serial.println("ESCRAVO " + String(meu_endereco) + " -> Novo Relogio: " + String(relogio));
    enviar_receber = -1;
  }
  Serial.println();
}
