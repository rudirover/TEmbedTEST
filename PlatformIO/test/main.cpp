#include "main.h"

int counter=0;
void setup() {
  Serial.begin(115200);
  Serial.printf("psram size : %d kb\r\n", ESP.getPsramSize() / 1024);
  Serial.printf("FLASH size : %d kb\r\n", ESP.getFlashChipSize() / 1024);
}

void loop() {
    counter++;
    Serial.print("Counter: ");
    Serial.println(counter);
    delay(1000);
}