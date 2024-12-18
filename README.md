# Arduino Nextion Timer

Простой, но функциональный таймер, реализованный на Arduino с использованием дисплея Nextion. Проект демонстрирует базовое взаимодействие между Arduino и Nextion дисплеем, обеспечивая точное измерение времени с возможностью запуска, остановки и сброса.

## Возможности

- ⏱️ Точное измерение времени в формате ЧЧ:ММ:СС
- ▶️ Кнопка START для запуска таймера
- ⏹️ Кнопка STOP для приостановки
- 🔄 Кнопка RESET для сброса
- 📱 Современный пользовательский интерфейс на дисплее Nextion
- 🔄 Обновление дисплея в реальном времени (каждые 100мс)

## Необходимое оборудование

- Arduino (любая модель)
- Дисплей Nextion (любая модель)
- Соединительные провода
- USB кабель для программирования Arduino

## Схема подключения

1. **Arduino → Nextion**
   - Arduino TX (Pin 2) → Nextion RX
   - Arduino RX (Pin 3) → Nextion TX
   - 5V → 5V
   - GND → GND

## Установка

1. Скачайте и установите [Arduino IDE](https://www.arduino.cc/en/software)
2. Скачайте и установите [Nextion Editor](https://nextion.tech/nextion-editor/)
3. Загрузите файлы проекта:
   - `script` - скетч для Arduino
   - `nextion_timer` - файл интерфейса для Nextion дисплея

## Настройка проекта

1. **Настройка Nextion дисплея:**
   - Откройте файл `nextion_timer` в Nextion Editor
   - Скомпилируйте проект
   - Загрузите прошивку на дисплей

2. **Настройка Arduino:**
   - Откройте `script` в Arduino IDE
   - Выберите правильную плату Arduino и порт
   - Загрузите скетч на Arduino

## Использование

1. После загрузки всех файлов и правильного подключения, на дисплее появится интерфейс с тремя кнопками и полем отображения времени
2. **Управление таймером:**
   - Нажмите START для запуска таймера
   - Нажмите STOP для приостановки (текущее время сохранится)
   - Нажмите RESET для сброса таймера в 00:00:00

## Отладка

Если что-то работает не так:
1. Проверьте правильность подключения проводов
2. Убедитесь, что скорость передачи данных (baud rate) установлена на 9600 как в Arduino, так и на дисплее
3. Откройте Serial Monitor в Arduino IDE для просмотра отладочных сообщений

## Технические детали

- Скорость передачи данных: 9600 бод
- Используется программный UART (SoftwareSerial)
- Частота обновления дисплея: каждые 100мс
- Точность измерения времени: миллисекунды
- Формат отображения: ЧЧ:ММ:СС

## Структура проекта

```
nextion_timer/
├── script                # Основной скетч Arduino
├── nextion_timer         # Файл интерфейса Nextion
└── README.md             # Документация проекта
```
