#include "main.h"

static TaskHandle_t  guiTaskHandler;

void setup()
{
  // Init serial port
  Serial.begin(115200);
  Serial.println("*************************");   
  Serial.println("***** T-Embed Board *****"); 
  Serial.println("*************************");      

  //xTaskCreate(guiTask, "guiTask", 8096, NULL, 10, &guiTaskHandler); 
  xTaskCreatePinnedToCore(guiTask, "guiTask", 4096*2, NULL, 0, NULL, 1);     
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