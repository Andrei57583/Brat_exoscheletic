   /*
  EMG-Muscular-Signal-Sensor
  made on 26 Jan 2021
  by Amir Mohammad Shojaee @ Electropeak
  Home

*/

void setup() {
Serial.begin(9600);
}

void loop() {
Serial.println(analogRead(A0));
delay(100);
}
