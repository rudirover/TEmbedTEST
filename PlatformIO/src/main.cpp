#include "main.h"


  static const uint16_t screenWidth  = 240;
  static const uint16_t screenHeight = 320; //Tft.height();
  static lv_disp_draw_buf_t draw_buf;
  static lv_color_t buf[ screenWidth * screenHeight / 10 ];  
  TFT_eSPI Tft = TFT_eSPI(screenWidth, screenHeight); // TFT instance  
  //TFT_eSPI Tft = TFT_eSPI(); // TFT instance

void setup()
{
  setBackLightLevel(50);

  // start up filesystem
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  
  File file = SPIFFS.open("/webpage.html");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }

  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("***** WebServer Board *****");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Board MAC address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  /*
  // Print some info from TFT_eSPI
  Tft.init(); // don't forget to initialize TFT!!!
  int x= Tft.width();
  int y=Tft.height();
  Serial.print("Width  X=");
  Serial.println(x);
  Serial.print("Height Y=");
  Serial.println(y);
  Serial.println("");

  // Trying to do something with lvgl with succes now!
  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println( LVGL_Arduino );
  Serial.println( "I am LVGL_Arduino" );

  // Initialize the display
  lv_init();
  lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );


  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  // Change the following line to your display resolution
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  //Create screen objects
  lv_obj_t *temperatureBtn; 
  lv_obj_t *temperatureLabel; 
  static lv_style_t temperatureStyle;  
  lv_obj_t *btn1;
  lv_obj_t *btn2;
  lv_obj_t *screenMain;
  lv_obj_t *label;  


  screenMain = lv_obj_create(NULL);

  lv_style_init(&temperatureStyle);
  lv_style_set_text_font(&temperatureStyle, &lv_font_montserrat_48);

  temperatureBtn = lv_btn_create(screenMain);
  //lv_obj_add_event_cb(btn1, event_handler_btn);
  lv_obj_set_width(temperatureBtn, 230);
  lv_obj_set_height(temperatureBtn, 64);
  lv_obj_set_pos(temperatureBtn, 5, 5);  


  temperatureLabel = lv_label_create(temperatureBtn);
  lv_obj_add_style(temperatureLabel, &temperatureStyle, 0);  
  lv_label_set_long_mode(temperatureLabel, LV_LABEL_LONG_DOT);
  lv_label_set_text(temperatureLabel, "20.3 °C");
  lv_obj_set_style_text_align(temperatureLabel, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_size(temperatureLabel, 230, 64);
  lv_obj_set_pos(temperatureLabel, 0, 0);

  btn1 = lv_btn_create(screenMain);
  //lv_obj_add_event_cb(btn1, event_handler_btn);
  lv_obj_set_width(btn1, 70);
  lv_obj_set_height(btn1, 32);
  lv_obj_set_pos(btn1, 32, 170);

  lv_obj_t * label1 = lv_label_create(btn1);
  lv_label_set_text(label1, "Hello");


  btn2 = lv_btn_create(screenMain);
  //lv_obj_add_event_cb(btn2, event_handler_btn);
  lv_obj_set_width(btn2, 70);
  lv_obj_set_height(btn2, 32);
  lv_obj_set_pos(btn2, 142, 170);

  lv_obj_t * label2 = lv_label_create(btn2);
  lv_label_set_text(label2, "Goodbye");

  lv_scr_load(screenMain);
  */

  httpServer.onNotFound(handleNotFound);
  httpServer.on("/", HTTP_GET, handleRoot);

  // Handling appMode
  httpServer.on("/thermostat/appMode/get", HTTP_GET, handleAppModeGet);
  httpServer.on("/thermostat/appMode/set", HTTP_GET, handleAppModeSet);

  // Handling currentTemp
  httpServer.on("/thermostat/currentTemp/get", HTTP_GET, handleCurrentTempGet);
  httpServer.on("/thermostat/currentTemp/set", HTTP_GET, handleCurrentTempSet);
  httpServer.on("/thermostat/currentTemp/up", HTTP_GET, handleCurrentTempUp);
  httpServer.on("/thermostat/currentTemp/down", HTTP_GET, handleCurrentTempDown);

   // Handling currentHumid
  httpServer.on("/thermostat/currentHumid/get", HTTP_GET, handleCurrentHumidGet);
  httpServer.on("/thermostat/currentHumid/set", HTTP_GET, handleCurrentHumidSet);
  httpServer.on("/thermostat/currentHumid/up", HTTP_GET, handleCurrentHumidUp);
  httpServer.on("/thermostat/currentHumid/down", HTTP_GET, handleCurrentHumidDown);

  // Handling dayTimeTemp
  httpServer.on("/thermostat/dayTimeTemp/get", HTTP_GET, handleDayTimeTempGet);
  httpServer.on("/thermostat/dayTimeTemp/set", HTTP_GET, handleDayTimeTempSet);
  httpServer.on("/thermostat/dayTimeTemp/up", HTTP_GET, handleDayTimeTempUp);
  httpServer.on("/thermostat/dayTimeTemp/down", HTTP_GET, handleDayTimeTempDown);

  // Handling nightTimeTemp
  httpServer.on("/thermostat/nightTimeTemp/get", HTTP_GET, handleNightTimeTempGet);
  httpServer.on("/thermostat/nightTimeTemp/set", HTTP_GET, handleNightTimeTempSet);
  httpServer.on("/thermostat/nightTimeTemp/up", HTTP_GET, handleNightTimeTempUp);
  httpServer.on("/thermostat/nightTimeTemp/down", HTTP_GET, handleNightTimeTempDown);
  
  // Handling antiFreezeTemp
  httpServer.on("/thermostat/antiFreezeTemp/get", HTTP_GET, handleAntiFreezeTempGet);
  httpServer.on("/thermostat/antiFreezeTemp/set", HTTP_GET, handleAntiFreezeTempSet);
  httpServer.on("/thermostat/antiFreezeTemp/up", HTTP_GET, handleAntiFreezeTempUp);
  httpServer.on("/thermostat/antiFreezeTemp/down", HTTP_GET, handleAntiFreezeTempDown);

  // Handling clockTable
  httpServer.on("/thermostat/clockTable/get", HTTP_GET, handleClockTableGet);
  httpServer.on("/thermostat/clockTable/set", HTTP_GET, handleClockTableSet);  

  // Handling clockTable Locking
  httpServer.on("/thermostat/clockTableLock/get", HTTP_GET, handleClockTableLockGet);
  httpServer.on("/thermostat/clockTableLock/set", HTTP_GET, handleClockTableLockSet);  

  // Handling WebPage
  httpServer.on("/thermostat/webpage", HTTP_GET, handleWebPage); 

  // Handling ScriptFile
  httpServer.on("/thermostat/script.js", HTTP_GET, handleScriptFile);

  // Handling StyleFile
  httpServer.on("/thermostat/style.css", HTTP_GET, handleStyleFile);   

  // Handling assets
  httpServer.on("/thermostat/assets/dayTime.svg", HTTP_GET, handleDayTimeSvg);
  httpServer.on("/thermostat/assets/nightTime.svg", HTTP_GET, handleNightTimeSvg);
  httpServer.on("/thermostat/assets/antiFreeze.svg", HTTP_GET, handleAntiFreezeSvg);
  httpServer.on("/thermostat/assets/clockMode.svg", HTTP_GET, handleClockModeSvg);
  httpServer.on("/thermostat/assets/expandSign.svg", HTTP_GET, handleExpandSignSvg); 
  httpServer.on("/thermostat/assets/colapseSign.svg", HTTP_GET, handleColapseSignSvg);
  httpServer.on("/thermostat/assets/editSign.svg", HTTP_GET, handleEditSignSvg);
  httpServer.on("/thermostat/assets/unselectedSign.svg", HTTP_GET, handleUnselectedSignSvg); 
  httpServer.on("/thermostat/assets/selectedSign.svg", HTTP_GET, handleSelectedSignSvg); 
  httpServer.on("/thermostat/assets/deleteSign.svg", HTTP_GET, handleDeleteSignSvg);
  httpServer.on("/thermostat/assets/addSign.svg", HTTP_GET, handleAddSignSvg);           

  httpServer.addHandler(&events);

  httpServer.begin();
  Serial.println("HTTP server started.");

  //Testing saving to EEPROM of clockTable
  entry.day=1;
  entry.hour=10;
  entry.min=0;
  entry.mode=1;
  clockTableList[0]=entry;

  entry.day=2;
  entry.hour=11;
  entry.min=30;
  entry.mode=2;
  clockTableList[1]=entry; 

  entry.day=5;
  entry.hour=9;
  entry.min=45;
  entry.mode=3;
  clockTableList[2]=entry; 

  entry.day=7;
  entry.hour=19;
  entry.min=15;
  entry.mode=1;
  clockTableList[3]=entry;

  entry.day=1;
  entry.hour=22;
  entry.min=30;
  entry.mode=2;
  clockTableList[4]=entry;      


  clockTableCount=5;

  saveClockTable();
  
}

 
void loop()
{
  //lv_timer_handler(); /* let the GUI do its work */
  delay( 100 );
  //currentTemp = currentTemp + round(random(10) - 5);
  //if (currentTemp > 400) currentTemp = 400;
  //if (currentTemp < 10) currentTemp = 10;
  /*
  simulate++;
  if(simulate>200) {
      events.send("my event content","myevent",millis());
      simulate=0;
  }
  */

  if (appMode != oldAppMode) {
    events.send("appMode", "updateEvent", millis()); 
    oldAppMode=appMode;
  }
  if(currentTemp != oldCurrentTemp) {
    events.send("currentTemp","updateEvent", millis());
    oldCurrentTemp = currentTemp;
  } 
  if(currentHumid != oldCurrentHumid) {
    events.send("currentHumid","updateEvent", millis());
    oldCurrentHumid = currentHumid;
  }  
  if(dayTimeTemp != oldDayTimeTemp) {
    events.send("dayTimeTemp","updateEvent", millis());
    oldDayTimeTemp = dayTimeTemp;
  }  
  if(nightTimeTemp != oldNightTimeTemp) {
    events.send("nightTimeTemp","updateEvent", millis());
    oldNightTimeTemp = nightTimeTemp;
  } 
  if(antiFreezeTemp != oldAntiFreezeTemp) {
    events.send("antiFreezeTemp","updateEvent", millis());
    oldAntiFreezeTemp = antiFreezeTemp;
  }
  if (clockTableUser != oldClockTableUser) {
    events.send("clockTableLock","updateEvent", millis()); 
    oldClockTableUser=clockTableUser;
  } 
}


