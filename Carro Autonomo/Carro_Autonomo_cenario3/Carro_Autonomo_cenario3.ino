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
void TaskEsquerda( void *pvParameters );
void TaskRe( void *pvParameters );
// --- Tarefas ---

void setup() {
  
  Serial.begin(9600);
  
  while (!Serial) {
    // Espera o serial
  }
  

    xTaskCreate(
    TaskEsquerda                    // Ponteiro para a funcao
    ,  (const portCHAR *)"Esquerda"  // Nome da Task
    ,  128                          // Words de memoria alocada
    ,  NULL                         // Parametros que devem ser passados a tarefa na sua inicializacao
    ,  1                            // Prioridade da tarefa
    ,  NULL );                      // Handle da tarefa, opcional

    xTaskCreate(
    TaskRe                          // Ponteiro para a funcao
    ,  (const portCHAR *)"Re"  // Nome da Task
    ,  128                          // Words de memoria alocada
    ,  NULL                         // Parametros que devem ser passados a tarefa na sua inicializacao
    ,  2                            // Prioridade da tarefa
    ,  NULL );                      // Handle da tarefa, opcional
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

void TaskEsquerda(void *pvParameters)
{
  (void) pvParameters;
    
  for(;;)  {
    taskENTER_CRITICAL();
    Serial.println("Task Esquerda");
    digitalWrite(MOTOR_DIR, LOW);
    digitalWrite(MOTOR_ESQ, HIGH);
    vTaskDelay( 10000 / portTICK_PERIOD_MS );
    taskEXIT_CRITICAL();
  }
}

void TaskRe(void *pvParameters)
{
  (void) pvParameters;
  int estado = 0;
    
  for (;;)
  {
    taskENTER_CRITICAL();
    Serial.println("Task Re");
    digitalWrite(MOTOR_DIR, LOW);
    digitalWrite(MOTOR_ESQ, LOW);
    vTaskDelay ( 2000 / portTICK_PERIOD_MS );
    taskEXIT_CRITICAL();
  }
}
