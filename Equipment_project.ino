#include <Servo.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>        
#include  <Wire.h>

// LiquidCrystal_I2C lcd(0x27,  16, 2);

int temp_condition = 37;
int color_condition = 30;

// Servo motor declaration.
Servo myservo;
int pos = 0;

// water pump declaration.
#define pump_pin 10

// IR sensor declaration.
#define ir_pin 4
int ir;
int count;                 // num of flux.

// DHT (temp/humidity) declarathion.
#define DHTPIN 5
#define DHTTYPE DHT11  // DHT 11  (AM2302), AM2321
//type ox3F or 0x27
DHT dht(DHTPIN, DHT11);
//variables
int temp;
int humidity;

// Water sensor declaration 
#define POWER_PIN  13
#define SIGNAL_PIN A5
int value = 0; // variable to store the sensor value

// Color sensor
#define S2 7       
#define S3 6     
// Note: we put S0, S1 on 5v in bread board to get 100% output freq scaling
#define colorsensorOut 8  
int frequencyR = 0;
int frequencyG = 0;
int frequencyB = 0;

void setup()
{ 
  // Servo motor setup.
  myservo.attach(12); 
  // water pump setup.
  pinMode(pump_pin,OUTPUT);
  digitalWrite(pump_pin,LOW);

  // IR sensor set up.
  pinMode(ir_pin,INPUT);

  // DHT11 sensor setup. 
  dht.begin();

  // Water sensor setup 
  pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF

  //Color sensor
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(colorsensorOut, INPUT);

  // lcd.backlight();
  // lcd.setCursor(0,0);
  // lcd.print("Begin");
  Serial.begin(9600);
}



void loop()
{ 

  // DHT (temp/humidity) code
  temp = dht.readTemperature();
  humidity = dht.readHumidity();
  // Serial.print("Humidity: ");
  // Serial.print(humidity);
  // Serial.println("%");
  // Serial.print("Temperature: ");
  // Serial.print(temp);
  // Serial.println(" C");
  if(temp > temp_condition){
    Serial.println("Tempreature is high");
    // lcd.setCursor(0,0);
    // lcd.print("High ");
    // lcd.setCursor(6,0);
    // lcd.print("Tempreature");
  }

  // Water sensor code
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF

  // Serial.print("Sensor value: ");
  // Serial.println(value);

  if(value < 100){
    Serial.println("The supplies are running out");
  }

  // Colour sensor
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  frequencyR = pulseIn(colorsensorOut, LOW);
  // Serial.print("R= ");
  // Serial.print(frequencyR);
  // Serial.print("  ");
  

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  frequencyB = pulseIn(colorsensorOut, LOW);
  // Serial.print("B= ");
  // Serial.print(frequencyB);
  // Serial.print("  ");
 

   
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  frequencyG = pulseIn(colorsensorOut, LOW);
  // Serial.print("G= ");
  // Serial.print(frequencyG);
  // Serial.println("  ");
  
  if (!(frequencyR<frequencyB && frequencyR<=frequencyG && frequencyR<color_condition)) //if Red value is the lowest one and smaller thant 23 it's likely Red
  { Serial.println("Blood leakage");
    //Serial.println("error: Wrong sample");
    // lcd.setCursor(0,0);
    // lcd.print("Wrong ");
    // lcd.setCursor(7,0);
    // lcd.print("sample");
  }

  // Start of application.
  for (pos = 0; pos <= 30; pos += 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
  delay(500);
  ir = digitalRead(ir_pin);
  if(ir == 0){
      digitalWrite(pump_pin,HIGH);
      delay(1000);
      digitalWrite(pump_pin,LOW);
  }
  for (pos = 30; pos <= 60; pos += 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
  delay(500);
  ir = digitalRead(ir_pin);
  if(ir == 0){
      digitalWrite(pump_pin,HIGH);
      delay(1000);
      digitalWrite(pump_pin,LOW);
  }
  delay(500);
  for (pos = 60; pos <= 90; pos += 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
  delay(500);
  ir = digitalRead(ir_pin);
  if(ir == 0){
      digitalWrite(pump_pin,HIGH);
      delay(1000);
      digitalWrite(pump_pin,LOW);
  }
  delay(500);
  for (pos = 90; pos <= 120; pos += 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
  delay(500);
  ir = digitalRead(ir_pin);
  if(ir == 0){
      digitalWrite(pump_pin,HIGH);
      delay(1000);
      digitalWrite(pump_pin,LOW);
  }
  delay(500);
  for (pos = 120; pos <= 150; pos += 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
  delay(500);
  ir = digitalRead(ir_pin);
  if(ir == 0){
      digitalWrite(pump_pin,HIGH);
      delay(1000);
      digitalWrite(pump_pin,LOW);
  }
  delay(500);
  for (pos = 150; pos <= 180; pos += 1) { 
    myservo.write(pos);              
    delay(15);                       
    
  }
  delay(500);
  ir = digitalRead(ir_pin);
  if(ir == 0){
      digitalWrite(pump_pin,HIGH);
      delay(1000);
      digitalWrite(pump_pin,LOW);
  }
  delay(500);


  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
}