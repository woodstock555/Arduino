#include <AFMotor.h>

AF_DCMotor motor(1);

int encoder_pin = 2; // импульсные сигналы от модуля
unsigned int rpm; // количество оборотов в минуту
volatile byte pulses; // количество импульсов
unsigned long timeold;
// количество импульсов на оборот
// в зависимости от вашего энкодерного диска
unsigned int pulsesperturn = 20;


void counter()
{
   //обновление счета импульсов
   pulses++;
}
void setup()
{
   Serial.begin(9600);
   pinMode(encoder_pin, INPUT);
   //Прерывание 0 на цифровой линии 2
   //Срабатывание триггера по спаду сигнала
   attachInterrupt(digitalPinToInterrupt(2), counter, RISING);
   // Инициализация
   pulses = 0;
   rpm = 0;
   timeold = 0;

   // turn on motor
   motor.setSpeed(200);
   motor.run(RELEASE);
}

void loop()
{
//   if (millis() - timeold >= 1000) {
//      //Не обрабатывать прерывания во время счёта
//      detachInterrupt(0);
//      rpm = (60 * 1000 / pulsesperturn )/ (millis() - timeold)* pulses;
//      timeold = millis();
//      pulses = 0;
//      Serial.print("RPM = ");
//      Serial.println(rpm,DEC);
//      //Перезагрузка процесса обработки прерываний
//      attachInterrupt(0, counter, FALLING);
//   }
 
  Serial.println("tick");
  
  motor.run(FORWARD);
  motor.setSpeed(200); 
  while (pulses<20) {
    delay(10);
  }
  motor.run(RELEASE);
  Serial.print("p=");
  Serial.print(pulses,DEC);
  pulses=0;
  
  delay(2000);
}
