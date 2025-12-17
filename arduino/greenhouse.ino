#include <WiFi.h>
#include <Firebase_ESP_Client.h>

/* ================= WIFI ================= */
const char* ssid = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";

/* ================= FIREBASE ================= */
#define API_KEY "AIzaSyBWykaVcM4DaQ-XBfF6CLQXoX2bfi96Cto"
#define DATABASE_URL "https://minggu11-d956b-default-rtdb.firebaseio.com/"
#define USER_EMAIL "emailfirebase@gmail.com"
#define USER_PASSWORD "passwordfirebase"

/* ================= PIN ================= */
#define LDR_PIN 19
#define SOIL_PIN 18
#define PIR_PIN 23

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

/* ================= SETUP ================= */
void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== SMART PLANT GREENHOUSE ===");
  Serial.println("Inisialisasi sistem...\n");

  // Pin modes
  pinMode(LDR_PIN, INPUT);
  pinMode(SOIL_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi Terhubung!");
  Serial.println(WiFi.localIP());

  // Firebase config
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  unsigned long fbStart = millis();
  while (!Firebase.ready() && millis() - fbStart < 10000) {
    Serial.print(".");
    delay(500);
  }

  if (Firebase.ready()) {
    Serial.println("\n✔ Firebase terhubung");
    Serial.println("✔ Sistem siap monitoring\n");
  } else {
    Serial.println("\n✖ Firebase gagal terhubung, sistem tetap berjalan\n");
  }
}

/* ================= LOOP ================= */
void loop() {
  // Cek koneksi WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi terputus! Mencoba reconnect...");
    WiFi.begin(ssid, password);
  }

  int soil = analogRead(SOIL_PIN);
  int light = analogRead(LDR_PIN);
  int motion = digitalRead(PIR_PIN);

  Firebase.RTDB.setInt(&fbdo, "greenhouse/sensors/soilMoisture", soil);
  Firebase.RTDB.setInt(&fbdo, "greenhouse/sensors/lightLevel", light);
  Firebase.RTDB.setBool(&fbdo, "greenhouse/sensors/motion", motion);

  Serial.println("Data terkirim ke Firebase");
  delay(3000);
}
