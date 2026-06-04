/**
 * Lab 7 - Parte 2: I2C Apprentice (Aprendiz)
 * 
 * Este programa actúa como el aprendiz I2C (dirección 8).
 * 1. Al recibir datos (onReceive), cambia el estado del LED integrado.
 * 2. Al ser consultado (onRequest), devuelve su estado actual al maestro.
 * 
 * Conexiones:
 * - Maestro Pin A4 (SDA) -> Aprendiz Pin A4 (SDA)
 * - Maestro Pin A5 (SCL) -> Aprendiz Pin A5 (SCL)
 * - GND común entre ambos Arduinos.
 */

#include <Wire.h>

// Definir Dirección I2C para el Aprendiz
const uint8_t MY_ADDR = 8;
const uint8_t ledPin = 13;

// Variables volatile ya que se modifican dentro de interrupciones de I2C
volatile uint8_t currentLedState = 0x02; // Por defecto apagado (0x02)

void setup() {
  // Inicializar pin de salida para el LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Inicializar serial para depuración
  Serial.begin(9600);
  
  // Registrar dirección I2C
  Wire.begin(MY_ADDR);
  
  // Registrar manejadores de eventos I2C
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  
  Serial.println("[I2C Apprentice] Inicializado y esperando solicitudes...");
}

void loop() {
  // El loop principal puede estar vacío o realizar otras tareas locales.
  // El procesamiento de I2C ocurre mediante interrupciones / callbacks.
  delay(100);
}

// Función que se ejecuta cuando el Maestro envía datos al Aprendiz
// Aprendiz siempre escuchando por comando del maestro.
// Requisito 4: Maestro Emisor de Comandos y Aprendiz Respondedor
void receiveEvent(int howMany) {
  while (Wire.available() > 0) {
    byte command = Wire.read();
    
    Serial.print("[I2C Apprentice] Recibido comando: ");
    if (command == 0x01) {
      digitalWrite(ledPin, HIGH);
      currentLedState = 0x01;
      Serial.println("ENCENDER LED (0x01)");
    } 
    else if (command == 0x02) {
      digitalWrite(ledPin, LOW);
      currentLedState = 0x02;
      Serial.println("APAGAR LED (0x02)");
    } 
    else {
      Serial.print("Desconocido (");
      Serial.print(command);
      Serial.println(")");
    }
  }
}

// Función que se ejecuta cuando el Maestro solicita datos al Aprendiz
void requestEvent() {
  // Enviar el estado actual del LED de vuelta al maestro
  Wire.write(currentLedState);
  Serial.print("[I2C Apprentice] Petición recibida. Enviando estado actual: ");
  Serial.println(currentLedState == 0x01 ? "ENCENDIDO (0x01)" : "APAGADO (0x02)");
}
