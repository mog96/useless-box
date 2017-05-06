int leftInverter  = 2;
int rightInverter = 3;
int limitSwitch   = 4;
int toggleSwitch  = 5;

void setup() {
  pinMode(leftInverter, OUTPUT);
  pinMode(rightInverter, OUTPUT);
  pinMode(limitSwitch, INPUT_PULLUP);   // Input pullup keeps the switch 'high' when the circuit is open.
  pinMode(toggleSwitch, INPUT_PULLUP);  // (As opposed to reading an arbitrary value, or connecting a
                                        // resistor from the third pin of the switch to the Vin of the board.)
  Serial.begin(115200);
  // Serial.println("READY");
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
  if (Serial.available()) {
    char userInput = Serial.read();
    if (userInput == 'f') {
      Serial.println("FORWARD");
      fingerForward();
    } else if (userInput == 'r') {
      Serial.println("REVERSE");
      fingerReverse();
    } else if (userInput == 's') {
      Serial.println("STOP");
      fingerStop();
    } else {
      Serial.println("Invalid character.");
    }
  }

  int limitInput = digitalRead(limitSwitch);
  Serial.print("LIMIT  ");
  Serial.println(limitInput == HIGH ? "high" : "low");

  int toggleInput = digitalRead(toggleSwitch);
  Serial.print("TOGGLE ");
  Serial.println(toggleInput == HIGH ? "high" : "low");

  if (toggleInput == HIGH) {
    fingerForward();
  } else { // toggleInput == LOW {
    if (limitInput == HIGH) {
      fingerStop();
    } else {
      fingerReverse();
    }
  }
}
