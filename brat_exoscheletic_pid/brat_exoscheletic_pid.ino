// Pinout motor
const int INA = 13;
const int INB = 12;
const int PWM = 11;

// EMG & senzor potențiometru
const int sensorPin = A1;
const int potPin = A0;
const int PushButton = 2;

// PID
float Kp = 2.5;
float Ki = 0.3;
float Kd = 0.8;
float previousError = 0;
float integral = 0;

// Stare sistem
enum State { IDLE, RIDICA, COBOARA };
State currentState = IDLE;

// Timere
unsigned long lastUpdate = 0;
const int interval = 50; // ms între actualizări

// Măsurători
int sensorValue = 0;
int potValue = 0;
float angle = 0;

void setup() {
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(PushButton, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  potValue = analogRead(potPin);
  angle = map(potValue, 0, 1023, 0, 300);
  int buttonState = digitalRead(PushButton);
  unsigned long now = millis();

  // FSM
  switch (currentState) {
    case IDLE:
      stop_motor();
      if (sensorValue >= 650) {
        currentState = RIDICA;
      } else if (buttonState == LOW) {
        currentState = COBOARA;
      }
      break;

    case RIDICA:
      if (now - lastUpdate >= interval) {
        lastUpdate = now;
        int pwmValue = computePID(90, angle);
        digitalWrite(INA, HIGH);
        digitalWrite(INB, LOW);
        analogWrite(PWM, pwmValue);

        Serial.print("Unghi: ");
        Serial.print(angle);
        Serial.print(" , PWM: ");
        Serial.println(pwmValue);
      }

      if (angle >= 90 || sensorValue < 650) {
        currentState = IDLE;
      }
      break;

    case COBOARA:
      if (now - lastUpdate >= interval) {
        lastUpdate = now;
        int pwmValue = computePID(5, angle);
        digitalWrite(INA, LOW);
        digitalWrite(INB, HIGH);
        analogWrite(PWM, pwmValue);

        Serial.print("Unghi: ");
        Serial.print(angle);
        Serial.print(" , PWM: ");
        Serial.println(pwmValue);
      }

      if (angle <= 5) {
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
  output = constrain(output, 0, 255);
  return (int)output;
}

void stop_motor() {
  analogWrite(PWM, 0);
  previousError = 0;
  integral = 0;
}
