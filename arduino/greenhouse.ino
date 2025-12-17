#include <WiFi.h>
#include <Firebase_ESP_Client.h>

const char* ssid = "negromoves";      
const char* password = "hhannalizu1337"; 

#define API_KEY "APIFirebaseAnda"        
#define DATABASE_URL "https://project-anda-id.firebasedatabase.app/"
#define USER_EMAIL "yeyo@gmail.com" 
#define USER_PASSWORD "yeyo12"         

#define dht 23
#define ldr 19
#define soil 18

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("\n=== SMART PLANT GREENHOUSE ===");
  Serial.println("Inisialisasi sistem...\n");

  pinMode(LDR_PIN, INPUT);
  pinMode(SOIL_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(FLAME_PIN, INPUT);
  pinMode(OBJECT_PIN, INPUT);

  connectWiFi();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Sinkronisasi waktu dengan NTP...");
  delay(2000);

  config.api_key = AIzaSyBWykaVcM4DaQ-XBfF6CLQXoX2bfi96Cto;
  config.database_url = https://minggu11-d956b-default-rtdb.firebaseio.com/;
  auth.user.email = yeyo@gmail.com;
  auth.user.password = yeyo12;
  config.token_status_callback = tokenStatusCallback;

  Serial.println("Menghubungkan ke Firebase...");
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  unsigned long fbStart = millis();
  while (!Firebase.ready() && millis() - fbStart < 10000) {
    Serial.print(".");
    delay(500);
  }

  if (Firebase.ready()) {
    Serial.println("\n✓ Firebase terhubung");
    Serial.println("✓ Sistem siap monitoring!\n");
  } else {
    Serial.println("\n✗ Firebase gagal terhubung, sistem tetap berjalan...\n");
  }
}


void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi terputus! Mencoba reconnect...");
    connectWiFi();
  }

  unsigned long now = millis();
  if (now - lastSensorUpdate > sensorInterval) {
    lastSensorUpdate = now;
    bacaDanKirimData();
  }
}

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Menghubungkan ke WiFi");
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    if (millis() - start > 20000) {
      Serial.println("\n✗ Gagal terhubung WiFi - restart...");
      ESP.restart();
    }
  }
  Serial.println();
  Serial.println("✓ WiFi Terhubung!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
