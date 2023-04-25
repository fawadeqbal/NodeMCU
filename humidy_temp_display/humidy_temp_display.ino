#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <BlynkSimpleEsp8266.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 14     // Digital pin connected to the DHT sensor

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

char auth[] = "FG4cbQI945Lp0VoR4rTtb11Dtq8-R2Gm"; //Enter the Auth code which was send by Blink
char ssid[] = "*-*";  //Enter your WIFI Name
char pass[] = "cloudy777";  //Enter your WIFI Password

BlynkTimer timer;

void sendSensor() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}

void setup() {
  Serial.begin(115200);
  
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, sendSensor);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  testscrolltext();
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  // clear display
  display.clearDisplay();
  int16_t i=0;
  display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
  //display.display(); // Update screen with each newly-drawn rectangle
  // display temperature
  display.setTextSize(1);
  display.setCursor(6,2);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(6,10);
  display.print(t);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  
  // display humidity
  display.setTextSize(1);
  display.setCursor(6, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(6, 45);
  display.print(h);
  display.print(" %"); 
  
  display.display(); 
  Blynk.run();
  timer.run();
   
  }

void testscrolltext(void) {
  display.clearDisplay();
  int16_t i=0;
  display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
  display.display(); // Update screen with each newly-drawn rectangle
  display.setTextSize(1.5); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  //display.setCursor(50,27);7
  display.setCursor(20,27);  
  display.println(F("CoolElektrodude"));
  display.display();      // Show initial text
  display.clearDisplay();
  delay(100);
}
