//dcf
#include <dcf77.h>
//rtc3231
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)


#define debug

//dcf77
const uint8_t dcf77_analog_sample_pin = 5;
const uint8_t dcf77_sample_pin = 8;       // A5 == d19
const uint8_t dcf77_inverted_samples = 0;
const uint8_t dcf77_analog_samples = 0;
const uint8_t dcf77_pin_mode = INPUT;  // disable internal pull up
const uint8_t dcf77_monitor_led = 18;  // A4 == d18

boolean rtcIsSet = false;

void setup() {
  // put your setup code here, to run once:
  setup_dcf77();

  setup_rtc3231();
}

void loop() {
  // put your main code here, to run repeatedly:
  loop_dcf77();

  loop_rtc3231();

  Clock::time_t now;
  DCF77_Clock::get_current_time(now);

  if (isClockStateClean() && !rtcIsSet && isFullHour(now)) {

    setTimeToRTC(now);
    rtcIsSet = true;
  }

}
