
#include <NTPClient.h>
#include <ESP8266WiFi.h> // provides ESP8266 specific Wi-Fi routines we are calling to connect to network
#include <WiFiUdp.h> //handles sending and receiving of UDP packages
#include <TimeLib.h>  
#include <SPI.h> // SPI for interfacing OLED with NodeMCU
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>              // include wire library (for I2C devices such as SSD1306 display)
#include <Adafruit_GFX.h>      // include Adafruit graphics library
#include <Adafruit_SSD1306.h>  // include Adafruit SSD1306 OLED display driver

 

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  13   //D1
#define OLED_CLK   14   //D0
#define OLED_DC    2
#define OLED_CS    15
#define OLED_RESET 16

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
int RX = 3;
int pin_state= 0;
unsigned long counter = 0;
unsigned long prev_counter = 0;
long DELAY = 0;
float freq = 0;

int i=0;
  int j=0;
  int x=0;
  int y=0;
  unsigned long previousMillis = 0; 

const char *ssid     = "sidd";
const char *password = "12345678901";


 
WiFiUDP ntpUDP;
 
// 'time.nist.gov' is used (default server) with +1 hour offset (3600 seconds) 60 seconds (60000 milliseconds) update interval
NTPClient timeClient(ntpUDP, "time.nist.gov", 19800, 60000);
 
void setup(void)
{
 
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever

Serial.begin(9600);
  pinMode(RX,INPUT);
  pinMode(13,OUTPUT);
 
 
  WiFi.begin(ssid, password);
  
 
  Serial.print("Connecting.");
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("connected");
  
 
  timeClient.begin();
 
}
 
char Time[] = "  :  :  ";
char Date[] = "  -  -20  ";
byte last_second, second_, minute_, hour_, wday, day_, month_, year_;
unsigned long currentMillis = millis();
   
void loop(){




  if(currentMillis - previousMillis >= 100)
  {
    previousMillis += 100;
  if (j==50){
i=0;
j=0;
x=0;
y=0;
}
j=j+1;
      
      
       Serial.println(DELAY);
       if(DELAY>=200 && DELAY<=390){
      i=i+1;
       }

Serial.println(j);

      if(i>=45){
        x=1;
  Serial.println("in range");

  

      }

      if(i>=30){
        
        y=1;
        
     if (x==0 && y==1 ){   
  Serial.println("in range22");
  
display.invertDisplay(true);
  display.clearDisplay();
  display.setFont();
display.setTextColor(1);
display.setTextSize(1);
display.setCursor(0,25);
display.println(" Device is in range 2 ");
display.display();
     }
      
  }
  }
  
  if(x==1 && y==1){
  display.invertDisplay(true);
  display.clearDisplay();
  display.setFont();
display.setTextColor(1);
display.setTextSize(1);
display.setCursor(0,25);
display.println(" Device is in range 1 ");
display.display();
  }

  
 if(digitalRead(RX) && pin_state== 0)
 {
  pin_state=1;
  prev_counter = micros();
 }

 if(!digitalRead(RX) && pin_state== 1)
 {
  pin_state=0;
  counter = micros();
  DELAY = counter - prev_counter;   
 }
 
  
  
 
  
 
  timeClient.update();
  unsigned long unix_epoch = timeClient.getEpochTime();   // get UNIX Epoch time
 
  second_ = second(unix_epoch);        // get seconds from the UNIX Epoch time
  if (last_second != second_)
  {
    minute_ = minute(unix_epoch);      // get minutes (0 - 59)
    hour_   = hour(unix_epoch);        // get hours   (0 - 23)
    wday    = weekday(unix_epoch);     // get minutes (1 - 7 with Sunday is day 1)
    day_    = day(unix_epoch);         // get month day (1 - 31, depends on month)
    month_  = month(unix_epoch);       // get month (1 - 12 with Jan is month 1)
    year_   = year(unix_epoch) - 2000; // get year with 4 digits - 2000 results 2 digits year (ex: 2018 --> 18)
 
    Time[7] = second_ % 10 + '0';
    Time[6] = second_ / 10 + '0';
    Time[4] = minute_ % 10 + '0';
    Time[3] = minute_ / 10 + '0';
    Time[1] = hour_   % 10 + '0';
    Time[0] = hour_   / 10 + '0';
    Date[9] = year_   % 10 + '0';
    Date[8] = year_   / 10 + '0';
    Date[4] = month_  % 10 + '0';
    Date[3] = month_  / 10 + '0';
    Date[1] = day_    % 10 + '0';
    Date[0] = day_    / 10 + '0';
 
    display_wday();
    draw_text(4,  29, Date, 2);        // display date (format: dd-mm-yyyy)
    draw_text(16, 50, Time, 2);        // display time (format: hh:mm:ss)
    display.display();
 
    last_second = second_;
 
  }
 
  delay(200);
 
}
 
void display_wday()
{
  switch(wday){
    case 1:  draw_text(40, 15, " SUNDAY  ", 1); break;
    case 2:  draw_text(40, 15, " MONDAY  ", 1); break;
    case 3:  draw_text(40, 15, " TUESDAY ", 1); break;
    case 4:  draw_text(40, 15, "WEDNESDAY", 1); break;
    case 5:  draw_text(40, 15, "THURSDAY ", 1); break;
    case 6:  draw_text(40, 15, " FRIDAY  ", 1); break;
    default: draw_text(40, 15, "SATURDAY ", 1);
  }
}
 
void draw_text(byte x_pos, byte y_pos, char *text, byte text_size)
{
  display.setCursor(x_pos, y_pos);
  display.setTextSize(text_size);
  display.print(text);
}
// End of code.
