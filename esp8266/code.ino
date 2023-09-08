// I/O PORT
int TOTAL_RELAY = 6;
int RELAYS[] = {
  16, // Relay #1
  5,  // Relay #2
  4,  // Relay #3
  14, // Relay #4
  12, // Relay #5
  13  // Relay #6
};

void setup() {
  // Set serial baud rate
  Serial.begin(74880);

  // Init pin mode
  delay(1000);
  for (int i = 0; i < TOTAL_RELAY; i++) {
    pinMode(RELAYS[i], OUTPUT);
  }

  // Info
  Serial.println("Device ready...");
}

void switchAll(int state) {
  for (int i = 0; i < TOTAL_RELAY; i++) {
    digitalWrite(RELAYS[i], state);
  }
  Serial.println(String("ALL -> ") + String(state));
}

void loop() {
  // Check serial
  if (Serial.available()) {
    // Get value
    String rVal = Serial.readStringUntil('\n');
    rVal.trim();

    // Check value length
    if (rVal.length() >= 3) {
      // Extract data
      int command = rVal.substring(0, 1).toInt();
      int number = rVal.substring(2, rVal.length()).toInt();

      // Check number length
      if (number > 0 && number <= TOTAL_RELAY) {
        // Get selected relay
        int selected = RELAYS[number - 1];

        // HIGH = 1
        if (command == 1) {
          Serial.println(String("ON -> #") + String(number));
          digitalWrite(selected, LOW);
        }
        else if (command == 2) {
          Serial.println(String("TOGGLE -> #") + String(number));
          digitalWrite(selected, !digitalRead(selected));
        }
        else {
          Serial.println(String("OFF -> #") + String(number));
          digitalWrite(selected, HIGH);
        }
      }
      else {
        // Check for another command
        if (rVal == "PING!") {
          Serial.println("PONG!");
        }
        else if (rVal == "1,all") {
          switchAll(LOW);
        }
        else if (rVal == "0,all") {
          switchAll(HIGH);
        }
        else {
          Serial.println(String("Unknown -> #") + String(number));
        }
      }
    }
  }
}