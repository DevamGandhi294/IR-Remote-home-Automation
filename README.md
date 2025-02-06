# Basic Home Automation System 🏡🔌

This project is a **basic home automation system** that allows users to control a **relay switch** (for lights, fans, etc.) using an **ESP8266 microcontroller** and a **Flutter mobile application**.

## 🔹 Features
- **Remote Control**: Turn appliances ON/OFF via a mobile app (WiFi-based control).
- **IR Remote Support**: Control appliances using an IR remote.
- **Real-Time Status**: View relay state via a REST API.

## 🔹 Tech Stack
- **ESP8266 (Arduino)** – Microcontroller for automation  
- **Flutter (Dart)** – Mobile application  
- **HTTP API** – Communication between the app and ESP8266  

## 🔹 Circuit Connections

### **ESP8266 & Relay**
| ESP8266 Pin | Relay Module |
|-------------|-------------|
| D1 (GPIO5)  | IN (Relay)  |
| GND         | GND         |
| 3.3V        | VCC         |

### **ESP8266 & IR Receiver**
| ESP8266 Pin | IR Receiver Pin |
|-------------|----------------|
| D2 (GPIO4)  | Data (OUT)      |
| GND         | GND            |
| 3.3V        | VCC            |

### **ESP8266 & RFID RC522**
| ESP8266 Pin | RFID RC522 Pin |
|-------------|---------------|
| D4 (GPIO2)  | SDA           |
| D5 (GPIO14) | SCK           |
| D7 (GPIO13) | MOSI          |
| D6 (GPIO12) | MISO          |
| D3 (GPIO0)  | RST           |
| GND         | GND           |
| 3.3V        | VCC           |

### **ESP8266 & Servo Motor**
| ESP8266 Pin | Servo Pin  |
|-------------|------------|
| D8 (GPIO15) | Signal     |
| GND         | GND        |
| 3.3V        | VCC        |

## 🔹 How to Use
1. **Upload the ESP8266 Code** to your board.
2. **Connect to WiFi** (SSID & password are pre-set in code).
3. **Run the Flutter App** and enter the **ESP8266 IP Address**.
4. **Control appliances remotely!**

## 🔹 Getting Started (For Developers)
1. Clone the repository:  
   ```sh
   git clone https://github.com/yourusername/home-automation.git
   cd home-automation
