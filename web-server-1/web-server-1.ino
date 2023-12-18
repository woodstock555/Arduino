#include <WiFi.h>
#include <Wire.h>
#include <DHT.h>

#define DHTTYPE DHT11   // DHT 11

// DHT Sensor
uint8_t DHTPin = 4; 
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                
float Temperature;
float Humidity;

// здесь пишем учетные данные своей сети:
const char* ssid     = "ASUS_34401";
const char* password = "03597bbdb";

// Задаем статический IP-адрес:
IPAddress local_IP(192, 168, 1, 110);
// Задаем IP-адрес сетевого шлюза:
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   // опционально
IPAddress secondaryDNS(8, 8, 4, 4); // опционально

WiFiServer server(80);
String header;

int pirPin = 2;                      // Указываем пин датчика 
int motionDetected = 0;              // Переменная для обнаружения движения
int pirValue;                        // Переменная для сохранения значения из PIR

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

pinMode(DHTPin, INPUT);
dht.begin();   

pinMode(pirPin, INPUT);            // Установка пин как вход
// Начальная задержка 1 минута, для стабилизации датчика// 
//delay(60000);
//delay(60000);
    
// подключаемся к WiFi-сети при помощи SSID и пароля:
  Serial.print("Connecting to ");  //  "Подключение к"
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // печатаем локальный IP-адрес и запускаем веб-сервер:
  Serial.println("");
  Serial.println("WiFi connected.");  //  "WiFi подключен."
  Serial.println("IP address: ");  //  "IP-адрес: "
  Serial.println(WiFi.localIP());
  server.begin();
}

String metricLine(String metricName, int value)
{
  String s="";
  // metric_without_timestamp_and_labels 12.47
  return metricName+" "+value;
}

void loop() {
delay(500);
  pirValue = digitalRead(pirPin);    // Считываем значение от датчика движения
  Serial.println("pirValue - "+String(pirValue));
  if (pirValue == 1)                 // Если движение есть, делаем задержку в 3 с.
  {               
    //digitalWrite(detectedLED, HIGH);
    motionDetected = 1;
    //Serial.println("motionDetected - "+String(motionDetected));
    //delay(3000);
  } else {
    //digitalWrite(detectedLED, LOW);
    motionDetected = 0;
    //Serial.println("motionDetected - "+String(motionDetected));
  }
    
  // put your main code here, to run repeatedly:
  // начинаем прослушивать входящих клиентов:
  //WiFiClient client = server.available();

//if (client) {                       // если подключился новый клиент,     
//    Serial.println("New Client.");  // печатаем сообщение
//                                    // «Новый клиент.»
//                                    // в мониторе порта;
//    String currentLine = "";        // создаем строку для хранения
//                                    // входящих данных от клиента;
//    while (client.connected()) {    // цикл while() будет работать
//                                    // все то время, пока клиент
//                                    // будет подключен к серверу;
//      if (client.available()) {     // если у клиента есть данные,
//                                    // которые можно прочесть, 
//        char c = client.read();     // считываем байт, а затем                 
//        Serial.write(c);            // печатаем его в мониторе порта 
//        header += c;
//        if (c == '\n') {            // если этим байтом является
//                                    // символ новой строки
//          // если мы получим два символа новой строки подряд,
//          // то это значит, что текущая строчка пуста;
//          // это конец HTTP-запроса клиента,
//          // а значит – пора отправлять ответ:
//          if (currentLine.length() == 0) {
//            Serial.println("Header - "+header);
//            if (header.indexOf("GET /metrics") >= 0) {
//            // HTTP-заголовки всегда начинаются
//            // с кода ответа (например, «HTTP/1.1 200 OK»)
//            // и информации о типе контента
//            // (чтобы клиент понимал, что получает);
//            // в конце пишем пустую строчку:
//            client.println("HTTP/1.1 200 OK");
//            client.println("Content-type:text/plain");
//            client.println("Connection: close");
//                         //  "Соединение: отключено"
//            client.println();
//            // показываем веб-страницу с помощью этого HTML-кода:
//            //client.print("# HELP abcd1 The total number of HTTP requests.\n");
//            //client.print("# TYPE abcd1 counter\n");
//            //client.print("http_requests_total 1027");
//            //client.print("metric_without_timestamp_and_labels 12,47");
//            Temperature = dht.readTemperature(); // Gets the values of the temperature
//            Humidity = dht.readHumidity(); // Gets the values of the humidity 
//            client.print("MyTemperature "+String(Temperature)+"\n");
//            client.print("MyHumidity "+String(Humidity)+"\n");
//
//            /*client.println("<!DOCTYPE html><html>");
//            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
//            client.println("<link rel=\"icon\" href=\"data:,\">");
//            // задаем CSS-стили для таблицы: 
//            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial;}");
//            client.println("table { border-collapse: collapse; width:35%; margin-left:auto; margin-right:auto; }");
//            client.println("th { padding: 12px; background-color: #0043af; color: white; }");
//            client.println("tr { border: 1px solid #ddd; padding: 12px; }");
//            client.println("tr:hover { background-color: #bcbcbc; }");
//            client.println("td { border: none; padding: 12px; }");
//            client.println(".sensor { color:white; font-weight: bold; background-color: #bcbcbc; padding: 1px; }");
//            
//            // заголовок веб-страницы:
//            client.println("</style></head><body><h1>ESP32 with BME280</h1>");
//            client.println("<table><tr><th>MEASUREMENT</th><th>VALUE</th></tr>");
//            client.println("<tr><td>Temp. Celsius</td><td><span class=\"sensor\">");
//            client.println(123);
//            client.println(" *C</span></td></tr>");  
//            client.println("<tr><td>Temp. Fahrenheit</td><td><span class=\"sensor\">");
//            client.println(1.8 * 123 + 32);
//            client.println(" *F</span></td></tr>");       
//            client.println("<tr><td>Pressure</td><td><span class=\"sensor\">");
//            client.println(853 / 100.0F);
//            client.println(" hPa</span></td></tr>");
//            client.println("<tr><td>Approx. Altitude</td><td><span class=\"sensor\">");
//            client.println(456);
//            client.println(" m</span></td></tr>"); 
//            client.println("<tr><td>Humidity</td><td><span class=\"sensor\">");
//            client.println(56);
//            client.println(" %</span></td></tr>"); 
//            client.println("</body></html>");
//            */
//
//            // конец HTTP-ответа задается 
//            // с помощью дополнительной пустой строки:
//            //client.println();
//            }
//            // выходим из цикла while():
//            break;
//          } else {  // если получили символ новой строки,
//                    // очищаем переменную «currentLine»
//            currentLine = "";
//          }
//        } else if (c != '\r') {  // если получили любые данные,
//                                 // кроме символа возврата каретки,
//          currentLine += c;      // добавляем эти данные 
//                                 // в конец строки «currentLine»
//        }
//      }
//    }
//    // очищаем переменную «header»:
//    header = "";
//    // отключаем соединение:
//    client.stop();
//    Serial.println("Client disconnected.");
//                // "Клиент отключился.")
//    Serial.println("");
//  }              
}
