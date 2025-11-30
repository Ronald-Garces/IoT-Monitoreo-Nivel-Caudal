#include <WiFi.h>
#include <PubSubClient.h>

// --------------- PINES ------------------
#define POT_PIN 34   // Potenciómetro (Sensor de nivel)
#define LED_BAJO 14  // LED Rojo
#define LED_MEDIO 12 // LED Naranja
#define LED_ALTO 13  // LED Verde

// ---------------- WIFI ------------------
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ---------------- BROKER MQTT ------------
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

const char* topic_analogico = "analogico";

// ----------------------------------------
void setup_wifi() {
  Serial.println("Conectando a WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }

  Serial.println("\nWiFi Conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ----------------------------------------
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando MQTT...");
    if (client.connect("ESP32_NIVELADOR")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Fallo, rc=");
      Serial.print(client.state());
      Serial.println(" Reintentando en 5s...");
      delay(5000);
    }
  }
}

// ----------------------------------------
void setup() {
  Serial.begin(115200);

  pinMode(LED_BAJO, OUTPUT);
  pinMode(LED_MEDIO, OUTPUT);
  pinMode(LED_ALTO, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

// ----------------------------------------
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  // Leer potenciómetro (0 - 4095)
  int rawValue = analogRead(POT_PIN);

  // Mapear a nivel en centímetros (0 - 1000)
  float nivel_cm = map(rawValue, 0, 4095, 0, 100000) / 100.0;

  // Mostrar por serial
  Serial.print("Nivel: ");
  Serial.print(nivel_cm);
  Serial.println(" cm");

  // Publicar a MQTT
  client.publish(topic_analogico, String(nivel_cm).c_str());

  // ----------------- LEDS ------------------
  if (nivel_cm <= 300) {
    digitalWrite(LED_BAJO, HIGH);
    digitalWrite(LED_MEDIO, LOW);
    digitalWrite(LED_ALTO, LOW);
  }
  else if (nivel_cm <= 600) {
    digitalWrite(LED_BAJO, LOW);
    digitalWrite(LED_MEDIO, HIGH);
    digitalWrite(LED_ALTO, LOW);
  }
  else {
    digitalWrite(LED_BAJO, LOW);
    digitalWrite(LED_MEDIO, LOW);
    digitalWrite(LED_ALTO, HIGH);
  }

  delay(400);
}