void handleNotFound(AsyncWebServerRequest* request)
{
  Serial.println("handleNotFound");
  request->send(404, "text/plain", "Not Found");
}


void handleRoot(AsyncWebServerRequest *request)
{
  Serial.println("handleRoot");
  request->send(200, "text/plain", "Hello From ThermostatServer");
}


// Handling appMode
void handleAppModeGet(AsyncWebServerRequest *request)
{
  Serial.println("handleAppModeGet");  
      //events.send("my event content","myevent",millis());  
  request->send(200, "text/plain", "appMode="+String(appMode));
}


void handleAppModeSet(AsyncWebServerRequest *request)
{
  Serial.println("handleAppModeSet");  
  uint8_t temp;
  temp = (request->getParam(0)->value()).toInt();
  Serial.println("temp="+String(appMode));  
  if((temp >= 1) && (temp <= 4)) appMode=temp;
  Serial.println("appMode="+String(appMode));   
  request->send(200, "text/plain", "appMode="+String(appMode));
}

// Handling currentTemp
void handleCurrentTempGet(AsyncWebServerRequest *request)
{
  Serial.println("handleCurrentTempGet");  
  request->send(200, "text/plain", "currentTemp="+String(currentTemp));
}


void handleCurrentTempSet(AsyncWebServerRequest *request)
{
  Serial.println("handleCurrentTempSet");  
  uint16_t temp;
  temp = (request->getParam(0)->value()).toInt();
  if((temp >= 50) && (temp <= 300)) currentTemp=temp;
  request->send(200, "text/plain", "currentTemp="+String(currentTemp));
}


