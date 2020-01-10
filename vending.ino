#include <Wire.h> 

#include <LiquidCrystal_I2C.h>



LiquidCrystal_I2C lcd(0x3F,16,2); 



// Constants

const int coinpin = 2;

const int ledpin = 8;



// Variables

volatile int pulse = 0;

volatile unsigned long timelastPulse = 0;



boolean bInserted = false;

int credits = 0;

int  price  = 20;



// Setup

void setup() {



    lcd.init();                      // initialize the lcd 



   pinMode( ledpin , OUTPUT);

   digitalWrite( ledpin, LOW);

  

  // Print a message to the LCD.

  lcd.backlight();

   

  lcd.clear();

 

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(coinpin), coinInterrupt, RISING);

  pinMode(ledpin, OUTPUT);



  displayCredit();

 

}



// Main loop

void loop() {

 

  unsigned long  lastTime = millis() - timelastPulse;

  

  if( (pulse > 0 ) && ( lastTime > 200)  ){ // for show LED ON when Inserted

     

     bInserted = false;

      

     credits +=  pulse;

     pulse = 0; 



     displayCredit();

     

     

  }



   if( credits >= price ){

      // OK

       digitalWrite(ledpin, HIGH);

   }

  

}



// Interrupt

void coinInterrupt(){

 

  // Each time a pulse is sent from the coin acceptor,

  // interrupt main loop to add 1  and flip on the LED

 

  pulse++ ;

  timelastPulse = millis();

  



 // digitalWrite(ledpin, HIGH);

 // Serial.println( pulse );

   

}



void displayCredit()

{

     lcd.clear();

     lcd.setCursor(0,0);

     lcd.print("Credit:"); 



     lcd.setCursor(0,1);

     lcd.print( credits );

}

