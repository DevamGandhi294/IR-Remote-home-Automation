#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// WiFi credentials
const char* ssid = "DEVGANDHI";
const char* password = "9724802622";

// Device Details
const String DEVICE_SERIAL = "ESP001";  // Unique serial number for this device

ESP8266WebServer server(80);

// Pin Definition
const int relayPin = D1;  // GPIO5
const int irPin = D2;     // GPIO4 (IR Receiver)

// Initialize IR receiver
IRrecv irrecv(irPin);
decode_results results;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);  // Initialize relay to OFF

  // Start IR receiver
  irrecv.enableIRIn();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Device Serial: ");
  Serial.println(DEVICE_SERIAL);

  // API Routes
  // Get device info
  server.on("/info", HTTP_GET, []() {
    String response = "{";
    response += "\"serial\":\"" + DEVICE_SERIAL + "\",";
    response += "\"ip\":\"" + WiFi.localIP().toString() + "\"";
    response += "}";
    server.send(200, "application/json", response);
  });

  // Control relay via web
  server.on("/relay/on", HTTP_GET, []() {
    digitalWrite(relayPin, LOW);
    server.send(200, "text/plain", "Relay ON");
    Serial.println("Relay turned ON");
  });

  server.on("/relay/off", HTTP_GET, []() {
    digitalWrite(relayPin, HIGH);
    server.send(200, "text/plain", "Relay OFF");
    Serial.println("Relay turned OFF");
  });

  // Get relay status
  server.on("/status", HTTP_GET, []() {
    String status = digitalRead(relayPin) == LOW ? "ON" : "OFF";
    server.send(200, "text/plain", status);
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  // Check for IR remote signals
  if (irrecv.decode(&results)) {
    Serial.print("IR Code Received: ");
    Serial.println(results.value, HEX);

    handleIRCommand(results.value);
    irrecv.resume(); // Receive next signal
  }
}

void handleIRCommand(unsigned long value) {
  switch (value) {
    case 0xFF6897: // Button '1' on the remote
      digitalWrite(relayPin, LOW); // Turn on the relay
      Serial.println("Relay ON via IR Remote");
      break;
      
    case 0xFF30CF: // Button '2' on the remote
      digitalWrite(relayPin, HIGH); // Turn off the relay
      Serial.println("Relay OFF via IR Remote");
      break;
      
    default:
      Serial.println("Unknown IR button");
      break;
  }
}