void handleCurrentTempUp(AsyncWebServerRequest *request)
{
  Serial.println("handleCurrentTempUp");
  currentTemp+=5;
  if(currentTemp > 300) currentTemp=300;
  request->send(200, "text/plain", "currentTemp="+String(currentTemp));
}


void handleCurrentTempDown(AsyncWebServerRequest *request)
{
  Serial.println("handleCurrentTempDown");  
  currentTemp-=5;
  if(currentTemp < 50) currentTemp=50;
  request->send(200, "text/plain", "currentTemp="+String(currentTemp));
}


// Handling currentHumid
void handleCurrentHumidGet(AsyncWebServerRequest *request)
{
  Serial.println("handleCurrentHumidGet");  
  request->send(200, "text/plain", "currentHumid="+String(currentHumid));
}


void handleCurrentHumidSet(AsyncWebServerRequest *request)
{
  Serial.println("handleCurrentHumidSet");  
  uint16_t temp;
  temp = (request->getParam(0)->value()).toInt();
  if((temp >= 10) && (temp <= 99)) currentHumid=temp;
  request->send(200, "text/plain", "currentHumid="+String(currentHumid));
}


void handleCurrentHumidUp(AsyncWebServerRequest *request)
{
  Serial.println("handleCurrentHumidUp");
  currentHumid+=1;
  if(currentHumid > 99) currentHumid=99;
  request->send(200, "text/plain", "currentHumid="+String(currentHumid));
}


