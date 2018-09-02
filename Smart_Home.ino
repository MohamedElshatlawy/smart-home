#include <Keypad.h>
#include <Servo.h>

int led =2;
int pir = 12;               
int pirState = LOW;             //  start assuming no motion detected
int val = 0;  
int Mode;


int vale;
int tempPin = A0;


#define fan  11                        
#define buzzer  13

Servo servo_Motor; 
int position = 0;

char* password = "123";
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = { 8, 7, 6, 9 };
byte colPins[COLS] = { 5, 4, 3 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup()
{
pinMode(led,OUTPUT);   
pinMode(pir, INPUT);
pinMode(fan, OUTPUT);
pinMode(buzzer, OUTPUT);
servo_Motor.attach(10);
setLocked(true);
Serial.begin(9600);
}



void loop(){
  // *********************************KEYPAD PASSWORD*******************************
  
char key = keypad.getKey();
if (key == '*' || key == '#')
{
position = 0;
setLocked(true);
Serial.println('#');

}
if (key == password[position])
{
position ++;
}
if (position == 3)
{
  Serial.println("123");
  
setLocked(false);
}


//**********************END OF KEYPAD PASSWORD**************************

 //****************************************
if (Serial.available() > 0){

int x=Serial.parseInt();

if(x ==1){ 
   Mode=1; 
  Serial.println(" PIR SECUIRTY MODE Activated "); }

if(x ==2){ 
   Mode=2; 
  Serial.println(" PIR SECUIRTY MODE Deactivated "); }

if(x ==3){ 
   Mode=3; 
  Serial.println(" Fan Activated "); }  
  
if(x ==4){ 
   Mode=4; 
  Serial.println(" Fan Deactivated "); }  


if(x ==5){ 
   Mode=5; 
  Serial.println(" Temp Sensor Readings "); }  
  
if(x ==6){ 
   Mode=6; 
  Serial.println(" LED Activated "); } 
  
if(x ==7){ 
   Mode=7; 
  Serial.println(" LED Deactivated "); } 

}
//*****************************End of PIR sensor **************************
//***************PIR SENSOR Mode ************************
if (Mode == 1){
  val = digitalRead(pir);  
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(buzzer, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      //  only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(buzzer, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // only want to print on the output change, not state
      pirState = LOW;
    }}}
 //****************************************

//***************************************
if (Mode == 2){  
  digitalWrite(buzzer,LOW);
}
 //****************************************
 //***************************************
if (Mode == 3){  
  digitalWrite(fan,HIGH);
}
 //****************************************
 //***************************************
if (Mode == 4){  
  digitalWrite(fan,LOW);
}
 //****************************************

  //***************************************
if (Mode == 5){  
  vale = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
float cel = mv/10;
float farh = (cel*9)/5 + 32;

Serial.print("TEMPRATURE = ");
Serial.print(cel);
Serial.print("*C");
Serial.println();
delay(1000);
}
 //****************************************
  //***************************************
if (Mode == 6){  
  digitalWrite(led,HIGH);
}
 //****************************************
   //***************************************
if (Mode == 7){  
  digitalWrite(led,LOW);
}
}void setLocked(int locked)
{
if (locked)
{

servo_Motor.write(120);
delay(15);
}
else
{
servo_Motor.write(20);
delay(15);
}
}
