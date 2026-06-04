/**
 * Desarrollado en la Universidad de Costa Rica para el curso
 * Sistemas Empotrados de Tiempo Real - CI-0155
 *
 * Este programa actúa como el emisor UART. Envía datos periódicamente
 * a través de un puerto serie virtual (SoftwareSerial) hacia el Arduino receptor.
 * También utiliza el puerto serie de hardware (Serial) para depuración.
 * 
 * Conexiones utilizadas: -> Requisito 2: Conexión TX y RX correcta
 * - Arduino Emisor Pin 3 (TX) -> Arduino Receptor Pin 2 (RX)
 * - Arduino Emisor Pin 2 (RX) -> Arduino Receptor Pin 3 (TX)
 * - GND común entre ambos Arduinos.
 */

// Requisito 1: Configurar SoftwareSerial o UART Hardware
#include <SoftwareSerial.h>

// Definición de pines para SoftwareSerial
const uint8_t rxPin = 2;
const uint8_t txPin = 3;

SoftwareSerial uartSerial(rxPin, txPin);

// Requisito 3: Programe un Arduino como emisor

uint32_t lastSendTime = 0;
const uint32_t sendInterval = 2000; // Enviar cada 2 segundos
uint16_t messageCounter = 0;

void setup() {
  // Inicializar puerto de depuración por hardware
  Serial.begin(9600);
  while (!Serial) {
    ; // Esperar a que se conecte el puerto serial (solo necesario en algunas placas)
  }
  
  // Inicializar puerto de comunicación UART por software
  uartSerial.begin(9600); // Requisito 6: Evaluar errores modificando la velocidad (Baud Rate)
  // uartSerial.begin(1200);
  // uartSerial.begin(115200)
  
  Serial.println("[UART Sender] Inicializado. Enviando mensajes cada 2s...");
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastSendTime >= sendInterval) {
    lastSendTime = currentTime;
    messageCounter++;
    
    // Requisito 4: Implemente un protocolo simple de comunicación
    // Formato del protocolo simple: [START]comando[END]
    // Ejemplo: [CMD_ON] o [CMD_OFF] alternados
    String command = (messageCounter % 2 == 0) ? "LED_ON" : "LED_OFF";
    String payload = "[" + command + "]";
    
    // Enviar el comando por SoftwareSerial
    uartSerial.print(payload);
    
    // Requisito 5: Visualización de datos por Monitor Serial
    // Registrar en el monitor local
    Serial.print("[UART Sender] Enviado: ");
    Serial.println(payload);
  }
}