void handleCurrentHumidDown(AsyncWebServerRequest *request)
{
  Serial.println("handleCurrentHumidDown");  
  currentHumid-=1;
  if(currentHumid < 10) currentHumid=10;
  request->send(200, "text/plain", "currentHumid="+String(currentHumid));
}


// Handling dayTimeTemp
void handleDayTimeTempGet(AsyncWebServerRequest *request)
{
  Serial.println("handleDayTimeTempGet");  
  request->send(200, "text/plain", "dayTimeTemp="+String(dayTimeTemp));
}


void handleDayTimeTempSet(AsyncWebServerRequest *request)
{
  Serial.println("handleDayTimeTempSet");  
  uint16_t temp;
  temp = (request->getParam(0)->value()).toInt();
  if((temp >= 50) && (temp <= 300)) dayTimeTemp=temp;
  request->send(200, "text/plain", "dayTimeTemp="+String(dayTimeTemp));
}


void handleDayTimeTempUp(AsyncWebServerRequest *request)
{
  Serial.println("handleDayTimeTempUp");
  dayTimeTemp+=5;
  if(dayTimeTemp > 300) dayTimeTemp=300;
  request->send(200, "text/plain", "dayTimeTemp="+String(dayTimeTemp));
}


void handleDayTimeTempDown(AsyncWebServerRequest *request)
{
  Serial.println("handleDayTimeTempDown");  
  dayTimeTemp-=5;
  if(dayTimeTemp < 50) dayTimeTemp=50;
  request->send(200, "text/plain", "dayTimeTemp="+String(dayTimeTemp));
}


// Handling nightTimeTemp
void handleNightTimeTempGet(AsyncWebServerRequest *request)
{
  Serial.println("handleNightTimeTempGet");  
  request->send(200, "text/plain", "nightTimeTemp="+String(nightTimeTemp));
}


void handleNightTimeTempSet(AsyncWebServerRequest *request)
{
  Serial.println("handleNightTimeTempSet");  
  uint16_t temp;
  temp = (request->getParam(0)->value()).toInt();
  if((temp >= 50) && (temp <= 300)) nightTimeTemp=temp;
  request->send(200, "text/plain", "nightTimeTemp="+String(nightTimeTemp));
}


void handleNightTimeTempUp(AsyncWebServerRequest *request)
{
  Serial.println("handleNightTimeTempUp");
  nightTimeTemp+=5;
  if(nightTimeTemp > 300) nightTimeTemp=300;
  request->send(200, "text/plain", "nightTimeTemp="+String(nightTimeTemp));
}


void handleNightTimeTempDown(AsyncWebServerRequest *request)
{
  Serial.println("handleNightTimeTempDown");  
  nightTimeTemp-=5;
  if(nightTimeTemp < 50) nightTimeTemp=50;
  request->send(200, "text/plain", "nightTimeTemp="+String(nightTimeTemp));
}


// Handling antiFreezeTemp
void handleAntiFreezeTempGet(AsyncWebServerRequest *request)
{
  Serial.println("handleAntiFreezeTempGet");  
  request->send(200, "text/plain", "antiFreezeTemp="+String(antiFreezeTemp));
}


void handleAntiFreezeTempSet(AsyncWebServerRequest *request)
{
  Serial.println("handleAntiFreezeTempSet");  
  uint16_t temp;
  temp = (request->getParam(0)->value()).toInt();
  if((temp >= 50) && (temp <= 300)) antiFreezeTemp=temp;
  request->send(200, "text/plain", "antiFreezeTemp="+String(antiFreezeTemp));
}


