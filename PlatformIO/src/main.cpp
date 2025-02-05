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


const char *get_var_setpoint_temperature(){
  return "22.5°C";
}

void set_var_setpoint_temperature(const char *value){

}

const char *get_var_actual_temperature(){
  return "20.5°C";
}

void set_var_actual_temperature(const char *value){

}
extern int32_t get_var_wifi_ssid_selected(){
  return 1;
}

void set_var_wifi_ssid_selected(int32_t value){

}

const char *get_var_wifi_ssid_list() {
  return "Rudis Wifi \n Another Wifi";
}

void set_var_wifi_ssid_list(const char *value){

}

const char *get_var_wifi_pass_input(){

}

void set_var_wifi_pass_input(const char *value){

}

bool get_var_wifi_pass_input_hidden() {

}

void set_var_wifi_pass_input_hidden(bool value) {
  
}