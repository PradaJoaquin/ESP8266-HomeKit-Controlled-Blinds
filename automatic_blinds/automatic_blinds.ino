#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"

#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

void setup() {
	Serial.begin(9600); // Modify to the bps of your device
	wifi_connect();
	my_homekit_setup();
  // homekit_storage_reset(); // Uncomment this if you want to reset the device. As for pairing from another phone.
}

void loop() {
	my_homekit_loop();
	delay(10);
}
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;

static uint32_t next_heap_millis = 0;


#define PIN_SWITCH D2

void cha_switch_on_setter(const homekit_value_t value) {
	bool on = value.bool_value;
	cha_switch_on.value.bool_value = on;
	LOG_D("Switch: %s", on ? "ON" : "OFF");
 
	digitalWrite(PIN_SWITCH, on ? HIGH : LOW);
}

void my_homekit_setup() {
	pinMode(PIN_SWITCH, OUTPUT);
	digitalWrite(PIN_SWITCH, HIGH);

	cha_switch_on.setter = cha_switch_on_setter;
	arduino_homekit_setup(&config);

}

void my_homekit_loop() {
	arduino_homekit_loop();
	const uint32_t t = millis();
	if (t > next_heap_millis) {
		next_heap_millis = t + 5 * 1000;
		LOG_D("Free heap: %d, HomeKit clients: %d",
				ESP.getFreeHeap(), arduino_homekit_connected_clients_count());

	}
}
