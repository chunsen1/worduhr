void setup_rtc3231() {
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC");
  else {
    Clock::time_t now;
    DCF77_Clock::get_current_time(now);
    setTimeToRTC(now);
    rtcIsSet = true;
    Serial.println("RTC has set the system time");
  }
}

void loop_rtc3231() {
  digitalClockDisplay();
  delay(1000);
}

void digitalClockDisplay(void) {
  // digital clock display of the time
  Serial.print("RTC: ");
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(' ');
  Serial.print(day());
  Serial.print(' ');
  Serial.print(month());
  Serial.print(' ');
  Serial.print(year());
  Serial.println();
}

void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(':');
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void setTimeToRTC(Clock::time_t tts) {
  tmElements_t tm = getTmElements_t(tts);
  time_t t = makeTime(tm);

  Serial.println("RTC time set.");

  RTC.set(t);
  setTime(t);
}


boolean isFullHour(Clock::time_t tts) {
  tmElements_t tm = getTmElements_t(tts);

  //if (bcd_to_int(tts.minute) == 0 && bcd_to_int(tts.second) == 0) {
  if (bcd_to_int(tts.second) == 0) {
    return true;
  }

  return false;
}

tmElements_t getTmElements_t(Clock::time_t tts) {
  tmElements_t tm;

  tm.Year = bcd_to_int(tts.year);
  tm.Month = bcd_to_int(tts.month);
  tm.Day = bcd_to_int(tts.day);
  tm.Hour = bcd_to_int(tts.hour);
  tm.Minute = bcd_to_int(tts.minute);
  tm.Second = bcd_to_int(tts.second);

  return tm;
}

