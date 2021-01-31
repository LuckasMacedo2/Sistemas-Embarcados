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
static int tempo = 668;
static int i = 0;

// --- Variaveis globais ---

// --- Tarefas ---
void TaskFrente5( void *pvParameters );
void TaskFrente10( void *pvParameters );
void TaskDireita1( void *pvParameters );
void TaskDireita2( void *pvParameters );
// --- Tarefas ---

void setup() {
  
  Serial.begin(9600);
  
  while (!Serial) {
    // Espera o serial
  }
    xTaskCreate(
    TaskFrente10                    // Ponteiro para a funcao
    ,  (const portCHAR *)"Frente10"   // Nome da Task
    ,  128                          // Words de memoria alocada
    ,  NULL                         // Parametros que devem ser passados a tarefa na sua inicializacao
    ,  3                            // Prioridade da tarefa
    ,  NULL );                      // Handle da tarefa, opcional

  /*  xTaskCreate(
    TaskFrente5                    // Ponteiro para a funcao
    ,  (const portCHAR *)"Frente10"   // Nome da Task
    ,  128                          // Words de memoria alocada
    ,  NULL                         // Parametros que devem ser passados a tarefa na sua inicializacao
    ,  3                            // Prioridade da tarefa
    ,  NULL );                      // Handle da tarefa, opcional*/


    xTaskCreate(
    TaskDireita1                     // Ponteiro para a funcao
    ,  (const portCHAR *)"Direita1" // Nome da Task
    ,  128                          // Words de memoria alocada
    ,  NULL                         // Parametros que devem ser passados a tarefa na sua inicializacao
    ,  0                            // Prioridade da tarefa
    ,  NULL );                      // Handle da tarefa, opcional

    xTaskCreate(
    TaskDireita2                     // Ponteiro para a funcao
    ,  (const portCHAR *)"Direita2" // Nome da Task
    ,  128                          // Words de memoria alocada
    ,  NULL                         // Parametros que devem ser passados a tarefa na sua inicializacao
    ,  0                            // Prioridade da tarefa
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

void TaskFrente10(void *pvParameters)
{
  (void) pvParameters;
    
  for(;;)  {
    taskENTER_CRITICAL();
    Serial.println("Task Frente 10s");
    digitalWrite(MOTOR_DIR, HIGH);
    digitalWrite(MOTOR_ESQ, HIGH);
    vTaskDelay( 200 );
    taskEXIT_CRITICAL();
  }
}

void TaskDireita1(void *pvParameters)
{
  (void) pvParameters;
    
  for (;;)
  {
    taskENTER_CRITICAL();
    Serial.println("Task Direita 1");
    digitalWrite(MOTOR_DIR, HIGH);
    digitalWrite(MOTOR_ESQ, LOW);
    vTaskDelay(  600 );
    taskEXIT_CRITICAL();
    
  }
}


void TaskDireita2(void *pvParameters)
{
  (void) pvParameters;
    
  for (;;)
  {
    taskENTER_CRITICAL();
    Serial.println("Task Direita 2");
    digitalWrite(MOTOR_DIR, HIGH);
    digitalWrite(MOTOR_ESQ, LOW);
    vTaskDelay(  1000 );
    taskEXIT_CRITICAL();
    
  }
}
