//Hermes Suen, Brian Barrows, Alvaro Mendez Michael Birosak
//Robotics Final Project


#include <Servo.h> 
#include<SoftwareSerial.h>

//Define the pins that will read data from Open MV
SoftwareSerial mySerial(0,1);

//Define the 5 servos required for the project. 2 for the conveyer belt, one to push the cards forward, one
//to flip over upside down cards, and one to rotate the card shuffler at the end. 
Servo conveyer1;
Servo conveyer2;
Servo cardPusher;
Servo Flipper;
Servo ShufflerRotate;

//angle that the flipper will be set at to stop cards
int restPos = 31;
int ShufflerPos = 0;

void setup() 
{ 
  //initialize all servos
  conveyer1.attach(9);
  conveyer2.attach(10);
  cardPusher.attach(11);
  Flipper.attach(3);
  ShufflerRotate.attach(6);

  //Start the conveyer belt system
  conveyer1.write(84);
  conveyer2.write(98);
  Serial.begin(9600);
  mySerial.begin(9600);

} 

void loop() {
  conveyer1.write(84);
  conveyer2.write(98);
  Flipper.write(restPos);

  //Read data from the Open MV to see if card
  //is face up or facedown
  int data = mySerial.read();
  Serial.println(data);

  //If no data, push a card forward
  if(data ==-1){
    Flipper.write(restPos);
    pushCard();

  //if the card is ok, let it through
  }else if (data == 0){
    Flipper.write(0);
    delay(1500);
    Flipper.write(restPos+8);
  }
  
  //if the card is upside down, flip it
  else if(data == 1){
    Flipper.write(130);
    delay(1000);
    Flipper.write(restPos-4);
  }

  delay(1000);

  //randomly rotate the card shuffler at the end(so that
  //there will be even number of cards on each side
  int randInt = random(0,100);
  Serial.println(randInt);
  if(randInt >50){
    if(ShufflerPos == 0){
      ShufflerRotate.write(180);
      ShufflerPos = 180;
    }else{
      ShufflerRotate.write(7);
      ShufflerPos = 0;
    }
  }
  
}

//function to push a card forward
void pushCard()
{
  cardPusher.write(65);  
  delay(380);
  cardPusher.write(90);
  delay(1000);
  
}
  
  
