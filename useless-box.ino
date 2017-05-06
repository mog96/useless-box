int leftInverter  = 2;
int rightInverter = 3;
int limitSwitch   = 4;
int toggleSwitch  = 5;

int lastToggleInput = LOW;

bool shy = false;                       // Toggle for shy mode. (Finger emerges after delay.)
bool angry = false;                     // Toggle for angry mode. (Finger beats switch repeatedly.)
int kNumSwitchHitsWhenAngry = 5;

void setup() {
  pinMode(leftInverter, OUTPUT);
  pinMode(rightInverter, OUTPUT);
  pinMode(limitSwitch, INPUT_PULLUP);   // Input pullup keeps the switch 'high' when the circuit is open.
  pinMode(toggleSwitch, INPUT_PULLUP);  // (As opposed to reading an arbitrary value, or connecting a
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

void fingerStop() {
  digitalWrite(leftInverter, HIGH);
  digitalWrite(rightInverter, HIGH);
}

void loop() {
  int limitInput = digitalRead(limitSwitch);
  int toggleInput = digitalRead(toggleSwitch);

  if (toggleInput == HIGH) {
    if (toggleInput != lastToggleInput && shy) {
      delay(1000);
    }
    fingerForward();
  } else { // toggleInput == LOW {
    if (limitInput == HIGH) {
      fingerStop();
    } else {
      if (toggleInput != lastToggleInput && angry) {
        for (int i = 0; i < kNumSwitchHitsWhenAngry - 1; i++) {
          unsigned long startTime = millis();
          while (millis() - startTime < 150) {
            fingerReverse();
          }
          startTime = millis();
          while (millis() - startTime < 170) {
            fingerForward();
          }
        }
      }
      fingerReverse();
    }
  }

  lastToggleInput = toggleInput;
}
