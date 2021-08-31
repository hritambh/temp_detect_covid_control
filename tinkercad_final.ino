// C++ code
//
#include <Servo.h>
#include <LiquidCrystal.h>
Servo myservo;
//int led=6;
int pir1=6;
int pir2=7;
int count=0;
int temp = A0;
int val1=0;
int val2=0;
double temc;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
 pinMode(pir1,INPUT);
  pinMode(pir2,INPUT);
  //pinMode(led,OUTPUT);
  myservo.attach(9);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{     
  
  val1 = digitalRead(pir1);
  if((val1==HIGH)&&(val2==LOW))

  {                                            
 
    Serial.println("value of PIR 1--------" + String(val1));
    Serial.println("Count-----" + String(count));
    if (count < 3) {     
     temc=calctemp();
      if(checktemp(temc)){
        myservo.write(70);
        lcd.println("People less than limit.Body temp ok");
        lcd.setCursor(0,1);
        
        lcd.println("Access Granted");
        for (int positionCounter = 0; positionCounter < 23; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(250);
  }
        
        Serial.println("Access granted people less than 10");
        //digitalWrite(led, HIGH);
        
        start:
        val2 = digitalRead(pir2);
        if (val2 == HIGH) {                      
          Serial.println("Value of PIR 2-----" + String(val2));
          //digitalWrite(led, LOW);
          myservo.write(10);
                  count++;
          //lcd.setCursor(0,1);
          lcd.clear();
        //lcd.println("ACCESS GRANTED!!");
          delay(500);
          lcd.clear();
        
          Serial.println("Count-----" + String(count));
                delay(100);
            }                                         
      else {                                       
      goto start;
        }
      }
      else{
      Serial.println("Access denied get checked");
      lcd.println("BODY TEMP ABOVE NORMAL!!");
        for (int positionCounter = 0; positionCounter < 23; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(250);
  }
      //delay(1000);
          lcd.clear();
      lcd.println("ACCESS DENIED");
      delay(1000);
          lcd.clear(); 
      myservo.write(10);
      }
      
    }
                                                                                            
          else{    
            temc=calctemp();
            if(checktemp(temc)){
        Serial.println("Access Denied people more than 10");
            lcd.print("MAX LIMIT REACHED");
            for (int positionCounter = 0; positionCounter < 20; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(250);
  }
            //delay(1500);
          lcd.clear();
            }
            else{
            Serial.println("Access denied get checked");
      lcd.println("BODY TEMP ABOVE NORMAL!!");
        for (int positionCounter = 0; positionCounter < 23; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(250);
  }
              lcd.clear();
              
            }     
          
     }
    
    
  }
                                               
    
    
    val2 = digitalRead(pir2);     
    if((val1==LOW)&&(val2==HIGH)){                                            
    Serial.println("value of PIR 2--------" + String(val1));
    Serial.println("Count-----" + String(count));
    //digitalWrite(led, HIGH);
      myservo.write(70);
      start2:
      val1 = digitalRead(pir1);
      if (val1 == HIGH) {                       
        Serial.println("Value of PIR 1-----" + String(val1));
        //digitalWrite(led, LOW);
        myservo.write(10);
                count--;
        lcd.println("VISIT AGAIN");
        delay(500);
         lcd.clear();
        Serial.println("Count-----" + String(count));
              delay(100);
      }                                         
          else {                                       
    goto start2;
      }
      delay(2000);                           
    }                                              
    
    if((val1==LOW)&&(val2==LOW)){
    //digitalWrite(led,LOW);
    myservo.write(10);
    delay(2000);
       
  }

  delay(1000);
}

double calctemp()
{
  double analogReading=analogRead(temp);
   // converting that reading to voltage
  double temv= analogReading *0.0049;   //  5v/1024
   //converting from 10 mv per degree with 500 mV offset
   //to degrees ((voltage -
  double temc= (temv - 0.5) *100.0;
  Serial.println(" degree C " + String(temc));
  return temc;
}


bool checktemp(double temc){
 if (temc <= 37) return true;
 
 else return false;
   

}
