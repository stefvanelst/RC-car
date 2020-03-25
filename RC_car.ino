int enablePin = 19;
int in1Pin = 12;
int in2Pin = 15;
int enable2Pin = 18;
int in3Pin = 4;
int in4Pin = 14;
int leds = 27;
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "your auth";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "your ssid";
char pass[] = "your pass";

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h> 
int BH1750address = 0x23; //i2c address
 
byte buff[2];

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // put your setup code here, to run once:
pinMode(in1Pin, OUTPUT);
pinMode(in2Pin, OUTPUT);
pinMode(enablePin, OUTPUT);
pinMode(in3Pin, OUTPUT);
pinMode(in4Pin, OUTPUT);
pinMode(enable2Pin, OUTPUT);
pinMode(leds, OUTPUT);

pinMode(in1Pin, HIGH);
pinMode(in2Pin, HIGH);
pinMode(enablePin, HIGH);
pinMode(in3Pin, HIGH);
pinMode(in4Pin, HIGH);
pinMode(enable2Pin, HIGH);

  Wire.begin();
  Serial.begin(115200);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
  }
  delay(2000);
  display.clearDisplay();

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");  

  Blynk.begin(auth, ssid, pass);
  Blynk.config(auth, "blynk-cloud.com", 8442);
  Blynk.connectWiFi(ssid, pass);

}

void loop() {
Blynk.run();
 int i;
  uint16_t val=0;
  BH1750_Init(BH1750address);
  delay(200);
 
  if(2==BH1750_Read(BH1750address))
  {
    val=((buff[0]<<8)|buff[1])/1.2;
    Serial.print(val,DEC);
    Serial.println("lux");
  }
  delay(150);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print(val,DEC);
  display.println(" lux");
  display.display(); 
  Blynk.virtualWrite(V1, val," lux"); //send lux value to virtual pin 1; add gauge to app & assign to virtual pin 1

  if(val < 10)
    {
      digitalWrite(leds,HIGH);
    } else {
      digitalWrite(leds,LOW);
    }
}
 
int BH1750_Read(int address) //
{
  int i=0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while(Wire.available()) //
  {
    buff[i] = Wire.read();  // receive one byte
    i++;
  }
  Wire.endTransmission();
  return i;
}
 
void BH1750_Init(int address)
{
  Wire.beginTransmission(address);
  Wire.write(0x10);//1lx reolution 120ms
  Wire.endTransmission();

}
