#include <SoftwareSerial.h>

// Пины для подключения экрана Nextion
const int NEXTION_RX = 2;  // Arduino TX -> Nextion RX
const int NEXTION_TX = 3;  // Arduino RX <- Nextion TX

// Создаем объект для работы с экраном
SoftwareSerial nextionSerial(NEXTION_RX, NEXTION_TX);

// Переменные для таймера
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
bool isRunning = false;

// Функция для отправки команды на экран Nextion
void sendCommand(const char* cmd) {
  Serial.print("Sending command: ");
  Serial.println(cmd);
  
  nextionSerial.print(cmd);
  nextionSerial.write(0xFF);
  nextionSerial.write(0xFF);
  nextionSerial.write(0xFF);
  delay(10);
}

// Функция обновления времени на экране
void updateDisplay() {
  unsigned long currentTime;
  if (isRunning && startTime > 0) {
    currentTime = elapsedTime + (millis() - startTime);
  } else {
    currentTime = elapsedTime;
  }
  
  // Преобразуем миллисекунды в часы, минуты, секунды
  unsigned long seconds = currentTime / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  
  seconds %= 60;
  minutes %= 60;
  
  // Формируем команду для обновления текста
  char buffer[50];
  sprintf(buffer, "t0.txt=\"%02lu:%02lu:%02lu\"", hours, minutes, seconds);
  sendCommand(buffer);
}

void setup() {
  // Инициализация последовательных портов
  Serial.begin(9600);
  nextionSerial.begin(9600);
  
  Serial.println("Starting...");
  delay(500);
  
  // Очистка экрана и переход на страницу 0
  sendCommand("cls BLACK");
  sendCommand("page 0");
  
  // Настройка текстового поля
  sendCommand("t0.bco=BLACK"); // Черный фон
  sendCommand("t0.pco=65535"); // Белый текст
  sendCommand("t0.txt=\"00:00:00\"");
  
  // Настройка кнопок
  // START - b2 (ID 4)
  sendCommand("b2.txt=\"START\"");
  sendCommand("b2.pco=65535"); // Белый текст
  sendCommand("b2.bco=1024"); // Темно-зеленый фон
  sendCommand("b2.press=1"); // Включаем отправку события при нажатии
  
  // STOP - b0 (ID 2)
  sendCommand("b0.txt=\"STOP\"");
  sendCommand("b0.pco=65535");
  sendCommand("b0.bco=63488"); // Красный фон
  sendCommand("b0.press=1");
  
  // RESET - b1 (ID 3)
  sendCommand("b1.txt=\"RESET\"");
  sendCommand("b1.pco=65535");
  sendCommand("b1.bco=64512"); // Желтый фон
  sendCommand("b1.press=1");
  
  Serial.println("Setup complete");
  updateDisplay();
}

void loop() {
  // Отладка входящих данных
  while (nextionSerial.available()) {
    byte data = nextionSerial.read();
    Serial.print("Received byte: 0x");
    Serial.println(data, HEX);
    
    if (data == 0x65) { // Код нажатия кнопки
      Serial.println("Button press detected!");
      delay(10); // Даем время на получение всех данных
      
      if (nextionSerial.available() >= 3) {
        byte page = nextionSerial.read();
        byte component = nextionSerial.read();
        byte event = nextionSerial.read();
        
        Serial.print("Page: ");
        Serial.print(page);
        Serial.print(" Component: ");
        Serial.print(component);
        Serial.print(" Event: ");
        Serial.println(event);
        
        if (page == 0) {
          switch (component) {
            case 4: // Start (b2)
              Serial.println("Start pressed");
              isRunning = true;
              if (startTime == 0) {
                startTime = millis();
                Serial.println("Timer started");
                Serial.print("startTime = ");
                Serial.println(startTime);
              }
              break;
              
            case 2: // Stop (b0)
              Serial.println("Stop pressed");
              isRunning = false;
              if (startTime > 0) {
                elapsedTime += millis() - startTime;
                startTime = 0;
                Serial.println("Timer stopped");
                Serial.print("elapsedTime = ");
                Serial.println(elapsedTime);
              }
              updateDisplay();
              break;
              
            case 3: // Reset (b1)
              Serial.println("Reset pressed");
              isRunning = false;
              startTime = 0;
              elapsedTime = 0;
              Serial.println("Timer reset");
              updateDisplay();
              break;
          }
        }
      }
    }
  }
  
  // Обновляем время на экране каждые 50мс
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= 50) {
    updateDisplay();
    lastUpdate = millis();
  }
}
