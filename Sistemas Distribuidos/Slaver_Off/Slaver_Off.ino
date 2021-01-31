// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.
#include <Wire.h>

#define LED 13

int meu_endereco = 5;
const int END_MESTRE = 0;

void transmitir(char tipo){
  char * msg = new char[2];
  msg[0] = meu_endereco + '0';  // Endereco
  msg[1] = tipo;                // Tipo de solicitacao
  Serial.println("ESCRAVO " + String(meu_endereco) + " -> Enviando " + String(msg) + " ao mestre");
  Wire.beginTransmission(END_MESTRE); 
  Wire.write(msg);       
  Wire.endTransmission();    
  delay(200);
  Serial.println("ESCRAVO " + String(meu_endereco) + " -> Transmissao terminada");
  Serial.println();   
}

void setup() {
  Serial.begin(9600);
  Serial.println("ESCRAVO " + String(meu_endereco) + " -> iniciando...");
  Wire.begin(meu_endereco);                
  Wire.onReceive(receiveEvent); 

  pinMode(LED, OUTPUT); 

  Serial.println();      
}

int usar = 0;

int teste = 0;

void loop() {
  if (usar == -1){
    if (teste == 1){
      int usar_ou_nao = random(2);
      if (usar_ou_nao == 1)
          Serial.println("ESCRAVO " + String(meu_endereco) + " -> Usarei o recurso, tirei: " + String(usar_ou_nao));
      else
          Serial.println("ESCRAVO " + String(meu_endereco) + " -> Nao usarei o recurso, tirei: " + String(usar_ou_nao));
      delay(300);
      transmitir(usar_ou_nao + '0');  // Envia sim ou nao para o uso do recurso
      usar = 0;
      // Usa o LED
      if(usar_ou_nao == 1){
        int tempo = random(400);
        Serial.println("ESCRAVO " + String(meu_endereco) + " -> Usando o recurso por " + String(tempo)  + "ms");
        digitalWrite(LED, HIGH);
        delay(300);
        digitalWrite(LED, LOW);
        Serial.println("ESCRAVO " + String(meu_endereco) + " -> Recurso liberado");
        usar = 0;
      }
      teste ++;
    }else{
      teste ++;
    }
  }
}

void receiveEvent(int howMany) {
  int i = 0;
  char * msg = new char[2];
  while (Wire.available()) { // loop through all but the last    
    msg[i] = Wire.read(); // receive byte as a character
    i ++;
  }
  Serial.println("ESCRAVO " + String(meu_endereco) + " -> Recebido " +  String(msg));
 
    if (msg[0] == '0' && msg[1] == '0') // Aceita a vez dele
      usar = 1;
  delay(300);

}
