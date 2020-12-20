int RX = 3;
int pin_state= 0;
unsigned long counter = 0;
unsigned long prev_counter = 0;
long DELAY = 0;
float freq = 0;

int i=0;
  int j=0;



unsigned long previousMillis = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(RX,INPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  


unsigned long currentMillis = millis();  
  if(currentMillis - previousMillis >= 100)
  {
    previousMillis += 100;
  if (j==50){
i=0;
j=0;
}
j=j+1;
      
      
       Serial.println(DELAY);
       if(DELAY>=250 && DELAY<=390){
      i=i+1;
       }

Serial.println(j);

      if(i>=45){
  Serial.println("in range");
      }

      if(i>=30){
  Serial.println("in range22");
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
 
  
  
 
  
 
}
