#include <dcf77.h>

#define debug

//dcf77
const uint8_t dcf77_analog_sample_pin = 5;
const uint8_t dcf77_sample_pin = 19;       // A5 == d19
const uint8_t dcf77_inverted_samples = 0;
const uint8_t dcf77_analog_samples = 0;
const uint8_t dcf77_pin_mode = INPUT;  // disable internal pull up
const uint8_t dcf77_monitor_led = 18;  // A4 == d18

void setup() {
  // put your setup code here, to run once:
  setup_dcf77();
}

void loop() {
  // put your main code here, to run repeatedly:
  loop_dcf77();
}
