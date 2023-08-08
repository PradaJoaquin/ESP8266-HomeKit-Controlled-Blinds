# ESP8266-HomeKit-Controlled-Blinds

Este proyecto usa un **NodeMCU ESP8266** y **Apple HomeKit** para controlar una persiana electrica.

## Motivación
El objetivo del proyecto es poder controlar una persiana electrica a través de HomeKit, pero ademas manteniendo el uso manual de la persiana con su viejo interruptor. Todo esto con el menor presupuesto posible.

Los componentes utilizados fueron:
- Board Nodemcu Wifi Esp8266.
- 2 Channel Relay Module (Songle).
- AC (220v) a 5v Power Supply.
- Cables hembra-hembra y cables de 1mm para las conexiones eléctricas.

El siguiente diagrama muestra las conexiones eléctricas:

![Diagrama arduino](https://github.com/PradaJoaquin/ESP8266-HomeKit-Controlled-Blinds/assets/36085103/8a106cd5-d9b8-4e31-9b24-ae49c9776df9)

## Configuración
Los pines logicos utilizados en el **NodeMCU ESP8266** son:
- **D1** (GPIO5) funcionando como *OUTPUT* y que activa y desactiva el relay para que la persiana baje.
- **D2** (GPIO4) funcionando como *OUTPUT* y que activa y desactiva el relay para que la persiana suba.
- **D6** (GPIO12) funcionando como *INPUT_PULLUP* y que se usa para saber cuando el interruptor físico está activado hacia abajo.
- **D7** (GPIO13) funcionando como *INPUT_PULLUP* y que se usa para saber cuando el interruptor físico está activado hacia arriba.

## Instalación
1. Descargar e instalar el [ch340 driver](https://sparks.gogo.co.nz/ch340.html) necesario para que la computadora reconozca a la placa en windows 10/11.
2. Descargar e instalar el [IDE de Arduino](https://www.arduino.cc/en/software).
3. Agregar el *ESP8266* al **Boards Manager** del IDE, en *Preferences/Additional-Boards-Manager-URLs*. Pegando ahí el siguiente link: *http://arduino.esp8266.com/stable/package_esp8266com_index.json*.
4. Descargar el *ESP8266* desde el **Boards Manager** del IDE, en *Tools/Board/Boards-Manager* buscando *ESP8266* e instalando la última version.
5. Descargar la Library [Arduino-HomeKit-ESP8266](https://github.com/PradaJoaquin/Arduino-HomeKit-ESP8266), e instalarla desde el IDE en *Sketch/IncludeLibrary* seleccionando el .zip del repositorio descargado. Para una explicación de porque se usa el fork ir a la sección: [Aclaración](#aclaración).

## Edición del Código
1. Dentro del archivo [wifi_info.h](https://github.com/PradaJoaquin/ESP8266-HomeKit-Controlled-Blinds/blob/main/automatic_blinds/wifi_info.h) cambiar la variable **ssid** por el nombre del WiFi y la variable **password** por la contraseña del WiFi.
2. Modifique el `Serial.begin(9600)` dentro de [automatic_blinds.ino](https://github.com/PradaJoaquin/ESP8266-HomeKit-Controlled-Blinds/blob/main/automatic_blinds/automatic_blinds.ino) con los **BPS** que usa su dispositivo, en el caso del NodeMCU ESP8266 este viene escrito es la parte trasera de la placa.
3. Tal vez sea necesario invertir las señales enviadas a los relays para su correcto funcionamiento, en mi caso el relay se activa al enviarle una señal LOW, con otros relays puede ser al revés. Si es necesario se deberían modificar las funciones que interactuan con el motor, como `blind_motor_off()` dentro de [automatic_blinds.ino](https://github.com/PradaJoaquin/ESP8266-HomeKit-Controlled-Blinds/blob/main/automatic_blinds/automatic_blinds.ino).

## Settings importantes para modificar en el Arduino IDE
- CPU Frequency: 160MHz (Obligatorio)
- Board/Module: Generic ESP8266 Module
- Erase Flash: Only Sketch (Idealmente seleccionar *All Flash Contents* cuando se sube el código por primera vez)
- SSL Support: Basic SSL ciphers (lower ROM use)

## Aclaración
Se usa un [fork](https://github.com/PradaJoaquin/Arduino-HomeKit-ESP8266) de la library original [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266), ya que con los cambios propuestos en [#212](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266/pull/212) y juntandolo con el cambio [#2](https://github.com/paullj1/Arduino-HomeKit-ESP8266/pull/2), está funcionando. 

Si en un futuro actualizan el repositorio original, que por ahora parece deprecado, esto ya no importa. Al dia de hoy 26/7/2023 sin estos cambios no anda.

## Bibliografía útil
- [Para saber que pines se pueden utilizar en el NodeMCU ESP8266](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/).
- [Para más información de como funciona el *INPUT_PULLUP*](https://aprendiendoarduino.wordpress.com/tag/input-pullup/).

## Agradecimientos
- [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266)
- [Arduino-ide](https://github.com/arduino/arduino-ide)
