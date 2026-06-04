# Laboratorio #7: Comunicación entre dos Arduino Uno R3 utilizando UART, I2C y SPI en entornos simulados

## Objetivo general

Implementar y comparar la comunicación entre dos sistemas embebidos (Arduino Uno R3) utilizando los protocolos UART, I2C y SPI en entornos de simulación.

## Requisitos generales

1. Configure dos placas Arduino Uno R3 en Simulide.
2. En todos los casos, identifique claramente el Arduino que actuará como Maestro y el que actuará como Aprendiz (cuando aplique).
3. Diseñe y documente los esquemas de conexión para cada protocolo en ambos simuladores.
4. Implemente un mecanismo de prueba donde:
   - Un Arduino envíe datos.
   - El otro Arduino reciba y procese dichos datos.
   - Se evidencie la recepción mediante LEDs o salida por monitor serial.

---

## Parte 1: Comunicación UARTs

1. Configure la comunicación serial entre ambos Arduino utilizando pines digitales (SoftwareSerial) o el puerto serial hardware, según disponibilidad del simulador.
2. Conecte correctamente las líneas TX y RX entre ambos dispositivos.
3. Programe:
   - Un Arduino como emisor, que envíe un mensaje periódico (texto o valor numérico).
   - Un Arduino como receptor, que reciba el mensaje y ejecute una acción (por ejemplo, encender un LED según el contenido recibido).
4. Implemente un protocolo simple de comunicación (por ejemplo, delimitadores de inicio/fin o códigos de comando).
5. Visualice los datos transmitidos y recibidos mediante el monitor serial del simulador.
6. Evalúe posibles errores de comunicación modificando la velocidad de transmisión (baud rate).

---

## Parte 2: Comunicación I2C

1. Configure la comunicación I2C utilizando los pines dedicados (A4 - SDA, A5 - SCL).
2. Conecte ambas placas asegurando una referencia común de tierra (GND).
3. Defina una dirección I2C para el dispositivo Aprendiz (Apprentice).
4. Programe:
   - Un Arduino como Maestro, que envíe solicitudes de datos o comandos.
   - Un Arduino como Aprendiz, que responda a las solicitudes del Maestro.
5. Implemente al menos dos tipos de interacción:
   - Envío de datos desde el Maestro al Aprendiz.
   - Solicitud de datos del Maestro al Aprendiz.
6. Use LEDs o variables para indicar la recepción correcta de datos.
7. Verifique la consistencia de los datos intercambiados y el comportamiento ante múltiples solicitudes consecutivas.

---

## Parte 3: Comunicación SPI

1. Configure la comunicación SPI utilizando los pines:
   - COPI / MOSI (pin 11)
   - CIPO / MISO (pin 12)
   - SCK (pin 13)
   - CS (pin 10 u otro definido como selección)
2. Conecte ambos Arduino asegurando todas las líneas SPI y GND común.
3. Defina claramente el Arduino Maestro y el Aprendiz.
4. Programe:
   - El Arduino Maestro para enviar datos periódicamente.
   - El Arduino Aprendiz para recibir y responder con un dato (intercambio bidireccional).
5. Implemente una lógica donde el valor recibido controle un comportamiento (por ejemplo, intensidad o estado de un LED).
6. Asegure el uso correcto de la línea CS para habilitar la comunicación con el Aprendiz.
7. Evalúe la sincronización de los datos y la integridad de la transmisión.

---

## Parte 4: Integración en simuladores

1. Replique cada una de las tres implementaciones (UART, I2C y SPI) tanto en Simulide.
2. Verifique el comportamiento de cada protocolo en el entorno de simulación.
3. Identifique:
   - Configuración de hardware virtual.
   - Herramientas de depuración disponibles.
   - Manejo del monitor serial.
4. Ajuste el diseño según las limitaciones o características del simulador.

---

## Parte 5: Pruebas y validación

1. Realice pruebas funcionales para cada protocolo verificando:
   - Correcta transmisión de datos.
   - Tiempo de respuesta.
   - Robustez ante múltiples mensajes.
2. Introduzca variaciones en los datos enviados para validar el comportamiento del sistema.
3. Simule condiciones de error (datos incorrectos o desconexión lógica) y observe la respuesta del sistema.

---

## Entregables

- Archivos de simulación para Simulide.
- Código fuente para ambos Arduino en cada protocolo.
- Diagramas de conexión utilizados en cada simulador.
- Evidencia de pruebas (capturas o descripción de resultados).
- Documento con análisis comparativo del comportamiento de UART, I2C y SPI en la plataforma de simulación.
