const int INA = 13;
const int INB = 12;
const int PWM = 11;
const int potPin = A0;  // Pinul unde este conectat potențiometrul

int potValue = 0;       // Variabilă pentru valoarea citită
float angle = 0;        // Variabilă pentru unghiul calculat

bool flag_ridicat = 0;

void setup() {
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);
  pinMode(PWM, OUTPUT);

  Serial.begin(9600);

}

void loop() {
    
  ridicare_mana();
  
 // !flag_ridicat;
  stop_motor();

  delay(3000);

  coborare_mana();

 // !flag_ridicat;
  stop_motor();

  delay(3000);
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

  while(angle > 0)
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