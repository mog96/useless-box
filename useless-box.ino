/**
 * Battery-powered implementation of the useless box
 * using a Metro-Mini computer as a control mechanism.
 * 
 * IMPORTANT: When connected to USB, the finger will
 * enter reverse mode. There is no code to stop the
 * finger.
 * 
 * In a battery-powered environment, the Metro-Mini
 * is disconnected from the battery when the finger
 * hits the limit switch, so no 'stop' code is
 * necessary.
 */

int leftInverter  = 2;
int rightInverter = 3;
int toggleSwitch  = 4;

void setup() {
  pinMode(leftInverter, OUTPUT);
  pinMode(rightInverter, OUTPUT);
  pinMode(toggleSwitch, INPUT_PULLUP);  // Input pullup keeps the switch 'high' when the circuit is open.
                                        // (As opposed to reading an arbitrary value, or connecting a
                                        // resistor from the third pin of the switch to the Vin of the board.)
}

void fingerForward() {
  digitalWrite(leftInverter, HIGH);
  digitalWrite(rightInverter, LOW);
}

void fingerReverse() {
  digitalWrite(leftInverter, LOW);
  digitalWrite(rightInverter, HIGH);
}

void loop() {
  int toggleInput = digitalRead(toggleSwitch);

  if (toggleInput == HIGH) {
    fingerForward();
  } else { // toggleInput == LOW {
    fingerReverse();
  }
}
