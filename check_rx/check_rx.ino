// ПРИМЕР ДЛЯ ПРОВЕРКИ РАБОТЫ ПРИЁМНИКА (MX-RM-5V) 
//
// Приёмник   подключён к выводу D3
// Передатчик подключён к выводу D4
//
// Алгоритм: Значение массива i отправляется передатчиком, принимается приёмником в массив j и выводится на монитор
// Если приёмник и передатчик работают, то на монитере будут появляться строки Hello World с указанием номера трубы, по которой они получены
//
// Подключаем библиотеку:
//#include <iarduino_RF433_Transmitter.h>                   // Подключаем библиотеку для работы с передатчиком FS1000A
#include <iarduino_RF433_Receiver.h>                      // Подключаем библиотеку для работы с приёмником MX-RM-5V

// Объявляем объекты, переменные и массивы:
//iarduino_RF433_Transmitter radioTX(4);                    // Создаём объект radioTX для работы с библиотекой iarduino_RF433, указывая номер вывода к которому подключён передатчик
iarduino_RF433_Receiver    radioRX(3);                    // Создаём объект radioRX для работы с библиотекой iarduino_RF433, указывая номер вывода к которому подключён приёмник (можно подключать только к выводам использующим внешние прерывания)
//char                     i[]="Hello World";               // Создаём массив для передачи данных
char                     j[12];                           // Создаём массив для приёма   данных
uint8_t                  k;                               // Создаём переменную, в которую получим номер трубы, по которой приняты данные

void setup(){
//  ===============================
    Serial.begin(9600);                                   // Инициируем передачу данных по последовательному порту на скорости 9600 бит/сек
//  =============================== ПЕРЕДАТЧИК
//    radioTX.begin(1000);                                  // Инициируем работу передатчика FS1000A на скорости 1 кбит/сек
//  radioTX.setDataRate(i433_1KBPS);                      // Скорость передачи данных можно изменить вызвав данную функцию в любом месте кода. Параметры (i433_5KBPS, i433_4KBPS, i433_3KBPS, i433_2KBPS, i433_1KBPS, i433_500BPS, i433_100BPS), i433_1KBPS - 1кбит/сек
//    radioTX.openWritingPipe(5);                           // Открываем 5 трубу для передачи данных (передатчик может передавать данные только по одной из труб: 0...7). Если повторно вызвать функцию openWritingPipe указав другой номер трубы, то передатчик начнёт передавать данные по вновь указанной трубе
//  =============================== ПРИЁМНИК
    radioRX.begin(1000);                                  // Инициируем работу приёмника MX-RM-5V (в качестве параметра можно указать скорость ЧИСЛО бит/сек, тогда можно не вызывать функцию setDataRate)
//  radioRX.setDataRate(i433_1KBPS);                      // Скорость приёма данных можно изменить вызвав данную функцию в любом месте кода. Параметры (i433_5KBPS, i433_4KBPS, i433_3KBPS, i433_2KBPS, i433_1KBPS, i433_500BPS, i433_100BPS), i433_1KBPS - 1кбит/сек
    radioRX.openReadingPipe (5);                          // Открываем 5 трубу для приема данных (если вызвать функцию без параметра, то будут открыты все трубы сразу, от 0 до 7)
//  radioRX.openReadingPipe (2);                          // Открываем 2 трубу для приёма данных (таким образом можно прослушивать сразу несколько труб)
//  radioRX.closeReadingPipe(2);                          // Закрываем 2 трубу от  приёма данных (если вызвать функцию без параметра, то будут закрыты все трубы сразу, от 0 до 7)
    radioRX.startListening  ();                           // Включаем приемник, начинаем прослушивать открытую трубу
//  radioRX.stopListening   ();                           // Выключаем приёмник, если потребуется
}

void loop(){
//  =============================== ПРИЁМНИК
    if(radioRX.available(&k)){                            // Если в буфере имеются данные принятые приёмником, то получаем номер трубы в переменную k и ...
       radioRX.read(&j, sizeof(j));                       // Читаем данные в массив j и указываем сколько байт читать
       Serial.print(j);                                   // Выводим полученные данные на монитор
       Serial.println((String)" (Pipe="+k+")");           // Выводим номер трубы, по которой эти данные получены. Так можно определить, от кокого передатчика они получены
    }
//  =============================== ПЕРЕДАТЧИК
//    radioTX.write(&i, sizeof(i));                         // Отправляем данные из массива i указывая сколько байт массива мы хотим отправить
//    delay(100);                                           // Ждем 200мс
}
