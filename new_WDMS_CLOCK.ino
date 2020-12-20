/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using SPI to communicate
 4 or 5 pins are required to interface.

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/
#include <NTPClient.h>
#include <ESP8266WiFi.h> // provides ESP8266 specific Wi-Fi routines we are calling to connect to network
#include <WiFiUdp.h> //handles sending and receiving of UDP packages
#include <TimeLib.h>  
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//#include <Fonts/FreeSans9pt7b.h>
//#include <Fonts/FreeSans12pt7b.h>
//#include <Fonts/FreeMonoOblique18pt7b.h>
//#include <Fonts/FreeSerif9pt7b.h>

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  13   //D1
#define OLED_CLK   14   //D0
#define OLED_DC    2
#define OLED_CS    15
#define OLED_RESET 16
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
  
  int RX = 12;
int pin_state= 0;
unsigned long counter = 0;
unsigned long prev_counter = 0;
long DELAY = 0;
float freq = 0;

int i=0;
  int j=0;
  int x=0;
  int y=0;
  int a=0;
  int b=0;
  int c=0;



unsigned long previousMillis = 0; 


const char *ssid     = "sidd";
const char *password = "12345678901";


 
WiFiUDP ntpUDP;
 
// 'time.nist.gov' is used (default server) with +1 hour offset (3600 seconds) 60 seconds (60000 milliseconds) update interval
NTPClient timeClient(ntpUDP, "time.nist.gov", 19800, 60000);
 


void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever

//Serial.begin(9600);
//  pinMode(RX,INPUT);
//  pinMode(13,OUTPUT);


    
  }
pinMode(RX,INPUT);
  pinMode(13,OUTPUT);


  display.clearDisplay();

//  display.setFont(&FreeSans12pt7b);
  display.setTextColor(1);
  display.setCursor(0,22);
   display.println("  i mpulse\n   projects");
  
  display.invertDisplay(true);
  display.display();

delay(2000);
 display.clearDisplay();

 
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

 
void loop() {


unsigned long currentMillis = millis();  
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
       if(DELAY>=100 && DELAY<=350){
      i=i+1;
       }

Serial.println(j);

      if(i>=45){
        x=1;
  Serial.println("in range");

  

      }

      if(i>=30){
        
        y=1;
  }
  
  if (x==0 && y==1 && j>=49){   
  Serial.println("in range22");
  

 a=1;
 b=0;
 c=0;
     }
  if(x==1 && y==1 ){

a=0;
b=1;
c=0;
  
  }
  if(y==0 && j>=45){

a=0;
b=0;
c=1;

  }
  
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
 display.clearDisplay();
    display_wday();
    draw_text(3,  3, Date, 1);        // display date (format: dd-mm-yyyy)
    draw_text(16, 15, Time, 2);        // display time (format: hh:mm:ss)

if (a==1){   
 
  display.setFont();
display.setTextColor(1);
display.setTextSize(1);
display.setCursor(0,35);
display.println(" Device is in range 2 ");
display.display();
     }
     if (b==1){   
  
  display.setFont();
display.setTextColor(1);
display.setTextSize(1);
display.setCursor(0,35);
display.println(" Device is in range 1 ");
display.display();
     }
     if (c==1){   
  
  display.setFont();
display.setTextColor(1);
display.setTextSize(1);
display.setCursor(0,35);
display.println(" ALERT! out of range ");
display.display();
     }


    
    display.display();
 
    last_second = second_;
 
  }
 
  
// display.clearDisplay();
 
}
 
void display_wday()
{
  switch(wday){
    case 1:  draw_text(80, 3, " SUNDAY  ", 1); break;
    case 2:  draw_text(80, 3, " MONDAY  ", 1); break;
    case 3:  draw_text(80, 3, " TUESDAY ", 1); break;
    case 4:  draw_text(80, 3, "WEDNESDAY", 1); break;
    case 5:  draw_text(80, 3, "THURSDAY ", 1); break;
    case 6:  draw_text(80, 3, " FRIDAY  ", 1); break;
    default: draw_text(80, 3, "SATURDAY ", 1);
  }
}
 
void draw_text(byte x_pos, byte y_pos, char *text, byte text_size)
{
  display.setCursor(x_pos, y_pos);
  display.setTextSize(text_size);
  display.print(text);
  
 
  
 
}
