// Connect Vcc and Ground, SDA to A4, SCL to A5 on Arduino
#include <Wire.h>  
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
#include <AddicoreRFID.h>
#include <SPI.h>
#define  uchar unsigned char
#define uint  unsigned int
uchar serNumA[5];
uchar fifobytes;
uchar fifoValue;
AddicoreRFID myRFID; 
const int chipSelectPin = 100;
const int NRSTPD = 9; // RST Pin
#define MAX_LEN 30
int a,b,d,c=0;
int ledPin = 13;
int inPin = A0;   
int val = 0;     



void setup()  
{
   pinMode(ledPin, OUTPUT);  // declare LED as output
  pinMode(inPin, INPUT);    // declare pushbutton as input
  Serial.begin(9600);  
   SPI.begin();
  pinMode(chipSelectPin,OUTPUT);               
    digitalWrite(chipSelectPin, LOW);         
  pinMode(NRSTPD,OUTPUT);                    
    digitalWrite(NRSTPD, HIGH);
  myRFID.AddicoreRFID_Init();  
  lcd.begin(16,2);         
int a,b,d,c=0;
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(500);
    lcd.setCursor(3,0);
    lcd.print ("welcome");
    lcd.setCursor(2,1);
    lcd.print ("add products");
    lcd.noBacklight();
    delay(500);
    lcd.backlight();
  }
 delay (500);
 lcd.clear ();
 lcd.setCursor(2,0);
 lcd.print ("Scan Card");

}
void loop()   
{
    uchar i, tmp, checksum1;
  uchar status;
        uchar str[MAX_LEN];
        uchar RC_size;
        uchar blockAddr;  
        String mynum = "";
        str[1] = 0x4400;
  //Find tags, return tag type
  status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str); 
  if (status == MI_OK)
  {
            Serial.println("RFID tag detected");
          Serial.print(str[0],BIN);
            Serial.print(" , ");
          Serial.print(str[1],BIN);
            Serial.println(" ");
  }

  
  status = myRFID.AddicoreRFID_Anticoll(str);
  if (status == MI_OK)
  {
            checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];
            Serial.println("The tag's number is  : ");
          //Serial.print(2);
          Serial.print(str[0]);
            Serial.print(" , ");
          Serial.print(str[1],BIN);
            Serial.print(" , ");
          Serial.print(str[2],BIN);
            Serial.print(" , ");
          Serial.print(str[3],BIN);
            Serial.print(" , ");
          Serial.print(str[4],BIN);
            Serial.print(" , ");
            Serial.println(checksum1,BIN);
            
          
            // Should really check all pairs, but for now we'll just use the first
            if(str[0] ==203
)                      
            {
                lcd.clear ();
                a=10;
                lcd.setCursor(0,0);
                lcd.print("tea");
                delay (500);
                lcd.setCursor(0,1);
                lcd.print ("10"); 
               
            }  
            if(str[0] ==75
) {            
                lcd.clear ();
                
                lcd.setCursor(0,0);
                lcd.print("sugger");
                delay (500);
                lcd.setCursor(0,1);
                lcd.print ("20");
                b=20;   
            }

            if(str[0] ==27

) {             
                lcd.clear ();
                
                lcd.setCursor(0,0);
                lcd.print("milk");
                delay (500);
                lcd.setCursor(0,1);
                lcd.print ("50"); 
                c=50;     
            }
            d=a+b+c;
//            
            
            
            Serial.println();
            delay(1000);
         
  }
  
    
  

   val = digitalRead(inPin);  
  if (val == HIGH) {         
    lcd.print ("total=");
            lcd.print (d);
//            lcd.print('\n');
  } 
  else {
   lcd.print("            ");
       
     
  }
  
}
