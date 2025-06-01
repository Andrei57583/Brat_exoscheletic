const int INA = 13;
const int INB = 12;
const int PWM = 11;

const int PushButton = 2;

int buttonState = 0;

const int potPin = A0;  // Pinul unde este conectat potențiometrul

int potValue = 0;       // Variabilă pentru valoarea citită
float angle = 0;        // Variabilă pentru unghiul calculat

const int sensorPin = A1;  // MyoWare signal pin connected to A1

int sensorValue = 0;       // Variable to store sensor reading

bool flag_ridicat = false;

void setup() {
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(PWM, OUTPUT);
  
  pinMode(PushButton, INPUT_PULLUP);
  Serial.begin(115200);

}

void loop() {
    
  sensorValue = analogRead(sensorPin);  // Read the analog signal
  Serial.print("MyoWare Sensor Value: ");
  Serial.println(sensorValue);          // Print the value to Serial Monitor
  delay(100);  // Short delay to prevent overwhelming serial output

  buttonState = digitalRead(PushButton);

  if (sensorValue >= 650 && flag_ridicat == false) 
  {
    ridicare_mana();
    stop_motor();
    flag_ridicat = !flag_ridicat;
    delay(3000);

  } else if ( buttonState == LOW && flag_ridicat == true) {
    coborare_mana();
    stop_motor();
    flag_ridicat = !flag_ridicat;
    delay(3000);
  } 
}


void ridicare_mana() {

  Serial.println("Se ridica mana!");
  Serial.println(flag_ridicat);

  digitalWrite(INA, HIGH);  // direcție înainte
  digitalWrite(INB, LOW);

  while(angle < 90)
  { 
    potValue = analogRead(potPin);  // Citește valoarea de la potențiometru
    angle = map(potValue, 0, 1023, 0, 300);  // Convertim valoarea într-unghi între 0° și 300°
    analogWrite(PWM, 240);
  }
  
}

void coborare_mana() {

  Serial.println("Se coboara mana!");
  Serial.println(flag_ridicat);

  digitalWrite(INA, LOW);  // direcție înapoi
  digitalWrite(INB, HIGH);

  while(angle > 5)
  {
    potValue = analogRead(potPin);  // Citește valoarea de la potențiometru
    angle = map(potValue, 0, 1023, 0, 300);  // Convertim valoarea într-unghi între 0° și 300°
    analogWrite(PWM, 240);
  }
  
}

void stop_motor() {

  Serial.println("Se opreste mana!");

  analogWrite(PWM, 0);
}