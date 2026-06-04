/**
 * Lab 7 - Parte 2: I2C Master (Maestro)
 * 
 * Este programa actúa como el maestro I2C. Realiza dos tipos de interacción:
 * 1. Envía comandos al aprendiz (escribir datos).
 * 2. Solicita el estado actual al aprendiz (leer datos).
 * 
 * Requisito 1: Configurar Pines Dedicados (A4 - SDA, A5 - SCL)
 * Conexiones sugeridas:
 * - Maestro Pin A4 (SDA) -> Aprendiz Pin A4 (SDA)
 * - Maestro Pin A5 (SCL) -> Aprendiz Pin A5 (SCL)
 * Requisito 2: Conecte ambas placas asegurando una referencia común de tierra (GND).
 * - GND común entre ambos Arduinos.
 * - Resistencias pull-up en SDA y SCL habitualmente de 4.7k
 */

#include <Wire.h>

// Requisito 3: Definir Dirección I2C para el Aprendiz
const uint8_t APPRENTICE_ADDR = 8; // Dirección I2C del aprendiz
uint32_t lastActionTime = 0;

// Requisito 4: Maestro Emisor de Comandos y Aprendiz Respondedor
// El maestro tira comandos, el aprendiz esta a la espera de ellos
const uint32_t actionInterval = 3000; // Ciclo cada 3 segundos
uint16_t commandCounter = 0;

void setup() {
  // Inicializar bus I2C como Maestro
  Wire.begin();
  
  // Inicializar serial para depuración
  Serial.begin(9600);
  Serial.println("[I2C Master] Inicializado.");
}

void loop() {
  unsigned long currentTime = millis();
  
  // Requisito 5: Implementar Dos Tipos de Interacción (Escritura y Lectura)
  if (currentTime - lastActionTime >= actionInterval) {
    lastActionTime = currentTime;
    commandCounter++;
    
    // --- INTERACCIÓN 1: Enviar datos (Comando de Escritura) ---
    // Alternar comandos: 0x01 (Encender LED), 0x02 (Apagar LED)
    byte commandToSend = (commandCounter % 2 == 0) ? 0x01 : 0x02;
    
    Wire.beginTransmission(APPRENTICE_ADDR);
    Wire.write(commandToSend);
    byte status = Wire.endTransmission();
    
    Serial.print("[I2C Master] Transmisión al aprendiz (Escribiendo ");
    Serial.print(commandToSend == 0x01 ? "LED_ON [0x01]" : "LED_OFF [0x02]");
    Serial.print("). Estado: ");
    
    if (status == 0) {
      Serial.println("Éxito");
    } else {
      Serial.print("Error (código ");
      Serial.print(status);
      Serial.println(")");
    }
    
    delay(500); // Pequeña pausa antes de solicitar respuesta
    
    // --- INTERACCIÓN 2: Solicitar datos (Petición de Lectura) ---
    // Solicitamos 1 byte al aprendiz para conocer el estado actual de su LED
    Wire.requestFrom(APPRENTICE_ADDR, 1);
    
    if (Wire.available()) {
      byte receivedVal = Wire.read();
      Serial.print("[I2C Master] Respuesta del aprendiz recibida: ");
      if (receivedVal == 0x01) {
        Serial.println("LED está ENCENDIDO (0x01)");
      } else if (receivedVal == 0x02) {
        Serial.println("LED está APAGADO (0x02)");
      } else {
        Serial.print("Desconocido (");
        Serial.print(receivedVal);
        Serial.println(")");
      }
    } else {
      Serial.println("[I2C Master] Error: No se recibió respuesta a la solicitud.");
    }
    
    Serial.println("----------------------------------------");
  }
}
