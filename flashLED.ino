
const int iPinLED = 2;

void setup() {
   // put your setup code here, to run once:
   pinMode(iPinLED, OUTPUT);

}

void loop() {
   // put your main code here, to run repeatedly:
   digitalWrite(iPinLED, HIGH);
   delay(500);
   digitalWrite(iPinLED, LOW);
   delay(1000);

}