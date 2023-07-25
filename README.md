# ESP8266-HomeKit-Controlled-Blinds

Este projecto usa un ESP8266 y HomeKit para controlar las persianas de mi casa.

# Instalación
1. Descargar e instalar el [IDE de Arduino](https://www.arduino.cc/en/software)
2. Agregar el ESP8266 al Boards Manager del IDE, en Preferences/Additional-Boards-Manager-URLs. Pegando el siguiente link: http://arduino.esp8266.com/stable/package_esp8266com_index.json
3. Descargar el ESP8266 desde el Boards Manager del IDE, en Tools/Board/Boards-Manager buscando esp8266 e instalando la última version.
4. Descargar la Library [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266), instalandola desde el IDE en Sketch/IncludeLibrary y seleccionando el .zip del repositorio descargado.

# Editar Código
1. Dentro de wifi_info.h cambiar la variable *ssid* por el nombre del wifi y la variable *password* por la contraseña del wifi.

# Gracias
- [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266)
- [Arduino-ide](https://github.com/arduino/arduino-ide)
