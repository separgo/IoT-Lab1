// Definición de los pines para el sensor ultrasónico y los LEDs
const int Trigger = 13;       // GPIO 13 para el Trigger del sensor ultrasónico
const int Echo = 12;          // GPIO 12 para el Echo del sensor ultrasónico
const int numLeds = 8;        // Número total de LEDs
int leds[numLeds] = {2, 4, 5, 18, 19, 21, 22, 23};  // Pines GPIO de los LEDs

void setup() {
  Serial.begin(9600);  // Inicialización de la comunicación serial
  pinMode(Trigger, OUTPUT);  // Configuración del pin Trigger como salida
  pinMode(Echo, INPUT);      // Configuración del pin Echo como entrada
  
  // Configuración de los pines GPIO de los LEDs como salidas
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  } 
  digitalWrite(Trigger, LOW);  // Inicialización del pin Trigger en estado bajo
}

void loop() {
  long t;  // Variable para el tiempo de eco
  long d;  // Variable para la distancia medida
  
  digitalWrite(Trigger, HIGH);         // Generar pulso de activación del sensor
  delayMicroseconds(10);               // Esperar un corto tiempo
  digitalWrite(Trigger, LOW);          // Finalizar el pulso
  
  t = pulseIn(Echo, HIGH);             // Medir la duración del pulso de eco
  d = t / 59;                          // Convertir el tiempo en distancia en cm
  Serial.print("Distancia: ");
  Serial.print(d);
  Serial.print("cm");
  Serial.println();
  
  // Apagar todos los LEDs
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(leds[i], LOW);
  }
  
  // Encender el LED correspondiente a la distancia medida
  for (int i = 0; i < numLeds; i++) {
    if (d <= (5 + 5 * i)) {
      digitalWrite(leds[i], HIGH);
      break;  // Romper el ciclo para encender solo un LED
    }
  }
  
  delay(100);  // Esperar un breve periodo de tiempo antes de la siguiente medición
}
