
uint8_t sample_input_pin() {
  const uint8_t sampled_data =
    dcf77_inverted_samples ^ (dcf77_analog_samples ? (analogRead(dcf77_analog_sample_pin) > 200)
                              : digitalRead(dcf77_sample_pin));

  digitalWrite(ledpin(dcf77_monitor_led), sampled_data);
  return sampled_data;
}

uint8_t ledpin(const uint8_t led) {
  return led;
}


void setup_dcf77() {
  Serial.begin(115200);
  Serial.println(F("Setup DCF77"));
  Serial.println("-------------------------------");
  Serial.print(F("Sample Pin:      ")); Serial.println(dcf77_sample_pin);
  Serial.print(F("Sample Pin Mode: ")); Serial.println(dcf77_pin_mode);
  Serial.print(F("Inverted Mode:   ")); Serial.println(dcf77_inverted_samples);
  Serial.println();
  Serial.println(F("Initializing..."));

  pinMode(ledpin(dcf77_monitor_led), OUTPUT);
  pinMode(dcf77_sample_pin, dcf77_pin_mode);

  DCF77_Clock::setup();
  DCF77_Clock::set_input_provider(sample_input_pin);

  // Wait till clock is synced, depending on the signal quality this may take
  // rather long. About 5 minutes with a good signal, 30 minutes or longer
  // with a bad signal
  for (uint8_t state = Clock::useless;
       state == Clock::useless || state == Clock::dirty;
       state = DCF77_Clock::get_clock_state()) {

    // wait for next sec
    Clock::time_t now;
    DCF77_Clock::get_current_time(now);

    // render one dot per second while initializing
    static uint8_t count = 0;
    Serial.print('.');
    ++count;
    if (count == 60) {
      count = 0;
      Serial.println();
    }
  }
}

void paddedPrint(BCD::bcd_t n) {
  Serial.print(n.digit.hi);
  Serial.print(n.digit.lo);
}

void loop_dcf77() {
  Clock::time_t now;

  DCF77_Clock::get_current_time(now);
  if (now.month.val > 0) {
    switch (DCF77_Clock::get_clock_state()) {
      case Clock::useless: Serial.print(F("useless ")); break;
      case Clock::dirty:   Serial.print(F("dirty:  ")); break;
      case Clock::synced:  Serial.print(F("synced: ")); break;
      case Clock::locked:  Serial.print(F("locked: ")); break;
    }
    Serial.print(' ');

    Serial.print(F("20"));
    paddedPrint(now.year);
    Serial.print('-');
    paddedPrint(now.month);
    Serial.print('-');
    paddedPrint(now.day);
    Serial.print(' ');

    paddedPrint(now.hour);
    Serial.print(':');
    paddedPrint(now.minute);
    Serial.print(':');
    paddedPrint(now.second);

    Serial.print("+0");
    Serial.print(now.uses_summertime ? '2' : '1');
    Serial.println();
  }
}


static boolean isClockStateClean() {
  boolean returnValue  = false;
  uint8_t state = DCF77_Clock::get_clock_state();

  
  if (state == Clock::synced || state == Clock::locked) {
    returnValue = true;

  }
  return returnValue;
}

