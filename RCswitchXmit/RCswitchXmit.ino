/*
/  Example for Transmitting with RC-Switch
/  
/  http://code.google.com/p/rc-switch/
/  
*/

#include <RCSwitch.h>

#define LEDPin 13  // used to flash LED during transmit

#define trigPin 8  // sonar trigger
#define echoPin 9  // sonar echo   

#define xmitPin 10 // Transmitter is connected to Arduino Pin #10  

#define NAME "joe4"  // name of ardiuno

// create RC-Switch instance
RCSwitch mySwitch = RCSwitch();

// random used for avoid transmit collision
int randomDelay = 0;

/*
/ Setup Arduino
*/
void setup() {

  // this is for debug out 
  Serial.begin(9600);
  
  // enable the RC-Switch library transmit
  mySwitch.setRepeatTransmit(5);
  mySwitch.enableTransmit(xmitPin);
  
  // randomly pick a delay between transmits
  randomDelay = random(450, 650);
  Serial.print("randomDelay=");
  Serial.println(randomDelay);  
}

/*
/ After setup completes, this loop will run forever
*/
void loop() {
  
  int duration, distance;

  // put the sonar trigger pin high for 1 second
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  
  // set trigger low
  digitalWrite(trigPin, LOW);
  
  // read the echo
  duration = pulseIn(echoPin, HIGH);
  
  // the distance is 1/2 the time divided by speed of light
  //  distance = (duration/2) / 29.1;
  
  // TODO - remove this line, uncomment above line
  // DEBUG, RANDOM DISTANCE
  distance = random(1, 300);
  Serial.print("distance=");
  Serial.println(distance);

  // beyond 200cm or less than 0 is pretty much noise
  if (distance >= 200 || distance <= 0) {
    Serial.println("out of range");
  
  } else {
    
    // build JSON string to tranmit
    //
    // A good string will look like:
    //
    //     {"id":"joe4", "dist":97}
    //
    char msg[50];
    msg[0]='\0';
    sprintf(msg, "{\"id\":\"%s\", \"dist\":%d}", NAME, distance);
    Serial.println(msg);

    // the RC-Switch library wants a String in binary
    // meaning "hello" is "0110100001100101011011000110110001101111"

    // Flash LED to show transmitting
    digitalWrite(LEDPin, true); 
    
    int i = 0;
    for (char *c = msg ; *c ; c++) {
       // send char with RC-Switch
       mySwitch.send((int)*c, 8);
    }
    mySwitch.send(255, 8);
    
    // turn off light
    digitalWrite(LEDPin, false);

    // random delay before next send
    delay(randomDelay);
  }
}
