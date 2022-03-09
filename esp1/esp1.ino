#define RXp2 16
#define TXp2 17

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
}
void loop() {
  char key = 'f';
  int val = 200;
  Serial2.print(key);
  Serial2.print(val);
  delay(3000);
  key='r';
  Serial2.print(key);
  Serial2.print(val);
  delay(3000);
}
