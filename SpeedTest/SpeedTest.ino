// CONFIGURACION ///////////////////////////////////////////////////////////////

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
///////////////////////////////////////////////////////////////////////////////

typedef enum
{
  speed40,
  speed60,
  speed80,
  speed100,
  speedNone
} speed_t;

// Tiempos en milisegundos
const unsigned long CRONOS[4][4] = {
    {1000, 216, 144, 216},
    {1000, 144, 96, 144},
    {1000, 108, 72, 108},
    {1000, 86, 58, 86},
};

void setup()
{
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
  if (PULSADO == digitalRead(PIN_BUTTON_A))
  {
    selector = speed40;
    digitalWrite(PIN_LED_A, HIGH);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, LOW);
    digitalWrite(PIN_LED_D, LOW);
  }
  else if (PULSADO == digitalRead(PIN_BUTTON_B))
  {
    selector = speed60;
    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, HIGH);
    digitalWrite(PIN_LED_C, LOW);
    digitalWrite(PIN_LED_D, LOW);
  }
  else if (PULSADO == digitalRead(PIN_BUTTON_C))
  {
    selector = speed80;
    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, HIGH);
    digitalWrite(PIN_LED_D, LOW);
  }
  else if (PULSADO == digitalRead(PIN_BUTTON_D))
  {
    selector = speed100;
    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, LOW);
    digitalWrite(PIN_LED_D, HIGH);
  }
  else
  {
    selector = speedNone;
    digitalWrite(PIN_LED_A, LOW);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_C, LOW);
    digitalWrite(PIN_LED_D, LOW);
  }

  digitalWrite(PIN_COIL_A, LOW);
  digitalWrite(PIN_COIL_B, LOW);

  // Si no hay velocidad seleccionada no ejecuto secuencia
  if (selector == speedNone)
  {
    delay(20);
    continue;
  }

  // Secuencia de pulsos:
  // 00
  delay(CRONOS[selector][0]);

  // 10
  digitalWrite(PIN_COIL_A, HIGH);
  digitalWrite(PIN_COIL_B, LOW);
  delay(CRONOS[selector][1]);

  // 11
  digitalWrite(PIN_COIL_A, HIGH);
  digitalWrite(PIN_COIL_B, HIGH);
  delay(CRONOS[selector][2]);

  // 01
  digitalWrite(PIN_COIL_A, LOW);
  digitalWrite(PIN_COIL_B, HIGH);
  delay(CRONOS[selector][3]);
}
