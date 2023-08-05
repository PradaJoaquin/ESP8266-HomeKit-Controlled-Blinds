#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"

#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

void setup() {
	Serial.begin(9600); // Modify to the bps of your device
	wifi_connect();
	my_homekit_setup();
  pin_setup();
  // homekit_storage_reset(); // Uncomment this if you want to reset the device. As for pairing from another phone.
}

void loop() {
  physical_switch_loop();
	my_homekit_loop();
	delay(10);
}

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;

static uint32_t next_heap_millis = 0;
static bool is_physical_switch_in_control = false;

#define PIN_BLIND_MOTOR_DOWN 16       // Tells the blind motor to go down (D0)
#define PIN_BLIND_MOTOR_UP 4          // Tells the blind motor to go up (D2)
#define PIN_PHYSICAL_SWITCH_UP 12     // Is LOW when the physical switch is UP (D6)
#define PIN_PHYSICAL_SWITCH_DOWN 15   // Is LOW when the physical switch is DOWN (D8)

void pin_setup() {
  pinMode(PIN_BLIND_MOTOR_DOWN, OUTPUT);
  pinMode(PIN_BLIND_MOTOR_UP, OUTPUT);
  pinMode(PIN_PHYSICAL_SWITCH_UP, INPUT_PULLUP);
  pinMode(PIN_PHYSICAL_SWITCH_DOWN, INPUT_PULLUP);
  
	digitalWrite(PIN_BLIND_MOTOR_DOWN, LOW); // TODO: Revisar si el LOW enciende la conexión y hay que invertirlo cambiandolo con un HIGH.
  digitalWrite(PIN_BLIND_MOTOR_UP, LOW); // TODO: Revisar si el LOW enciende la conexión y hay que invertirlo cambiandolo con un HIGH.
}

void my_homekit_setup() {
	cha_switch_on.setter = cha_switch_on_setter;
	arduino_homekit_setup(&config);
}

void cha_switch_on_setter(const homekit_value_t value) {
  if (!is_physical_switch_in_control) {
    // We always prioritize the physical switch over the homekit switch.
    LOG_D("Physical Switch is in control, change the position of the physical switch to neutral to use the homekit switch.");
    return;
  }
  bool on = value.bool_value;
	cha_switch_on.value.bool_value = on;

  LOG_D("Homekit Switch: %s", on ? "ON" : "OFF");

	if (on) {
    blind_motor_up();
  } else {
    blind_motor_down();
  }
}

void blind_motor_up() {
  digitalWrite(PIN_BLIND_MOTOR_DOWN, LOW);
  delay(50);  // To make sure the other pin is LOW before chaging the other to HIGH.
  digitalWrite(PIN_BLIND_MOTOR_UP, HIGH);
}

void blind_motor_down() {
  digitalWrite(PIN_BLIND_MOTOR_UP, LOW);
  delay(50);  // To make sure the other pin is LOW before chaging the other to HIGH.
  digitalWrite(PIN_BLIND_MOTOR_DOWN, HIGH);
}

void blind_motor_off() {
  digitalWrite(PIN_BLIND_MOTOR_UP, LOW);
  digitalWrite(PIN_BLIND_MOTOR_DOWN, LOW);
}

void physical_switch_loop() {
  if (digitalRead(PIN_PHYSICAL_SWITCH_UP) == LOW) {
    if (!is_physical_switch_in_control) {
      LOG_D("Physical Switch: UP");
      is_physical_switch_in_control = true;
      blind_motor_up(); 
    }
  }
  else if (digitalRead(PIN_PHYSICAL_SWITCH_DOWN) == LOW) {
    if (!is_physical_switch_in_control) {
      LOG_D("Physical Switch: DOWN");
      is_physical_switch_in_control = true;
      blind_motor_down();
    }
  }
  else {
    if (is_physical_switch_in_control) {
      LOG_D("Physical Switch: NEUTRAL");
      blind_motor_off();
      is_physical_switch_in_control = false;
    }
  }
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
