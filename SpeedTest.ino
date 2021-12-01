#include <Wire.h>

// Configuracion
#define BAUD_RATE 9600
#define DISTANCE 2.4   // metros entre espiras
#define VEHICLE_SIZE 4 // metros, largo del vehiculo
#define TICK_TIME 10

// Botones selectores de velocidad
#define PULSADO HIGH
#define PIN_BUTTON_A 1
#define PIN_BUTTON_B 2
#define PIN_BUTTON_C 3
#define PIN_BUTTON_D 4

// Salidas de espiras
#define PIN_COIL_A 5
#define PIN_COIL_B 6

// Salidas de leds
#define PIN_LED_A 7
#define PIN_LED_B 8
#define PIN_LED_C 9
#define PIN_LED_D 10

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
  Serial.begin(BAUD_RATE);

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
  Serial.print("A\n");
  // Leo los botones
  if (digitalRead(PIN_BUTTON_A) == PULSADO)
  {
    while (digitalRead(PIN_BUTTON_A) == PULSADO)
      ;
    digitalWrite(PIN_LED_A, HIGH);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, LOW);
    digitalWrite(PIN_LED_D, LOW);
    selected_speed = SPEED_A;
  }
  if (digitalRead(PIN_BUTTON_B) == PULSADO)
  {
    while (digitalRead(PIN_BUTTON_B) == PULSADO)
      ;
    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, HIGH);
    digitalWrite(PIN_LED_C, LOW);
    digitalWrite(PIN_LED_D, LOW);
    selected_speed = SPEED_B;
  }
  if (digitalRead(PIN_BUTTON_C) == PULSADO)
  {
    while (digitalRead(PIN_BUTTON_C) == PULSADO)
      ;
    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, HIGH);
    digitalWrite(PIN_LED_D, LOW);
    selected_speed = SPEED_C;
  }
  if (digitalRead(PIN_BUTTON_D) == PULSADO)
  {
    while (digitalRead(PIN_BUTTON_D) == PULSADO)
      ;
    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, LOW);
    digitalWrite(PIN_LED_D, HIGH);
    selected_speed = SPEED_D;
  }
  digitalWrite(PIN_COIL_A, HIGH);
  COUNTER = 0;
  STATE = ONLY_COIL_A;
}

void only_coil_a()
{
  Serial.print("B\n");
  float ms = (DISTANCE / selected_speed) * 3600;
  unsigned long T = round(ms / 10);
  if (COUNTER >= T)
  {
    digitalWrite(PIN_COIL_B, HIGH);
    STATE = BOTH_COILS;
  }
  ++COUNTER;
}

void both_coils()
{
  Serial.print("C\n");
  float ms = (VEHICLE_SIZE / selected_speed) * 3600;
  unsigned long T = round(ms / 10);
  if (COUNTER >= T)
  {
    digitalWrite(PIN_COIL_A, LOW);
    STATE = ONLY_COIL_B;
  }
  ++COUNTER;
}

void only_coil_b()
{
  Serial.print("D\n");
  float ms = ((DISTANCE / selected_speed) * 3600) + ((VEHICLE_SIZE / selected_speed) * 3600);
  unsigned long T = round(ms / 10);
  if (COUNTER >= 5000)
  {
    digitalWrite(PIN_COIL_B, LOW);
    STATE = NO_COILS;
  }
  COUNTER = 0;
}
