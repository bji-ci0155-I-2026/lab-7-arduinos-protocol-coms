/**
 * Lab 7 - Parte 3: SPI Apprentice (Aprendiz)
 * 
 * Este programa actúa como el aprendiz SPI.
 * Configura el SPI por hardware en modo aprendiz y habilita interrupciones
 * para procesar los datos entrantes a nivel de registros (ATmega328P).
 * Controla el brillo de un LED en un pin PWM (Pin 9) basado en el byte recibido.
 * Devuelve un contador de transacciones al maestro.
 * 
 * Conexiones sugeridas:
 * - Master Pin 11 (COPI) -> Aprendiz Pin 11 (COPI)
 * - Master Pin 12 (CIPO) -> Aprendiz Pin 12 (CIPO)
 * - Master Pin 13 (SCK)  -> Aprendiz Pin 13 (SCK)
 * - Master Pin 10 (CS)   -> Aprendiz Pin 10 (CS)
 * - GND común entre ambos Arduinos.
 * - Pin 9 (PWM) -> LED externo + resistencia de 220 ohmios -> GND
 */

#include <SPI.h>

// Compatibilidad con versiones de Arduino que no definen CIPO por defecto
#ifndef CIPO
#define CIPO MISO
#endif

const uint8_t ledPin = 9; // Pin PWM para controlar la intensidad del LED
volatile uint8_t receivedVal = 0;
volatile bool dataReceived = false;
volatile uint8_t transactionCounter = 0;

void setup() {
  // Configurar LED como salida
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0); // Iniciar apagado
  
  // Configurar CIPO (Pin 12) como salida para que el maestro pueda leer
  pinMode(CIPO, OUTPUT);
  
  // Serial para monitorear depuración
  Serial.begin(9600);
  
  // Configurar SPCR (SPI Control Register) para habilitar SPI en modo aprendiz y habilitar interrupciones:
  // SPE: SPI Enable (Habilitar SPI)
  // SPIE: SPI Interrupt Enable (Habilitar interrupción por transferencia completa)
  SPCR |= _BV(SPE);
  SPCR |= _BV(SPIE);
  
  // Preparar el primer byte de respuesta cargándolo en el Registro de Datos SPI (SPDR)
  SPDR = transactionCounter;
  
  Serial.println("[SPI Apprentice] Inicializado y listo en modo interrupción.");
}

// Rutina de Servicio de Interrupción de SPI (Serial Transfer Complete - STC)
ISR(SPI_STC_vect) {
  receivedVal = SPDR; // Leer el byte recibido enviado por el maestro
  dataReceived = true;
  
  // Incrementar el contador de transacciones y precargarlo para el siguiente ciclo
  transactionCounter++;
  SPDR = transactionCounter; 
}

void loop() {
  if (dataReceived) {
    // Ajustar el brillo del LED mediante PWM
    analogWrite(ledPin, receivedVal);
    
    // Mostrar en serial de depuración
    Serial.print("[SPI Apprentice] Brillo recibido: ");
    Serial.print(receivedVal);
    Serial.print(" | Siguiente respuesta preparada (Contador): ");
    Serial.println(transactionCounter);
    
    dataReceived = false;
  }
}
