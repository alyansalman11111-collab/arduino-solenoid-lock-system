int sensorPin = A1;
int buttonPin = 2;
int relayPin = 7;

int threshold = 150;
int tolerance = 600;

#define MAX_TAPS 10

unsigned long savedPattern[MAX_TAPS];
unsigned long inputPattern[MAX_TAPS];

int savedCount = 0;
int inputCount = 0;

bool recording = false;
bool patternSaved = false;

unsigned long lastTapTime = 0;
unsigned long lastEventTime = 0;

bool lastButtonState = HIGH;
bool wasHigh = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, HIGH); // LOCKED (active LOW relay)

  Serial.begin(9600);
}

void loop() {

  // ================= BUTTON =================
  bool currentButton = digitalRead(buttonPin);

  if (lastButtonState == HIGH && currentButton == LOW) {
    recording = true;
    patternSaved = false;

    savedCount = 0;
    inputCount = 0;
    lastTapTime = 0;

    Serial.println("RECORD START");
  }

  if (lastButtonState == LOW && currentButton == HIGH) {
    if (savedCount > 0) {
      recording = false;
      patternSaved = true;
      Serial.println("PATTERN SAVED");
    }
  }

  lastButtonState = currentButton;

  // ================= SENSOR (FIXED EVENT DETECTION) =================
  int val = analogRead(sensorPin);

  // Rising edge detection (CRITICAL FIX)
  if (val > threshold && !wasHigh && millis() - lastEventTime > 120) {

    wasHigh = true;
    lastEventTime = millis();

    Serial.println("TAP");

    unsigned long now = millis();

    // ================= RECORD =================
    if (recording) {

      if (savedCount == 0) {
        lastTapTime = now;
      } else {
        savedPattern[savedCount - 1] = now - lastTapTime;
        lastTapTime = now;
      }

      savedCount++;
    }

    // ================= MATCH =================
    else if (patternSaved) {

      if (inputCount == 0) {
        lastTapTime = now;
      } else {
        inputPattern[inputCount - 1] = now - lastTapTime;
        lastTapTime = now;
      }

      inputCount++;

      if (inputCount == savedCount && savedCount > 1) {

        if (matchPattern()) {
          Serial.println("UNLOCKED");

          digitalWrite(relayPin, LOW);
          delay(3000);
          digitalWrite(relayPin, HIGH);
        } else {
          Serial.println("WRONG PATTERN");
        }

        inputCount = 0;
      }
    }
  }

  // Reset trigger only when signal fully drops
  if (val < (threshold - 30)) {
    wasHigh = false;
  }
}

// ================= MATCH FUNCTION =================
bool matchPattern() {
  for (int i = 0; i < savedCount - 1; i++) {
    if (abs((long)savedPattern[i] - (long)inputPattern[i]) > tolerance) {
      return false;
    }
  }
  return true;
}