void handleAntiFreezeTempUp(AsyncWebServerRequest *request)
{
  Serial.println("handleAntiFreezeTempUp");
  antiFreezeTemp+=5;
  if(antiFreezeTemp > 300) antiFreezeTemp=300;
  request->send(200, "text/plain", "antiFreezeTemp="+String(antiFreezeTemp));
}


void handleAntiFreezeTempDown(AsyncWebServerRequest *request)
{
  Serial.println("handleAntiFreezeTempDown");  
  antiFreezeTemp-=5;
  if(antiFreezeTemp < 50) antiFreezeTemp=50;
  request->send(200, "text/plain", "antiFreezeTemp="+String(antiFreezeTemp));
}


// Handling clockTable
void handleClockTableGet(AsyncWebServerRequest *request)
{
  String sendString;
  
  Serial.println("handleClockTableGet");
  loadClockTable();
  sendString=String(clockTableCount);
  for(int counter=0;counter<clockTableCount;counter++) {
    entry=clockTableList[counter];
    sendString=sendString + "," + String(entry.day);
    sendString=sendString + "," + String(entry.hour);
    sendString=sendString + "," + String(entry.min);
    sendString=sendString + "," + String(entry.mode);
  }
  request->send(200, "text/plain", "getClockTable="+sendString);   
}

void handleClockTableSet(AsyncWebServerRequest *request)
{
  String sendString;
  
  Serial.println("handleClockTableSet"); 
  request->send(200, "text/plain", "setClockTable=OK");   
}

// Handling clockTable Locking (lock=OFF free to use, lock=ON Not free to use)
void handleClockTableLockGet(AsyncWebServerRequest *request)
{
  String sendString="clockTableLock=";
  uint32_t client=request->client()->getRemoteAddress();  

  Serial.println("handleClockTableLockGet: User: " + String(clockTableUser) + " Client: " + String(client));

  if((clockTableUser == 0) 
  or(clockTableUser == client)) {
    // clockTable is free to use
    sendString=sendString + "OFF";
  } else {
    // clockTable is not free to use
    sendString=sendString + "ON";    
  }
  request->send(200, "text/plain", sendString);
} 


void handleClockTableLockSet(AsyncWebServerRequest *request)
{
  String sendString="clockTableLock=";
  String temp=(request->getParam(0)->value());
  uint32_t client=request->client()->getRemoteAddress();

  Serial.println("handleClockTableLockSet: User: " + String(clockTableUser) + " Client: " + String(client));
  if (temp=="ON") {
    // Try to use clockTable
    if((clockTableUser==client)
    or(clockTableUser==0)) {
      // clockTable is free to use, set clockTableClient
      clockTableUser=client;
      sendString=sendString + "OK";
    } else {
      // clockTable is not free to use
      sendString=sendString + "NOK";
    }
  }
    if (temp=="OFF") {
    // Try to use clockTable
    if((clockTableUser==client)
    or(clockTableUser==0)) {
      // clockTable is free to use, reset clockTableClient
      clockTableUser=0;
      sendString=sendString + "OK";
    } else {
      // clockTable is not free to use
      sendString=sendString + "NOK";
    }
  } 
  request->send(200, "text/plain", sendString);
} 
 

// Handle WebPage
void handleWebPage(AsyncWebServerRequest *request)
{
  Serial.println("handleWebPage");
  request->send(SPIFFS, "/webpage.html", String(), false, NULL);
}


// Handle ScriptFile
void handleScriptFile(AsyncWebServerRequest *request)
{
  Serial.println("handleScriptFile");
  request->send(SPIFFS, "/script.js", String(), false, NULL);
}

// HandleStyleFile
void handleStyleFile(AsyncWebServerRequest *request)
{
  Serial.println("handleStyleFile");
  request->send(SPIFFS, "/style.css", String(), false, NULL);
}

// Handling assets
void handleDayTimeSvg(AsyncWebServerRequest *request)
{
  Serial.println("handleDayTimeSvg");
  request->send(SPIFFS, "/dayTime.svg", "image/svg+xml", false);
}


void handleNightTimeSvg(AsyncWebServerRequest *request)
{
  Serial.println("handleNightTimeSvg");
  request->send(SPIFFS,"/nightTime.svg", "image/svg+xml", false);
}


