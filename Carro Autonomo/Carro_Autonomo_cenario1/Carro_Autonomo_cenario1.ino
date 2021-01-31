/*
  Cenario 1
    Carro faz uma volta completa no quadrante esquerdo
  Tarefas:
      Esquerda -> O carro faz uma curva a esquerda. Tempo = 3 segundos
      Frente -> O carro segue em frente. Tempo = 13 segundos

    
*/

#include <Arduino_FreeRTOS.h>

// --- Variaveis globais ---
#define MOTOR_ESQ 6
#define MOTOR_DIR 5

// --- Variaveis globais ---

// --- Tarefas ---
void TaskFrente( void *pvParameters );
void TaskEsquerda( void *pvParameters );
// --- Tarefas ---

void setup() {
  
  Serial.begin(9600);
  
  while (!Serial) {
    // Espera o serial
  }

    xTaskCreate(
    TaskFrente                      // Ponteiro para a funcao
    ,  (const portCHAR *)"Frente"   // Nome da Task
    ,  128                          // Words de memoria alocada
    ,  NULL                         // Parametros que devem ser passados a tarefa na sua inicializacao
    ,  2                            // Prioridade da tarefa
    ,  NULL );                      // Handle da tarefa, opcional

  xTaskCreate(
    TaskEsquerda
    ,  (const portCHAR *) "Esquerda"
    ,  128  
    ,  NULL
    ,  1
    ,  NULL );

  // Definindo os motores como saída
  pinMode(MOTOR_ESQ, OUTPUT);
  pinMode(MOTOR_DIR, OUTPUT);
}

void loop()
{
  // Nao usado
}


/*--------------------------------------------------*/
/*---------------------- Tarefa --------------------*/
/*--------------------------------------------------*/

void TaskFrente(void *pvParameters)
{
  (void) pvParameters;
    
  for(;;)  {
    taskENTER_CRITICAL();
    Serial.println("Task Frente 13s");
    digitalWrite(MOTOR_DIR, HIGH);
    digitalWrite(MOTOR_ESQ, HIGH);
    vTaskDelay( 2000 / portTICK_PERIOD_MS );
    taskEXIT_CRITICAL();
  }
}

void TaskEsquerda(void *pvParameters)
{
  (void) pvParameters;
  int estado = 0;
    
  for (;;)
  {
    taskENTER_CRITICAL();
    Serial.println("Task Esquerda 32s");
    digitalWrite(MOTOR_DIR, LOW);
    digitalWrite(MOTOR_ESQ, HIGH);
    vTaskDelay( 10000 / portTICK_PERIOD_MS );
    taskEXIT_CRITICAL();
  }
}
