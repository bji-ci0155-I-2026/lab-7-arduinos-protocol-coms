/**
 * Desarrollado en la Universidad de Costa Rica para el curso
 * Sistemas Empotrados de Tiempo Real - CI-0155
 *
 * Lab 7 - Parte 1: UART Receiver (Receptor)
 * 
 * Este programa actúa como el receptor UART. Escucha los datos entrantes
 * por SoftwareSerial, procesa comandos delimitados por corchetes (ej. "[LED_ON]")
 * y ejecuta una acción (encender/apagar el LED integrado en el Pin 13).
 * 
 * Requisito 2: Conexión TX y RX correcta
 * Conexiones sugeridas:
 * - Arduino Emisor Pin 3 (TX) -> Arduino Receptor Pin 2 (RX)
 * - Arduino Emisor Pin 2 (RX) -> Arduino Receptor Pin 3 (TX) [Opcional]
 * - GND común entre ambos Arduinos.
 */

// Configurar SoftwareSerial o UART Hardware
#include <SoftwareSerial.h>

const uint8_t rxPin = 2;
const uint8_t txPin = 3;

// Requisito 3: Programar Emisor Periódico y Receptor Actuador
const uint8_t ledPin = 13;

SoftwareSerial uartSerial(rxPin, txPin);

String inputBuffer = "";
bool messageReceived = false;

void setup() {
  // Inicializar pin del LED
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Inicializar puerto de depuración por hardware
  Serial.begin(9600);
  
  // Inicializar puerto de comunicación UART por software
  uartSerial.begin(9600); // Requisito 6: Evaluar errores modificando la velocidad (Baud Rate)
  // uartSerial.begin(1200);
  // uartSerial.begin(115200)
  Serial.println("[UART Receiver] Inicializado. Esperando comandos...");
}

void loop() {
  // Requisito 4: Protocolo Simple de Comunicación (Delimitadores)
  // Leer datos del SoftwareSerial
  while (uartSerial.available() > 0) {
    char inChar = (char)uartSerial.read();
    
    // Si detectamos el delimitador de inicio, vaciamos el buffer
    if (inChar == '[') {
      inputBuffer = "";
    }
    // Si detectamos el delimitador de fin, marcamos como recibido
    else if (inChar == ']') {
      messageReceived = true;
      break;
    }
    // De lo contrario, acumulamos los caracteres
    else {
      inputBuffer += inChar;
    }
  }
  
  // Requisito 5: Visualización de datos por Monitor Serial
  // Procesar el mensaje recibido
  if (messageReceived) {
    Serial.print("[UART Receiver] Recibido: ");
    Serial.println("[" + inputBuffer + "]");
    
    if (inputBuffer == "LED_ON") {
      digitalWrite(ledPin, HIGH);
      Serial.println("[UART Receiver] -> LED ENCENDIDO");
    } 
    else if (inputBuffer == "LED_OFF") {
      digitalWrite(ledPin, LOW);
      Serial.println("[UART Receiver] -> LED APAGADO");
    }
    
    // Limpiar estado
    inputBuffer = "";
    messageReceived = false;
  }
}