void handleAntiFreezeSvg(AsyncWebServerRequest *request)
{
  Serial.println("handleAntiFreezeSvg");
  request->send(SPIFFS, "/antiFreeze.svg", "image/svg+xml", false);
}


void handleClockModeSvg(AsyncWebServerRequest *request)
{
  Serial.println("handleClockModeSvg");
  request->send(SPIFFS, "/clockMode.svg", "image/svg+xml", false);
}


void handleExpandSignSvg(AsyncWebServerRequest *request)
{
  Serial.println("handleExpandSignSvg");
  request->send(SPIFFS, "/expandSign.svg", "image/svg+xml", false);
}


void handleColapseSignSvg(AsyncWebServerRequest *request)
{
  Serial.println("handleColapseSignSvg");
  request->send(SPIFFS, "/colapseSign.svg", "image/svg+xml", false);
}


void handleEditSignSvg(AsyncWebServerRequest *request)
{
  Serial.println("handleEditSignSvg");
  request->send(SPIFFS, "/editSign.svg", "image/svg+xml", false);
}


void handleUnselectedSignSvg(AsyncWebServerRequest *request)
{
  Serial.println("handleUnselectedSignSvg");
  request->send(SPIFFS, "/unselectedSign.svg", "image/svg+xml", false);
}


void handleSelectedSignSvg(AsyncWebServerRequest *request)
{
  Serial.println("handleSelectedSignSvg");
  request->send(SPIFFS, "/selectedSign.svg", "image/svg+xml", false);
}


void handleDeleteSignSvg(AsyncWebServerRequest *request)
{
  Serial.println("handleDeleteSignSvg");
  request->send(SPIFFS, "/deleteSign.svg", "image/svg+xml", false);
}


void handleAddSignSvg(AsyncWebServerRequest *request)
{
  Serial.println("handleAddSignSvg");
  request->send(SPIFFS, "/addSign.svg", "image/svg+xml", false);
}

void saveClockTable()
{
  String saveString;
  
  Serial.println("saveClockTable");
  programData.begin("clockTable", false);
  programData.clear();
  saveString=String(clockTableCount);   
  for (int counter=0;counter<clockTableCount;counter++)
  {  
    entry=clockTableList[counter];
    saveString=saveString + "," + String(entry.day);
    saveString=saveString + "," + String(entry.hour);
    saveString=saveString + "," + String(entry.min);
    saveString=saveString + "," + String(entry.mode);           
  }    
  //Serial.println("saveString: " + saveString);
  programData.putString("clockTableList", saveString);    
  programData.end(); 
}

void loadClockTable()
{
  int index;
  String loadString;
  
  Serial.println("loadClockTable");
  programData.begin("clockTable", true);
  loadString=programData.getString("clockTableList");
  programData.end();
  index=loadString.indexOf(",");
  //Serial.println("index: " + String(index));
  clockTableCount=loadString.substring(0, index).toInt();
  //Serial.println("clockTableCount: " + String(clockTableCount));  
  loadString=loadString.substring(index + 1);
  //Serial.println("loadString: " + loadString);  

  for (int counter=0;counter<clockTableCount;counter++)
  {
    index=loadString.indexOf(",");
    entry.day=loadString.substring(0, index).toInt();
    loadString=loadString.substring(index + 1); 
    index=loadString.indexOf(",");
    entry.hour=loadString.substring(0, index).toInt();
    loadString=loadString.substring(index + 1);
    index=loadString.indexOf(",");
    entry.min=loadString.substring(0, index).toInt();
    loadString=loadString.substring(index + 1); 
    index=loadString.indexOf(",");
    entry.mode=loadString.substring(0, index).toInt();
    loadString=loadString.substring(index + 1); 
    clockTableList[counter]=entry;      
    //Serial.println("Day: " + String(clockTableList[counter].day));
    //Serial.println("Hour: " + String(clockTableList[counter].hour));
    //Serial.println("Min: " + String(clockTableList[counter].min));
    //Serial.println("Mode: " + String(clockTableList[counter].mode));      
    //Serial.println("-------------------");    
  } 
}

void setBackLightLevel(byte level)
{
    analogWrite(TFT_BL, level);
}

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    Serial.println("Entering LVGL Callback.");
    Tft.startWrite();
    Tft.setAddrWindow( area->x1, area->y1, w, h );
    Tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    Tft.endWrite();

    lv_disp_flush_ready( disp );
    Serial.println("Leaving LVGL callback.");
}