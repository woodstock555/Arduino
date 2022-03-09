#include <SoftwareSerial.h>
//Привет!
//SoftwareSerial mySerial(2, 3); // RX, TX
SoftwareSerial mySerial(A0,A1); // RX, TX

#include <AFMotor.h>      // Подключаем библиотеку AFMotor
AF_DCMotor motor(1);      // Указываем какому порту подключен двигатель (1 - 4)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  motor.setSpeed(200);    // Начальная скорость вращения
  motor.run(RELEASE);     // Останавливаем двигатель
}
void loop() {
  int val;
  char key;
  if (mySerial.available()>1) {
    key = mySerial.read();
    val = mySerial.parseInt();
    switch (key) {
      case 'b': // Вращение назад
      motor.run(BACKWARD);
      break;
      
      case 'f': // Вращение вперед
      motor.run(FORWARD);     // Вращение двигателя вперед
      break;
      
      case 's': // Установка скорости вращения
      motor.setSpeed(val);    // Отправка скорости
      break;
      
      case 'r': // Стоп
      motor.run(RELEASE);     // Останавливаем двигатель
      break;
    
    }
    Serial.println("Message Received: ");
    Serial.println("key="+key);
    Serial.println("val="+String(val, DEC));
    delay(10);
  }

}
