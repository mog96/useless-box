int leftInverter  = 2;
int rightInverter = 3;
int limitSwitch   = 4;
int toggleSwitch  = 5;

bool reverseCalled = false;
int switchToggledCount = 0;
bool abusingSwitch = false;
int kNumTogglesBeforeAbuse = 5;
int cyclesSinceAbuseStart = 0;


void setup() {
  pinMode(leftInverter, OUTPUT);
  pinMode(rightInverter, OUTPUT);
  pinMode(limitSwitch, INPUT_PULLUP);   // Input pullup keeps the switch 'high' when the circuit is open.
  pinMode(toggleSwitch, INPUT_PULLUP);  // (As opposed to reading an arbitrary value, or connecting a
                                        // resistor from the third pin of the switch to the Vin of the board.)
  Serial.begin(115200);
}

void loop() {
  int limitInput = digitalRead(limitSwitch);
  int toggleInput = digitalRead(toggleSwitch);

  if (switchToggledCount == kNumTogglesBeforeAbuse) {
    abusingSwitch == true;

    Serial.println(switchToggledCount);
    Serial.println(kNumTogglesBeforeAbuse);
    Serial.println("START ABUSE");
  }

  if (abusingSwitch) {
    cyclesSinceAbuseStart++;
    
    Serial.print("ABUSE CYCLES: ");
    Serial.println(cyclesSinceAbuseStart);
    
    if (switchToggledCount == 0) {
      cyclesSinceAbuseStart = 0;
      abusingSwitch = false;
    }
    if (cyclesSinceAbuseStart % 100 == 0) {
      
      Serial.print("ABUSING ");
      Serial.println(switchToggledCount);
      
      if (toggleInput == HIGH) {
        fingerForward();
        switchToggledCount--;
      } else {
        fingerReverse();
      }
    }
    return;
  }
  
  if (toggleInput == HIGH) {
    fingerForward();
  } else { // toggleInput == LOW {
    if (limitInput == HIGH) {
      fingerStop();
    } else {
      if (!reverseCalled) {
        fingerReverse();
      }
    }
  }
}

void fingerForward() {
  reverseCalled = false;
  digitalWrite(leftInverter, HIGH);
  digitalWrite(rightInverter, LOW);
}

void fingerReverse() {
  if (!abusingSwitch) {
    
    Serial.print("TOGGLES ");
    Serial.println(switchToggledCount);
    
    switchToggledCount++;
  }
  digitalWrite(leftInverter, LOW);
  digitalWrite(rightInverter, HIGH);
  reverseCalled == true;
}

void fingerStop() {
  digitalWrite(leftInverter, HIGH);
  digitalWrite(rightInverter, HIGH);
}

