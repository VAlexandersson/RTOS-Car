#include <Arduino.h>
#include <IRremote.h>
#include <Arduino_FreeRTOS.h>
#include <event_groups.h>



#define   L_SPEED           2 // ENA
#define   L_FORWARD         3
#define   L_REVERSE         4

#define   R_FORWARD         5
#define   R_REVERSE         6
#define   R_SPEED           7  // ENB 

#define   ECHO_PIN          8
#define   TRIG_PIN          9

uint32_t g_speed = 200;


uint32_t g_distance;

TaskHandle_t h_distancetask = NULL;

void vDistanceTask( void* p );

void setup() {
  Serial.begin(9600);

 // pinMode(LED_BUILTIN, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(L_SPEED, OUTPUT);
  pinMode(L_FORWARD, OUTPUT);
  pinMode(L_REVERSE, OUTPUT);

  pinMode(R_SPEED, OUTPUT);
  pinMode(R_FORWARD, OUTPUT);
  pinMode(R_REVERSE, OUTPUT);

  digitalWrite(TRIG_PIN, LOW);

  digitalWrite(L_FORWARD, LOW);
  digitalWrite(L_REVERSE, LOW);

  digitalWrite(R_FORWARD, LOW);
  digitalWrite(R_REVERSE, LOW);

  analogWrite(L_SPEED, g_speed);
  analogWrite(R_SPEED, g_speed);


  
  xTaskCreate( vDistanceTask, "DistanceTask", 256, NULL, tskIDLE_PRIORITY+1, &h_distancetask );

  vTaskStartScheduler();

} void loop() {}



void vDistanceTask( void* p ){ 
  while(1) {
    digitalWrite(TRIG_PIN, HIGH);
    vTaskDelay(1);
    digitalWrite(TRIG_PIN, LOW);
    int dist = pulseIn(ECHO_PIN, HIGH);
    g_distance = (dist*0.0172);

    if(g_distance < 100) {
     // digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(L_FORWARD, HIGH);
      digitalWrite(R_FORWARD, HIGH);
    } else {
    //  digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(L_FORWARD, LOW);
      digitalWrite(R_FORWARD, LOW);
    }
    vTaskDelay(10);
  }
}