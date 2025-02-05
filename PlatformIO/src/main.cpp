#include "main.h"

TaskHandle_t  networkScanTaskHandle =  NULL;
TaskHandle_t  guiTaskHandle = NULL;
QueueHandle_t networkScanQueueHandle;
bool runNetworkTask = false;

void setup()
{
  // Init serial port
  Serial.begin(115200);
  delay(500);
  Serial.println("*************************");   
  Serial.println("***** T-Embed Board *****"); 
  Serial.println("*************************");      

  xTaskCreate(guiTask, "guiTask", 8096, NULL, 0, &guiTaskHandle); 
  //xTaskCreatePinnedToCore(guiTask, "guiTask", 4096*2, NULL, 0, &guiTaskHandler, 0);
  Serial.println((uint32_t)guiTaskHandle);

  
  
  networkScanQueueHandle=xQueueCreate(10, sizeof(ssidInfo_t));
  xTaskCreate(networkScanTask, "networkScanTask", 4096, NULL, 0, &networkScanTaskHandle);
  //xTaskCreatePinnedToCore(networkScanTask, "networkScanTask", 4096*2, NULL, 0, &networkScanTaskHandler, 0);
  Serial.println((uint32_t)networkScanTaskHandle);   
}

 
void loop()
{
    delay(1000);
}