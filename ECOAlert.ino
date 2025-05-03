#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11
#define BUZZER_PIN 7
#define FAN_PIN 6  // controlled via transistor
#define BUTTON_PIN 12
#define LDR_PIN A0
#define THERMISTOR_PIN A1

int mode = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

unsigned long lastRainbowUpdate = 0;
const unsigned long rainbowInterval = 20;  // smooth speed

unsigned long lastSensorUpdate = 0;
const unsigned long sensorInterval = 500;

unsigned long lastBuzzerTime = 0;
int buzzerStep = 0;
bool buzzerActive = false;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  setColor(0, 0, 0);
}

void loop() {
  handleButton();

  switch (mode) {
    case 0:
      rainbowCycle();
      break;
    case 1:
      ldrMode();
      break;
    case 2:
      thermistorMode();
      break;
    case 3:
      combinedMode();
      break;
  }

  if (buzzerActive) {
    updateBuzzer();
  }
}

void handleButton() {
  static int lastButtonState = HIGH;
  int reading = digitalRead(BUTTON_PIN);

  if (reading == LOW && lastButtonState == HIGH && millis() - lastDebounceTime > debounceDelay) {
    mode = (mode + 1) % 4;
    Serial.print("Switched to Mode: ");
    Serial.println(mode);
    lastDebounceTime = millis();
  }
  lastButtonState = reading;
}

void rainbowCycle() {
  static int hue = 0;

  if (millis() - lastRainbowUpdate >= rainbowInterval) {
    lastRainbowUpdate = millis();

    hue = (hue + 1) % 360;
    int r, g, b;
    hsvToRgb(hue, 1, 1, r, g, b);
    setColor(r, g, b);
  }
}

void ldrMode() {
  if (millis() - lastSensorUpdate >= sensorInterval) {
    lastSensorUpdate = millis();

    int ldrValue = analogRead(LDR_PIN);
    Serial.print("LDR Value: ");
    Serial.println(ldrValue);

    if (ldrValue < 250) {
      startBuzzerTune();
      setColor(255, 0, 0);
    } else {
      buzzerActive = false;
      noTone(BUZZER_PIN);
      setColor(0, 255, 0);
    }
  }
}

void thermistorMode() {
  if (millis() - lastSensorUpdate >= sensorInterval) {
    lastSensorUpdate = millis();

    float temperatureC = readTemperature();
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" C");

    if (temperatureC > 16) {
      digitalWrite(FAN_PIN, HIGH);
      setColor(255, 0, 0);
    } else if (temperatureC > 20) {
      digitalWrite(FAN_PIN, HIGH);
      setColor(255, 165, 0);
    } else {
      digitalWrite(FAN_PIN, LOW);
      setColor(0, 0, 255);
    }
  }
}

void combinedMode() {
  if (millis() - lastSensorUpdate >= sensorInterval) {
    lastSensorUpdate = millis();

    int ldrValue = analogRead(LDR_PIN);
    float temperatureC = readTemperature();

    Serial.print("LDR: ");
    Serial.print(ldrValue);
    Serial.print(" | Temp: ");
    Serial.print(temperatureC);
    Serial.println(" C");

    if (ldrValue < 250 && temperatureC > 16) {
      startBuzzerTune();
      digitalWrite(FAN_PIN, HIGH);
      setColor(255, 0, 255);
    } else if (ldrValue < 250 && temperatureC <= 30) {
      startBuzzerTune();
      digitalWrite(FAN_PIN, LOW);
      setColor(148, 0, 211);
    } else if (ldrValue >= 250 && temperatureC > 16) {
      buzzerActive = false;
      noTone(BUZZER_PIN);
      digitalWrite(FAN_PIN, HIGH);
      setColor(255, 69, 0);
    } else {
      buzzerActive = false;
      noTone(BUZZER_PIN);
      digitalWrite(FAN_PIN, LOW);
      setColor(0, 255, 255);
    }
  }
}

float readTemperature() {
  int rawValue = analogRead(THERMISTOR_PIN);
  float voltage = rawValue * (5.0 / 1023.0);
  float resistance = (5.0 - voltage) * 10000 / voltage;
  float temperatureC = 1 / (log(resistance / 10000) / 3950 + 1 / (25 + 273.15)) - 273.15;
  return temperatureC;
}

void setColor(byte r, byte g, byte b) {
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}

void startBuzzerTune() {
  if (!buzzerActive) {
    buzzerActive = true;
    buzzerStep = 0;
    lastBuzzerTime = millis();
  }
}

void updateBuzzer() {
  // Simple single tone for buzzer
  if (millis() - lastBuzzerTime >= 500) {  // 500ms delay between buzzer sound
    tone(BUZZER_PIN, 1000, 500);  // 1000Hz tone for 500ms
    lastBuzzerTime = millis();
    buzzerActive = false;  // Deactivate after one beep
  }
}

// HSV to RGB conversion for smooth rainbow
void hsvToRgb(int h, float s, float v, int &r, int &g, int &b) {
  float c = v * s;
  float x = c * (1 - abs(fmod(h / 60.0, 2) - 1));
  float m = v - c;
  float r_, g_, b_;

  if (h < 60) { r_ = c; g_ = x; b_ = 0; }
  else if (h < 120) { r_ = x; g_ = c; b_ = 0; }
  else if (h < 180) { r_ = 0; g_ = c; b_ = x; }
  else if (h < 240) { r_ = 0; g_ = x; b_ = c; }
  else if (h < 300) { r_ = x; g_ = 0; b_ = c; }
  else { r_ = c; g_ = 0; b_ = x; }

  r = (r_ + m) * 255;
  g = (g_ + m) * 255;
  b = (b_ + m) * 255;
}
