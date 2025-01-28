#include "gui.h"
#include "ui.h"
#include <lvgl.h>

lv_color_t *buf1[ SCREENWIDTH * SCREENHEIGHT];
//lv_color_t *buf2[ SCREENWIDTH * SCREENHEIGHT];   
TFT_eSPI Tft = TFT_eSPI(SCREENWIDTH, SCREENHEIGHT); // TFT instance 
lv_disp_draw_buf_t draw_buf;

unsigned long lastTickMillis = 0;
SemaphoreHandle_t guiMutex;
unsigned int screenTimer;

unsigned int newGuiState = INFOPAGE_STATE;
unsigned int oldGuiState = NONE_STATE;

#define SCREENTIME 2500

void guiTask(void *param) {

  // Turn on lcd
  pinMode(POWER_ON, OUTPUT);
  digitalWrite(POWER_ON, HIGH);

  // Turn on black light
  setBackLightLevel(255);

  // Initialize TFT
  Tft.init(); // don't forget to initialize TFT!!!
  Tft.setRotation(3);
  Tft.fillScreen(TFT_BLACK); 

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

    guiMutex = xSemaphoreCreateMutex();

  // Initialize the display
  lv_init();
  
  lv_disp_draw_buf_init( &draw_buf, buf1, NULL, DISP_BUF_SIZE );

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  disp_drv.hor_res = SCREENWIDTH;
  disp_drv.ver_res = SCREENHEIGHT;
  disp_drv.rotated = LV_DISP_ROT_270;
  //disp_drv.sw_rotate = 1;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  disp_drv.full_refresh = 1;
  lv_disp_drv_register( &disp_drv );    

  ui_init();

  if(xSemaphoreTake(guiMutex, portMAX_DELAY)==pdTRUE){
    loadScreen(SCREEN_ID_INFO_PAGE, LV_SCR_LOAD_ANIM_FADE_IN);      
    xSemaphoreGive(guiMutex);  
  }

  screenTimer = millis();

  while(true) {

    if(xSemaphoreTake(guiMutex, portMAX_DELAY)==pdTRUE){
      lv_timer_handler();
      xSemaphoreGive(guiMutex);
    }

    if(millis() - screenTimer > SCREENTIME) {
      screenTimer=millis();
      newGuiState++;
      if(newGuiState > WIFIPAGE_STATE) newGuiState=INFOPAGE_STATE;

      if(newGuiState != oldGuiState){
        if(xSemaphoreTake(guiMutex, portMAX_DELAY)==pdTRUE){
          switch (newGuiState) {
            case 1: loadScreen(SCREEN_ID_INFO_PAGE, LV_SCR_LOAD_ANIM_OVER_LEFT); break; 
            case 2: loadScreen(SCREEN_ID_TEMP_PAGE, LV_SCR_LOAD_ANIM_OVER_LEFT); break; 
            case 3: loadScreen(SCREEN_ID_WIFI_PAGE, LV_SCR_LOAD_ANIM_OVER_LEFT); break; 
          }
          xSemaphoreGive(guiMutex);
          oldGuiState = newGuiState;
        }      
      }
    }
  }
}


void setBackLightLevel(byte level)
{
    analogWrite(15, level);
}


/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    //Serial.println("Entering LVGL Callback.");
    //Tft.startWrite();
    Tft.setAddrWindow( area->x1, area->y1, w, h );
    //long start = millis();    
    Tft.pushColors( ( uint16_t * )&color_p->full, w * h );
    //Serial.printf("Execution Time = %lu mS\r\n",millis()-start);
    //Serial.print("x1: ");
    //Serial.print(area->x1);
    //Serial.print("   y1: ");    
    //Serial.println(area->y1);
    //Serial.print("x2: ");
    //Serial.print(area->x2);
    //Serial.print("   y2: ");    
    //Serial.println(area->y2);      
    //Tft.endWrite();

    lv_disp_flush_ready( disp );
    //Serial.println("Leaving LVGL callback.");   
}