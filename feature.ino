void sendIRCommand() {
  digitalWrite(IR_INDICATOR_PIN, HIGH);
  ac.send();
  delay(100);
  ac.send();  // Kirim 2x untuk memastikan
  digitalWrite(IR_INDICATOR_PIN, LOW);
}

void turnACOn() {
  ac.on();
  ac.setMode(kDaikinCool);
  ac.setTemp(18);
  ac.setFan(kDaikinFanAuto);
  sendIRCommand();
}

void turnACOff() {
  ac.off();
  sendIRCommand();
}

void enableSwing() {
  ac.setSwingVertical(true);
  ac.setSwingHorizontal(true);
  sendIRCommand();
}

void disableSwing() {
  ac.setSwingVertical(false);
  ac.setSwingHorizontal(false);
  sendIRCommand();
}

void setTemperature(int temp) {
  ac.setTemp(temp);
  sendIRCommand();
}