//#define DEBUG_MODE // Descomentar para utilizar el puerto serie
#ifdef DEBUG_MODE
#include <Wire.h>
#endif

// Configuracion
#define BAUD_RATE 115200
#define DISTANCE 2.4   // metros entre espiras
#define VEHICLE_SIZE 4 // metros, largo del vehiculo
#define TIME_WITH_NO_VEHICLE 250 * 4 // Tiempo sin vehiculo (se leen los pulsadores)
#define TICK_TIME 20

#define SPEED_CONVERTER 3600

// Botones selectores de velocidad
#define PULSADO LOW
#define PIN_BUTTON_A 22
#define PIN_BUTTON_B 24
#define PIN_BUTTON_C 26
#define PIN_BUTTON_D 28

// Salidas de espiras
#define PIN_COIL_A 31
#define PIN_COIL_B 33

// Salidas de leds
#define PIN_LED_A 32
#define PIN_LED_B 34
#define PIN_LED_C 36
#define PIN_LED_D 38

// Velocidades en km/4
#define SPEED_A 40
#define SPEED_B 60
#define SPEED_C 80
#define SPEED_D 100

// Maquina de estados
#define NO_COILS 0
#define ONLY_COIL_A 1
#define BOTH_COILS 2
#define ONLY_COIL_B 3
int STATE = NO_COILS;

unsigned long COUNTER = 0;
float selected_speed = SPEED_A;

void no_coils();
void only_coil_a();
void both_coils();
void only_coil_b();

void setup()
{
  #ifdef DEBUG_MODE
  Serial.begin(BAUD_RATE);
  #endif

  pinMode(PIN_BUTTON_A, INPUT);
  pinMode(PIN_BUTTON_B, INPUT);
  pinMode(PIN_BUTTON_C, INPUT);
  pinMode(PIN_BUTTON_D, INPUT);

  pinMode(PIN_COIL_A, OUTPUT);
  pinMode(PIN_COIL_B, OUTPUT);

  pinMode(PIN_LED_A, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  pinMode(PIN_LED_C, OUTPUT);
  pinMode(PIN_LED_D, OUTPUT);
}

void loop()
{
  switch (STATE)
  {
  case NO_COILS:
    no_coils();
    break;
  case ONLY_COIL_A:
    only_coil_a();
    break;
  case BOTH_COILS:
    both_coils();
    break;
  case ONLY_COIL_B:
    only_coil_b();
    break;
  }
  ++COUNTER;
  delay(TICK_TIME); // Patron de tiempo
}

void no_coils()
{
  #ifdef DEBUG_MODE
  Serial.print("A\n");
  #endif
  // Leo los botones
  if (digitalRead(PIN_BUTTON_A) == PULSADO)
  {
    digitalWrite(PIN_LED_A, HIGH);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, LOW);
    digitalWrite(PIN_LED_D, LOW);
    selected_speed = SPEED_A;
  }
  delay(TIME_WITH_NO_VEHICLE / 4);
  if (digitalRead(PIN_BUTTON_B) == PULSADO)
  {
    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, HIGH);
    digitalWrite(PIN_LED_C, LOW);
    digitalWrite(PIN_LED_D, LOW);
    selected_speed = SPEED_B;
  }
  delay(TIME_WITH_NO_VEHICLE / 4);
  if (digitalRead(PIN_BUTTON_C) == PULSADO)
  {
    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, HIGH);
    digitalWrite(PIN_LED_D, LOW);
    selected_speed = SPEED_C;
  }
  delay(TIME_WITH_NO_VEHICLE / 4);
  if (digitalRead(PIN_BUTTON_D) == PULSADO)
  {
    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, LOW);
    digitalWrite(PIN_LED_D, HIGH);
    selected_speed = SPEED_D;
  }
  delay(TIME_WITH_NO_VEHICLE / 4);
  digitalWrite(PIN_COIL_A, HIGH);
  COUNTER = 0;
  STATE = ONLY_COIL_A;
}

void only_coil_a()
{
  #ifdef DEBUG_MODE
  Serial.print("B\n");
  #endif
  float ms = (DISTANCE / selected_speed) * SPEED_CONVERTER;
  unsigned long T = round(ms / TICK_TIME);
  if (COUNTER >= T)
  {
    digitalWrite(PIN_COIL_B, HIGH);
    STATE = BOTH_COILS;
    COUNTER = 0;
  } else {
    ++COUNTER;  
  }
  
}

void both_coils()
{
  #ifdef DEBUG_MODE
  Serial.print("C\n");
  #endif
  float ms = (VEHICLE_SIZE / selected_speed) * SPEED_CONVERTER;
  unsigned long T = round(ms / TICK_TIME);
  if (COUNTER >= T)
  {
    digitalWrite(PIN_COIL_A, LOW);
    STATE = ONLY_COIL_B;
    COUNTER = 0;
  } else {
    ++COUNTER;  
  }
}

void only_coil_b()
{
  #ifdef DEBUG_MODE
  Serial.print("D\n");
  #endif
  float ms = (((DISTANCE / selected_speed)) + ((VEHICLE_SIZE / selected_speed)) * SPEED_CONVERTER);
  unsigned long T = round(ms / TICK_TIME);
  if (COUNTER >= T)
  {
    digitalWrite(PIN_COIL_B, LOW);
    STATE = NO_COILS;
  }
}
