int leftInverter  = 2;
int rightInverter = 3;
int limitSwitch   = 4;
int toggleSwitch  = 5;

int lastToggleInput = LOW;
int lastLimitInput = LOW;
bool abusingSwitch = false;
int switchToggledCount = 0;
int switchAbusedCount = 0;
int cyclesSinceAbuseStarted  =0;

int kNumTogglesBeforeAbuse = 5;
int kNumAbuses = 5;


void setup() {
  pinMode(leftInverter, OUTPUT);
  pinMode(rightInverter, OUTPUT);
  pinMode(limitSwitch, INPUT_PULLUP);   // Input pullup keeps the switch 'high' when the circuit is open.
  pinMode(toggleSwitch, INPUT_PULLUP);  // (As opposed to reading an arbitrary value, or connecting a
                                        // resistor from the third pin of the switch to the Vin of the board.)
  Serial.begin(115200);
}

void loop() {
//  if (abusingSwitch) {
//    cyclesSinceAbuseStarted++;
//    if (cyclesSinceAbuseStarted % 100000 == 0) {
//
//      Serial.print("ABUSE CYCLE ");
//      Serial.print(cyclesSinceAbuseStarted);
//    
//      fingerForward();
//    }
//  }
  
  int limitInput = digitalRead(limitSwitch);
  int toggleInput = digitalRead(toggleSwitch);

  if (toggleInput != lastToggleInput) {
    if (toggleInput == HIGH) {
      checkSwitch();
      fingerForward();
    } else { // toggleInput == LOW
      if (limitInput == HIGH) {
        fingerStop();
      } else {
        fingerReverse();
      }
    }
  }

  lastToggleInput = toggleInput;
  lastLimitInput = limitInput;
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

void checkSwitch() {
  if (abusingSwitch) {
    switchAbusedCount++;
    if (switchToggledCount == kNumTogglesBeforeAbuse) {
      abusingSwitch = false;
      switchAbusedCount = 0;
      cyclesSinceAbuseStarted = 0;
    }
    
  } else {
    switchToggledCount++;
    if (switchToggledCount == kNumTogglesBeforeAbuse) {
      abusingSwitch = true;
      switchToggledCount = 0;
    }

    Serial.print("TOGGLE ");
    Serial.println(switchToggledCount);
  }
}

