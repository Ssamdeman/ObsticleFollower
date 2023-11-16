
//Tested November 13, 2023
//Developed by:
      //Gabriella Lonsdale (Project Engineering Lead)
      //Narendra Nath Chalasani (Design Lead)
      //Sultan Samidinov (Software Engineering Lead)
      //Gianna Del Nero Marcondes(Product Development Lead)
      //Mohammed Alsinani (Testing Lead)


#include <LiquidCrystal_I2C.h> //  enables us to see the message in the LCD library.

LiquidCrystal_I2C lcd(0x27, 16, 2); // setting up on how LCD set up and configured it's screen size.



// global varibales
char array1[] = "Ready to Ride   "; // array of message that shows on the LCD
char array2[] = "STOPPED         "; //message that shows on the LCD
char array3[] = "FOLLOWING       ";//message that shows on the LCD
char array4[] = "FORWARD         ";//message that shows on the LCD
char array5[] = "OUT OF RANGE    ";//message that shows on the LCD
char array6[] = "ROTATING        ";//message that shows on the LCD


//char array6[] = "HELLO WORLD     ";////testing the LCD

//seting up the ultrasonic sensor and configures the pin
int echoPin = 8; //  pin D8 to pin ultrasonic sensor
int trigPin = 7; //  pin D7 to pin ultrasonic sensor

//setting up the motor
int in1 = 4; // variable names for the L298N Motor Drive Controller Board Module Dual H Bridge DC
int in2 = 5; // variable names for the L298N Motor Drive Controller Board Module Dual H Bridge DC
int in3 = 9; // variable names for the L298N Motor Drive Controller Board Module Dual H Bridge DC
int in4 = 10; // variable names for the L298N Motor Drive Controller Board Module Dual H Bridge DC


int LCDprev = 99; // update the LCD message keeps track the previous
int LCDcurr = 100; // update the LCD message keeps track the current

int ledpin = 13; //specify the LED pin to pin 13


long duration; //   sound wave travel wich will be converted into distance
int distance; // distance measureming from the wave travel.



//Functions

void following(int distance) {

  if (distance <= 30) { //if object 30cm away from the robot, it will move forward and follow the obsticle, assuming the object is moving

    LCDcurr = 1; // temporary set the LCDcurr message

    ///Moves  forward if robot sees obsticle  in 30 cm
    //It lockes the 30cm obsticle 30
    //spind clock-wise motor  A
    digitalWrite(in1, HIGH);  //Using the monitor. Spin the monitor.
    digitalWrite(in2, LOW); //Using the monitor. Spin the monitor.
    //spind clock-wise motor B
    digitalWrite(in3, HIGH); //Using the monitor. Spin the monitor.
    digitalWrite(in4, LOW); //Using the monitor. Spin the monitor.


    //stop the robot if it 10 cm close tothe object.
    if ((distance <= 5)) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);

      //motor B Stop
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      
    }


    if (LCDprev != LCDcurr) { // check if prev message not equal to current then
      lcd.setCursor(0, 1); // set the LCD where to print.
      lcd.print(array3); //Print Following
      delay(10); //  //wai›t until next one code execute.
    }




  } else if (distance >= 30) { //if object less then 30cm  from the robot LCD will stopp

    LCDcurr = 2; //temporary set the LCDcurr message. So it's difference from the previus one

    //Move motor stops
    //motor A
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    //motor B Stop
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    if (LCDprev != LCDcurr) { //check the previous message, if they are not the same, print new message..
      lcd.setCursor(0, 1); // set the LCD where to print.
      lcd.print(array2); //print on the screen  STOPPED
      delay(7000); //wait until next one code execute.
    }

  }



}


//Functions
void rotate(int distance) {

  if (distance >= 30) {

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    //motor B Stop
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    lcd.setCursor(0, 1); // set the LCD where to print.
    lcd.print(array6); //print on the screen  Rotating
    delay(10); //wait until next one code execute.

    following(distance);


  }
}








//Action code
void setup() {

  lcd.init(); // init  LCD
  lcd.backlight(); // turn on LCD

  pinMode (trigPin, OUTPUT) ; // ultrasonic sensor digital pin mode for trig
  pinMode (echoPin, INPUT); // ultrasonic sensor digital pin mode for echo



  pinMode (in1, OUTPUT); // all L298N digital pins are outputs aka Motor
  pinMode (in2, OUTPUT); // all L298N digital pins are outputs aka Motor
  pinMode (in3, OUTPUT); // all L298N digital pins are outputs aka Motor
  pinMode (in4, OUTPUT); // all L298N digital pins are outputs aka Motor
  pinMode (ledpin, OUTPUT) ; // configure LCD pin as an output



  Serial.begin (9600) ; //Serial Monitor, make sure to use one of the baud rates listed.
  //Function of Serial.begin https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/
  //It Sets the data rate in bits per second (baud) for serial data transmission

  lcd.setCursor(0, 0); // set up the LDC to start at top left to print message.

  //lcd.print (array1); //prints the first line "Robot State:

}


//Action Start here.

void loop() {

//this is not working.
  ///Moves  forward if robot sees obsticle  in 30 cm
    //It lockes the 30cm obsticle 30
    //spind clock-wise motor  A
    digitalWrite(in1, HIGH);  //Using the monitor. Spin the monitor.
    digitalWrite(in2, LOW); //Using the monitor. Spin the monitor.
    //spind clock-wise motor B
    digitalWrite(in3, HIGH); //Using the monitor. Spin the monitor.
    digitalWrite(in4, LOW); //Using the monitor. Spin the monitor.



  LCDprev = LCDcurr; // keep track the LCD message.


//Ultrosonic is working.
  // Setting up the trigger Pin condition. Distance
  digitalWrite (trigPin, LOW);// Set trigger pin low
  delayMicroseconds (3); //waits for hardwares to respond
  digitalWrite (trigPin, HIGH); //Set trigger pin high
  delayMicroseconds (20) ; //continues high trigger pin state for 20 microseconds
  digitalWrite (trigPin, LOW); //after 20 microseconds trigger pin set low
  
  duration = pulseIn (echoPin, HIGH); //Reading the echo data as it receives the pulse and stores duration in duration
  distance = duration * 0.034 / 2; // Conversion the time of flight to distance to object
  


  // Displays the distance on the LCD
  Serial.print ("Distance: "); //printing on LCD
  Serial.print (distance);//printing on LCD
  Serial.println(" cm");//printing on LCD with new line

  //lcd.print(array6);//test code

  following(distance);

  rotate(distance);

  if(distance = 0 || distance > 350){

    digitalWrite(in1, HIGH);  //Using the monitor. Spin the monitor.
    digitalWrite(in2, LOW); //Using the monitor. Spin the monitor.
    //spind clock-wise motor B
    digitalWrite(in3, HIGH); //Using the monitor. Spin the monitor.
    digitalWrite(in4, LOW); //Using the monitor. Spin the monitor.

    }


    

  

}
