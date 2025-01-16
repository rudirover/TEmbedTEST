#include <Arduino.h>
#include <analogWrite.h>
#include <Preferences.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <TFT_eSPI.h>
#include <SPIFFS.h>
#include <lvgl.h>


//#define SERVERADDRESS 192.168.0.2
#define SERVERPORT 80

// Bijs 1
//const char* ssid = "telenet-9BE55CB";
//const char* password = "w28vtueaKree";

// Bijs 2
//const char* ssid = "WifiBijs2.4";
//const char* password = "bijs292929";

// Marisa
//const char* ssid = "telenet-8F5AC";
//const char* password = "JJ3K8QhKwrKV";

// Rudi
const char* ssid = "Orange-beb32";
const char* password = "78dh8JE7";

// B&B Wannes
//const char* ssid = "WiFi-2.4-60D7";
//const char* password = "719FC39D67";

typedef struct {
  byte day;
  byte hour;
  byte min;
  byte mode;
} clockTableEntry;

uint16_t currentTemp = 203;
uint16_t currentHumid = 90;
uint16_t dayTimeTemp = 215;
uint16_t nightTimeTemp = 150;
uint16_t antiFreezeTemp = 70;
uint8_t appMode = 1;
uint16_t oldCurrentTemp = 0;
uint16_t oldCurrentHumid = 0;
uint16_t oldDayTimeTemp = 0;
uint16_t oldNightTimeTemp = 0;
uint16_t oldAntiFreezeTemp = 0;
uint8_t oldAppMode = 0;
bool simulate = true;

clockTableEntry clockTableList[64];
byte clockTableCount;
clockTableEntry entry;
uint32_t clockTableUser = 0;
uint32_t oldClockTableUser = 0;


AsyncWebServer httpServer(SERVERPORT);
AsyncEventSource events("/events");
Preferences programData;
  

void handleNotFound(AsyncWebServerRequest* request);
void handleRoot(AsyncWebServerRequest *request);
void handleAppModeGet(AsyncWebServerRequest *request);
void handleAppModeSet(AsyncWebServerRequest *request);
void handleCurrentTempGet(AsyncWebServerRequest *request);
void handleCurrentTempSet(AsyncWebServerRequest *request);
void handleCurrentTempUp(AsyncWebServerRequest *request);
void handleCurrentTempDown(AsyncWebServerRequest *request);
void handleCurrentHumidGet(AsyncWebServerRequest *request);
void handleCurrentHumidSet(AsyncWebServerRequest *request);
void handleCurrentHumidUp(AsyncWebServerRequest *request);
void handleCurrentHumidDown(AsyncWebServerRequest *request);
void handleDayTimeTempGet(AsyncWebServerRequest *request);
void handleDayTimeTempSet(AsyncWebServerRequest *request);
void handleDayTimeTempUp(AsyncWebServerRequest *request);
void handleDayTimeTempDown(AsyncWebServerRequest *request);
void handleNightTimeTempGet(AsyncWebServerRequest *request);
void handleNightTimeTempSet(AsyncWebServerRequest *request);
void handleNightTimeTempUp(AsyncWebServerRequest *request);
void handleNightTimeTempDown(AsyncWebServerRequest *request);
void handleAntiFreezeTempGet(AsyncWebServerRequest *request);
void handleAntiFreezeTempSet(AsyncWebServerRequest *request);
void handleAntiFreezeTempUp(AsyncWebServerRequest *request);
void handleAntiFreezeTempDown(AsyncWebServerRequest *request);
void handleClockTableGet(AsyncWebServerRequest *request);
void handleClockTableSet(AsyncWebServerRequest *request);
void handleClockTableLockGet(AsyncWebServerRequest *request);
void handleClockTableLockSet(AsyncWebServerRequest *request);
void handleWebPage(AsyncWebServerRequest *request);
void handleScriptFile(AsyncWebServerRequest *request);
void handleStyleFile(AsyncWebServerRequest *request);
void handleDayTimeSvg(AsyncWebServerRequest *request);
void handleNightTimeSvg(AsyncWebServerRequest *request);
void handleAntiFreezeSvg(AsyncWebServerRequest *request);
void handleClockModeSvg(AsyncWebServerRequest *request);
void handleExpandSignSvg(AsyncWebServerRequest *request);
void handleColapseSignSvg(AsyncWebServerRequest *request);
void handleEditSignSvg(AsyncWebServerRequest *request);
void handleUnselectedSignSvg(AsyncWebServerRequest *request);
void handleSelectedSignSvg(AsyncWebServerRequest *request);
void handleDeleteSignSvg(AsyncWebServerRequest *request);
void handleAddSignSvg(AsyncWebServerRequest *request);
void saveClockTable();
void loadClockTable();

void setBackLightLevel(byte level);

void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );
