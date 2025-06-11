# Проєкт РК-годинника на ESP8266

Цей проєкт являє собою розумний цифровий годинник, побудований з використанням мікроконтролера ESP8266 та РК-дисплея 16x2 I2C. Пристрій відображає поточний час, погодні дані (температуру та вологість), а також надає веб-портал конфігурації Wi-Fi, коли немає доступної мережі Wi-Fi.

## Функції

### 1. Портал конфігурації Wi-Fi (LittleFS + Captive Portal)

* При запуску ESP8266 намагається підключитися до раніше збереженої мережі Wi-Fi, використовуючи облікові дані, що зберігаються у файловій системі LittleFS.
* Якщо дійсні облікові дані не знайдено або з'єднання не вдалося, годинник відкриває локальну точку доступу (SSID: `ClockAP`, пароль: `setclock`) і запускає веб-сервер.
* Користувач може отримати доступ до закритого порталу за адресою `http://192.168.4.1/` та ввести Wi-Fi облікові дані за допомогою HTML-форми.
* Введені облікові дані зберігаються у файлі конфігурації JSON у файловій системі LittleFS і використовуються для подальших підключень.

### 2. Автоматичне нічне затемнення

* З 2:00 до 5:00 ранку підсвічування дисплея приглушується, щоб зменшити світлові перешкоди.
* Це визначається шляхом порівняння поточного часу з попередньо визначеним інтервалом в основному циклі.

### 3. Фізичний поворотний перемикач для вибору режиму дисплея

* Поворотний перемикач зі спільним входом та 7 дискретними виходами підключено до виводів GPIO.
* Залежно від положення перемикача, дисплей перемикається між наступними режимами:

  * Тільки годинник.
  * Тільки температура
  * Тільки вологість
  * Все разом (комбінований режим)

## Використане обладнання

* **Мікроконтролер:** ESP8266 (модуль ESP-12E)
* **Дисплей:** 16x2 I2C LCD (адреса: `0x26`)
* **Датчики:** OpenWeatherMap API, що використовується для отримання даних про температуру та вологість
** Перемикач:** Поворотний перемикач з 1 загальною та 7 вихідними клемами

## Стек програмного забезпечення

* **PlatformIO** як середовище збірки
* **Фреймворк:** Arduino для ESP8266
* **Файлова система:** LittleFS для зберігання конфігурації
* **Бібліотеки веб-сервера:**
ESPAsyncWebServer,
AsyncFsWebServer
* **JSON парс:** ArduinoJson
* **Кастомні бібліотеки для інтерфейсу користувача:** BigNumbers_I2C, LiquidCrystal_I2C

## Структура папок
```
project_root/
├── data/
│ ├── setup/
│ ├── index.html        # Форма конфігурації Wi-Fi
│ ├── wifi_conf.json    # Збережені SSID/пароль (не зберігаються в git)
├── include/
│ ├── clock. h          # Синхронізація NTP та обробка часу
│ ├── lcd.h             # Логіка роботи РК-дисплея
│ ├── led_sts.h         # Керування світлодіодним індикатором
│ ├── special_chars. h  # Спеціальні визначення символів LCD
│ ├── weather.h         # Запити API погоди
│ └── wifiConf. h       # Конфігурація Wi-Fi та логіка порталу
├── src/
│ └── main.cpp          # Точка входу до проєкту
├── platformio.ini      # Конфігурація збірки
└── README.md
```

## Інструкції з налаштування

1. **Встановіть PlatformIO** у код Visual Studio.
2. **Підключіть ESP8266** через USB (переконайтеся, що це правильний COM-порт).
3. **Завантажте прошивку:**.
 ```sh
 pio run -t upload
 ```
4. **Завантажте файлову систему (форму та конфігурацію Wi-Fi):**
```sh
 pio run -t uploadfs
 ```
5. **Послідовний вихід монітора (необов'язково):**
```sh
pio device monitor --baud 115200
```

----------------------------------------------------------

# ESP8266 LCD Clock Project

This project is a smart digital clock built using an ESP8266 microcontroller and a 16x2 I2C LCD display. The device displays the current time, weather data (temperature and humidity), and provides a web-based Wi-Fi configuration portal when no known Wi-Fi network is available.

## Features

### 1. Wi-Fi Configuration Portal (LittleFS + Captive Portal)

* On startup, the ESP8266 attempts to connect to a previously saved Wi-Fi network using credentials stored in the LittleFS filesystem.
* If no valid credentials are found or the connection fails, the clock opens a local Access Point (SSID: `ClockAP`, password: `setclock`) and starts a web server.
* The user can access the captive portal via `http://192.168.4.1/` and input Wi-Fi credentials via an HTML form.
* Submitted credentials are saved in a JSON configuration file on the LittleFS filesystem and used for future connections.

### 2. Automatic Nighttime Dimming

* Between 2:00 a.m. and 5:00 a.m., the display backlight is dimmed to reduce light disturbance.
* This is determined by checking the current time against the predefined interval in the main loop.

### 3. Physical Rotary Switch for Display Mode Selection

* A rotary switch with a shared input and 7 discrete outputs is connected to GPIO pins.
* Based on the position of the switch, the display changes between the following modes:

  * Clock only
  * Temperature only
  * Humidity only
  * All together (combined mode)

## Hardware Used

* **Microcontroller:** ESP8266 (ESP-12E module)
* **Display:** 16x2 I2C LCD (Address: `0x26`)
* **Sensors:** OpenWeatherMap API used for fetching temperature and humidity data
* **Switch:** Rotary switch with 1 common and 7 output terminals

## Software Stack

* **PlatformIO** as the build environment
* **Framework:** Arduino for ESP8266
* **Filesystem:** LittleFS for configuration storage
* **Web server libraries:**
ESPAsyncWebServer,
AsyncFsWebServer
* **JSON Parsing:** ArduinoJson
* **Custom UI Libraries:** BigNumbers_I2C, LiquidCrystal_I2C

## Folder Structure
```
project_root/
├── data/
│   └── setup/
│       ├── index.html       # Wi-Fi config form
│       └── wifi_conf.json   # Stored SSID/password (don't get synced to git)
├── include/
│   ├── clock.h              # NTP sync and time handling
│   ├── lcd.h                # LCD display logic
│   ├── led_sts.h            # LED indicator control
│   ├── special_chars.h      # Custom LCD character definitions
│   ├── weather.h            # Weather API requests
│   └── wifiConf.h           # Wi-Fi config & captive portal logic
├── src/
│   └── main.cpp             # Project entry point
├── platformio.ini           # Build configuration
└── README.md
```

## Setup Instructions

1. **Install PlatformIO** in Visual Studio Code.
2. **Connect the ESP8266** via USB (ensure correct COM port).
3. **Upload firmware:**

```sh
pio run -t upload
```
4. **Upload filesystem (Wi-Fi form & config):**

```sh
pio run -t uploadfs
```
5. **Monitor serial output (optional):**
```sh
pio device monitor --baud 115200
```
