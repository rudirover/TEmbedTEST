#include "main.h"

void setup()
{
  // Init serial port
  Serial.begin(115200);
  Serial.println("*************************");   
  Serial.println("***** T-Embed Board *****"); 
  Serial.println("*************************");      

  guiSetup();    
}

 
void loop()
{
    guiLoop();
}
