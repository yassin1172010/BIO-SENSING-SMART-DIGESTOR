#define BLYNK_template_ID "TMPL21nht7obf" 
#define BLYK_TEMPLATE_NAME "bio sensing smart digestor"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOCKEN"
#include <wifi.h>
#include <BlynkSimpleESP32.h>
char ssid[] ="darwish" ;
char pass[] ="010910694421999" ; 

BlynkTimer timer;


#include <LiquidCrystal.h>
#include <DHT.h>
// direct connection pins of lcd 
const int 
rs = 22;
en = 23;
d4 = 5 ;
d5 = 18 ;
d6 = 19;
d7 = 21;
liquidCrystal lcd(rs,en,d4,d5,d6,d7);

// pins of the DHT SENSOR
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

// PINS OF THE ULTRASONIC SENSOR
const int trigpin = 12 ;
const int echopin = 13 ;

// PINS OF THE LDR SENSOR
const int ldrpin = 34 ;
// pins of the rgb led 
const int greenpin = 25 ;
const int yellowpin = 26;
const int redpin = 27;

// variables of the beaker 500 ml
const float hightbeforedissolving = 9.0 ; // distance in cm before dissolving 
const float hightafterdissolving = 12.0 ;  // distance in cm after dissolving 
const int lightlimit = 2500 ; //limit of the light to avoid danger light 

void setup(){
  // serial monitor
  Serial.begin(115200);
  // turn the lcd and the dht on 
  lcd.begin(16,2);
  dht.begin();

  // set pins of the ultrasonic
  pinMode (trigpin,OUTPUT);
  pinMode (echopin,INPUT);
  
  // set pins of the rgb led 
  pinMode ( greenpin,OUTPUT);
  pinMode (yellowpin,OUTPUT);
  pinMode (redpin,OUTPUT);

  // display initial titles in the begining when power the system
  lcd .setcursor(0,0);
  lcd. print("BIO SMART ");
  lcd.setcursor(0,1);
  lcd.print("digestor util..")
  delay(2000);
  lcd. clear();

}
void loop(){
//read the temperature to correct the speed of the sound by the equation V=331.4 +(0.6*temperature)
float temperature = dht.readTemperature();

if (insan(currenttemperature)){
  temperature = 25.0 ;
}

//calculating the speed of the sound according to the current temperature
float soundspeed = (331.4+(0.6*temperature)) / 10000.0 ; \\ to convert it into cm\microsecond to be fit to the ultrasonic sensor

// set of the ultrasonic sensor 
digitalWrite(trigpin,LOW);
delayMicroseconds(2);
digitalWrite(trigpin,HIGH);
delaymicroseconds(10);
digitalWrite(trigpin,LOW);

long duration = pulseIn(echoPin,HIGH);
// calculate the distance with the cintemeter
float distance = (duration * speedofsound cm ) / 2.0 ;
// calculation of the dissolution rate 
float dissolutionrate = ((distance-fulldistance)/(emptydistance-fulldistance)) * 100 ;
// define the range of the dissolution rate between zero to 100 percent
if (dissolutionrate < 0) dissolutionrate = 0 ;
if dissolution rate > 100) dissolutionrate = 100 ;

int ldrvalue = analogread(ldrpin) ;
bool lightunsafe (ldrvalue > lightThreshold) ; //if the ligth was highier than the safe then it is true 

//according to the reading will control the RGB pins 
if (lightunsafe) {
// danger state red light and turn off the others 
digitalwrite(redpin,HIGH) ;
digitalwrite(yellowpin,LOW) ;
digitalwrite(greenpin,LOW);
}
else if (dissolutionrate >= 99.0) {
  //light up the green light 
  digitalwrite(greenpin,HIGH) ;
  digitalwrite(redpin,LOW) ;
  digitalwrite(yellowpin,LOW) ;
}
else {
  // process and safe light up the yellow color 
  digitalwrite(yellowpin,HIGH);
  digitalwrite(redpin,LOW);
  digitalwrite(greenpin,HIGH);
  }
// display the data(results) on the lcd
lcd.clear();
//first raw is for the dissolution rate
lcd.setcursor(0,0) ;
lcd.print("dissolve: ") ;
lcd.print((int)dissolutionrate) ;
lcd.print("%") ;

// second raw is for the condition of the light 
lcd.setcursor (0,1) ;
if (islightunsafe) {
  lcd.print("light: unsafe!") ;
  }
  else {
    lcd.print ("light:unsafe") ;
}
serial.print ("Temp: ") ; serial.print(temperature);
serial.print ("C | Dist: ") ; serial.print(distance) ;
serial.print("cm | Dissolve ") serial.print(dissolutionrate) ;
serial.print("% | LDR: ") ; serial.println(ldrvalue) ;

//simple delay to update the readings half a minute
delay(500) ;

}

void sendData To Blynk () {
Blync.virtualwrite (v0,65) ; // dissolution Rate % 
Blync.virtualwrite (v1,8.7) ; // Distance cm 
Blync.vittualwrite (v2,1450) ;// Light Level 
Blync.virtualwrite (v3,"safe") ; //status
Blync.virtualwrite (v4,255) ;// Led On 
Blync.virtualwrite (v5,27) ;// Temperature °C
serial.println ( "data sent to blynk successfully!") ;
}

void setup (){
  serial.begin(115200) ;
  Blynk.begin(BLYNK_AUTH-TOKEN,ssid,pass) ;
  timer.setinterval(2000L,sendDatatoBlynk) ;
}
void loop (){
Blynk.run();
timer.run();
}




