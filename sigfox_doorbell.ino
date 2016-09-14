#include <Akeru.h>
#include <CapacitiveSensor.h>

// TD1208 Sigfox module IO definition
/*   Snootlab device | TX | RX
               Akeru | D4 | D5
               Akene | D5 | D4
            Breakout | your pick */
#define TX 4
#define RX 5

// Sigfox instance management 
Akeru akeru(RX, TX);


//Capacitive sensor
CapacitiveSensor   cs = CapacitiveSensor(2,8); // 1M resistor between pins 2 & 8, pin 8 is sensor pin, add a wire and or foil


//Global variable
bool flag = true;

void setup()                    
{
   cs.set_CS_AutocaL_Millis(0xFFFFFFFF);// turn off autocalibrate on channel 1 - just as an example
   //Serial.begin(9600);
   
   pinMode(7,OUTPUT);

   //Serial.println("Starting...");

   if (!akeru.begin())
  {
    //Serial.println("TD1208 KO");
    while(1);
  }else{
    //Serial.println("Ready!!");
  }
}

void loop()                    
{
   long sensor =  cs.capacitiveSensor(50);

   //Serial.println(sensor1);  // print sensor output 
   if(sensor >= 1000)
   {
    digitalWrite(7,HIGH);
    if(flag){
      sendMessage();
    }
    }
   else{
    digitalWrite(7,LOW);
   }  
}

void sendMessage(){
    flag = false;
    //Serial.println("Sending...");
    if (akeru.sendPayload("01"))
    {
      //Serial.println("Message sent !");
      
    }
    delay(1000);
    flag = true;
  
}

