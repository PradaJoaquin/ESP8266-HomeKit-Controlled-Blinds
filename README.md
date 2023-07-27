# ESP8266-HomeKit-Controlled-Blinds

Este proyecto usa un **NodeMCU ESP8266** y **Apple HomeKit** para controlar una persiana electrica.

# Motivación
El objetivo del proyecto es poder controlar una persiana electrica desde un Iphone a través de HomeKit. Pero ademas manteniendo el uso manual de la persiana con su viejo interruptor.

El siguiente diagrama muestra las conexiones electricas:

![Diagrama arduino](https://github.com/PradaJoaquin/ESP8266-HomeKit-Controlled-Blinds/assets/36085103/d3c16e67-620a-412f-8215-a3811f8034fc)

# Instalación
1. Descargar e instalar el [IDE de Arduino](https://www.arduino.cc/en/software).
2. Agregar el ESP8266 al Boards Manager del IDE, en Preferences/Additional-Boards-Manager-URLs. Pegando el siguiente link: *http://arduino.esp8266.com/stable/package_esp8266com_index.json*.
3. Descargar el ESP8266 desde el Boards Manager del IDE, en Tools/Board/Boards-Manager buscando ESP8266 e instalando la última version.
4. Descargar la Library [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266), e instalarla desde el IDE en Sketch/IncludeLibrary y seleccionando el .zip del repositorio descargado.

# Edición del Código
1. Dentro del archivo [wifi_info.h](https://github.com/PradaJoaquin/ESP8266-HomeKit-Controlled-Blinds/blob/main/automatic_blinds/wifi_info.h) cambiar la variable **ssid** por el nombre del wifi y la variable **password** por la contraseña del wifi.

# Recommended settings in IDE
- Module: Generic ESP8266 Module (to enable full settings)
- FlashSize: at least 470KB for sketch (see WolfSSL section if you want a smaller sketch)
- LwIP Variant: v2 Lower Memory (for lower memory use)
- Debug Level: None (for lower memory use)
- Espressif FW: nonos-sdk 2.2.1+119(191122) (which I used to build this project)
- SSL Support: Basic SSL ciphers (lower ROM use)
- VTables: Flash (does not matter maybe)
- Erase Flash: select All Flash Contents when you first upload
- CPU Frequency: 160MHz (must)

# IMPORTANTE
Se Usa el [FORK de paullj1](https://github.com/paullj1/Arduino-HomeKit-ESP8266) del [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266), ya que con sus cambios hasta el
26/7/2023 (fecha al escribir esto) y juntando el Pull Request [Corrected pairing address for resets ](https://github.com/paullj1/Arduino-HomeKit-ESP8266/pull/2) a ese fork, me funciona.

Si en un futuro actualizan el repositorio original, que por ahora parece deprecado, esto ya no importa. Al dia de hoy sin estos cambios no anda. 

# Gracias
- [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266)
- [Arduino-ide](https://github.com/arduino/arduino-ide)
