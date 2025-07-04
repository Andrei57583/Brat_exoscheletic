// === Pinout motor ===
const int INA = 13;
const int INB = 12;
const int PWM = 11;

// === Senzori ===
const int sensorPin = A1;   // EMG
const int potPin = A0;      // Potențiometru
const int PushButton = 2;   // Buton

// === PID ===
float Kp = 1.0659;
float Ki = 2.2033;
float Kd = 0.0133;
float previousError = 0;
float integral = 0;

// === FSM ===
enum State { IDLE, RIDICA, COBOARA };
State currentState = IDLE;

// === Timp actualizări motor ===
unsigned long lastUpdate = 0;
const int interval = 50;  // ms între iterații PID

// === Măsurători ===
int sensorValue = 0;
int potValue = 0;
float angle = 0;

// === Flag poziție braț ===
bool flag_ridicata = false;

// === Flag apăsare unică buton ===
static bool buttonWasPressed = false;
static bool requestCoborare = false;

void setup() {
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(PushButton, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  unsigned long now = millis();

  // === Citiri actualizate ===
  sensorValue = analogRead(sensorPin);
  potValue = analogRead(potPin);
  angle = map(potValue, 0, 1023, 0, 300);


  // === Citire buton + generare cerere de coborâre ===
  bool buttonState = digitalRead(PushButton) == LOW;

  if (buttonState && !buttonWasPressed) {
    requestCoborare = true;  // apăsare detectată
  }
  buttonWasPressed = buttonState;

  // === FSM ===
  switch (currentState) {

    case IDLE:
      stop_motor();

      Serial.print("IDLE | EMG: ");
      Serial.print(sensorValue);
      Serial.print(" | Buton: ");
      Serial.print(buttonState);
      Serial.print(" | RequestCoborare: ");
      Serial.print(requestCoborare);
      Serial.print(" | Flag ridicat: ");
      Serial.print(flag_ridicata);
      Serial.print(" | Unghi: ");
      Serial.println(angle);

      if (sensorValue >= 650 && !flag_ridicata) {
        currentState = RIDICA;
      } else if (requestCoborare && flag_ridicata) {
        currentState = COBOARA;
        requestCoborare = false;  // resetăm cererea după executare
      }
      break;

    case RIDICA:
      if (now - lastUpdate >= interval) {
        lastUpdate = now;
        int pwmValue = computePID(70, angle);  // target: 95°

        digitalWrite(INA, HIGH);
        digitalWrite(INB, LOW);
        analogWrite(PWM, pwmValue);

        Serial.print("RIDICA | Unghi: ");
        Serial.print(angle);
        Serial.print(" | PWM: ");
        Serial.println(pwmValue);
      }

      if (angle >= 70) {
        flag_ridicata = true;
        currentState = IDLE;
      }
      break;

    case COBOARA:
      if (now - lastUpdate >= interval) {
        lastUpdate = now;
        int pwmValue = computePID(30, angle);  // target: 30°

        digitalWrite(INA, LOW);
        digitalWrite(INB, HIGH);
        analogWrite(PWM, pwmValue);
        
        Serial.print("COBOARA | Unghi: ");
        Serial.print(angle);
        Serial.print(" | PWM: ");
        Serial.println(pwmValue);
      }

      if (angle <= 30) {
        flag_ridicata = false;
        currentState = IDLE;
      }
      break;
  }
}

int computePID(float setpoint, float measured) {
  float error = setpoint - measured;
  integral += error;
  float derivative = error - previousError;
  previousError = error;

  float output = Kp * error + Ki * integral + Kd * derivative;

  output = abs(output);  // permite control și pentru erori negative
  output = constrain(output, 0, 100);
  return (int)output;
}

void stop_motor() {
  analogWrite(PWM, 0);
  previousError = 0;
  integral = 0;
}
