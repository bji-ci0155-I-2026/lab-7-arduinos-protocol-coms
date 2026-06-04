/**
 * Lab 7 - Parte 3: SPI Master (Maestro)
 * 
 * Este programa actúa como el maestro SPI. Envía datos periódicamente (un valor de brillo)
 * y recibe de vuelta el estado del aprendiz mediante una transferencia full-duplex.
 * 
 * Conexiones:
 * - Master Pin 11 (COPI) -> Aprendiz Pin 11 (COPI)
 * - Master Pin 12 (CIPO) -> Aprendiz Pin 12 (CIPO)
 * - Master Pin 13 (SCK)  -> Aprendiz Pin 13 (SCK)
 * - Master Pin 10 (CS)   -> Aprendiz Pin 10 (CS)
 * - GND común entre ambos Arduinos.
 */

#include <SPI.h>

const uint8_t csPin = 10;
uint32_t lastTransferTime = 0;
const uint32_t transferInterval = 2000; // Transferir cada 2 segundos

// Valores de brillo para enviar al LED del aprendiz (0 a 255)
const uint8_t brightnessLevels[] = {0, 64, 128, 192, 255};
uint8_t levelIndex = 0;

void setup() {
  // Inicializar Serial para depuración
  Serial.begin(9600);
  
  // Configurar el pin Chip Select como salida
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH); // Iniciar deshabilitado (HIGH)
  
  // Inicializar el hardware SPI como Maestro
  SPI.begin();
  
  // Configurar la velocidad para la simulación
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  
  Serial.println("[SPI Master] Inicializado.");
}

void loop() {
  uint32_t currentTime = millis();
  
  if (currentTime - lastTransferTime >= transferInterval) {
    lastTransferTime = currentTime;
    
    // Obtener el valor de brillo a enviar
    uint8_t valToSend = brightnessLevels[levelIndex];
    levelIndex = (levelIndex + 1) % 5;
    
    // Habilitar comunicación con el aprendiz (CS -> LOW)
    digitalWrite(csPin, LOW);
    
    // Realizar la transferencia bidireccional (Full-Duplex)
    uint8_t receivedVal = SPI.transfer(valToSend);
    // Puede que para simulaciones este valor no se obtenga correctamente, 
    // pero en hardware real si se obtendría.
    
    // Deshabilitar comunicación (CS -> HIGH)
    digitalWrite(csPin, HIGH);
    
    // Mostrar resultados
    Serial.print("[SPI Master] Transmitido (Brillo LED): ");
    Serial.print(valToSend);
    Serial.print(" | Recibido (Estado Aprendiz): ");
    Serial.println(receivedVal);
  }
}
