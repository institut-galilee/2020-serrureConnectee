#include <Servo.h> //librairie du servo moteur


#define SS_PIN 10
#define RST_PIN 9

//pins
int esp=A1;
int servo=A0;
int ledrouge=A2;
int ledverte=A3;

int button=A4;
int hallsensor= A5;
//servo
Servo myservo;

void setup() {
  Serial.begin(9600);
  delay(200);
  pinMode(esp, INPUT);
  pinMode(button, INPUT);
  pinMode(ledrouge, OUTPUT);
  pinMode(ledverte, OUTPUT);
  pinMode(hallsensor, INPUT);


}

void loop() {

  //ouverture/fermeture si un signal est détecté par l'esp8266
  if (analogRead(esp)>600){
      esp_servo();
      delay(2000); 
  }
  //ouverture/fermeture si un signal est détecté par le bouton poussoir
  if (analogRead(button)>900){
      boutton();
      delay(2000);
  }
}

/* ----Fonction pour activer le servomoteur avec l'ESP----  avec hall sensor */
void esp_servo(){
  myservo.attach(servo);
  //fermeture
  if(myservo.read()>=0 && myservo.read()<90){
      //hallsensor pour déterminer si la porte est fermé.
      int detected = digitalRead(hallsensor);
      if(detected == high){
        analogWrite(ledrouge, 700);
        myservo.write(180); 
        delay(2000); 
        analogWrite(ledrouge, 0);
      }else{
        
        // à changer avec le truc blynk      
        Serial.println("Attention! La porte est entre ouverte! elle ne peut donc pas se fermer");
        delay(2000);
      }
      
      
  }
  //ouverture
  else if (myservo.read()>90 && myservo.read()<=185){
      int detected = digitalRead(hallsensor);
      if(detected == high){
        analogWrite(ledverte, 700);
        myservo.write(0);
        delay(2000); 
        analogWrite(ledverte, 0);
      }else{
        Serial.println("Attention ! la porte est entre ouverte, elle ne peut donc pas se fermé correctement");
      }
  myservo.detach();  
}

void boutton(){
    myservo.attach(servo);
    //fermeture
    if(myservo.read()>=0 && myservo.read()<90){
        int detected = digitalRead(hallsensor);
        if(detected == high){
          analogWrite(ledrouge, 700);
          myservo.write(180); 
          delay(2000); 
          analogWrite(ledrouge, 0);
        }else{
          Serial.println("Attention! La porte est ouverte! elle ne peut donc pas se fermer");
        }
    //ouverture
    }else if (myservo.read()>90 && myservo.read()<=185){
        if(detected == high){
          analogWrite(ledverte, 700);
          myservo.write(0);
          delay(2000); 
          analogWrite(ledverte, 0);
        }else{
          Serial.printfln("Attention! la porte est entre ouverte, 
        }
    }
  myservo.detach();
  }
