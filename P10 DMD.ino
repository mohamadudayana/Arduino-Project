#include <DMD3.h>
#include <EMSans8x16.h>


DMD3 Disp(1,1);

void scan()
  { Disp.refresh();}
  void Disp_init()  { 
    //Disp.setDoubleBuffer(true);
    Timer1.initialize(2000);
    Timer1.attachInterrupt(scan);
    Timer1.pwm(9,40);
    Disp.clear();
    Disp.swapBuffers();
    }
    
const unsigned int MAX_MESSAGE_LENGTH = 19;

void setup() {
 Serial.begin(115200);
 Disp_init();
}

void loop() {

 //Check to see if anything is available in the serial receive buffer
 while (Serial.available() > 0)
 {
   //Create a place to hold the incoming message
   static char message[MAX_MESSAGE_LENGTH];
   static unsigned int message_pos = 0;

   //Read the next available byte in the serial receive buffer
   char inByte = Serial.read();

   //Message coming in (check not terminating character) and guard for over message size
   if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
   {
     //Add the incoming byte to our message
     message[message_pos] = inByte;
     message_pos++;
   }
   //Full message received...
   else
   {
     //Add null character to string
    message[message_pos] = '\0';

     //Print the message (or do other things)
     Serial.println(message);
     Disp.clear();
   // Disp.setFont(EMSansSP8x16);
   Disp.setFont(EMSans8x16);
   // Disp.drawText(0, -1, "TS ");
    Disp.drawText(3, 0, message);

     //Reset for the next message
     message_pos = 0;
   }
 }
}
