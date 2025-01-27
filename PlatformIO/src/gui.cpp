#include "gui.h"
#include "ui.h"
#include <lvgl.h>

const uint16_t screenWidth  = SCREENWIDTH;
const uint16_t screenHeight = SCREENHEIGHT;
lv_color_t buf1[ screenWidth * screenHeight];
lv_color_t buf2[ screenWidth * screenHeight];   
TFT_eSPI Tft = TFT_eSPI(screenWidth, screenHeight); // TFT instance 
lv_disp_draw_buf_t draw_buf;

lv_obj_t *btn1;

typedef struct {
    uint8_t cmd;
    uint8_t data[14];
    uint8_t len;
} lcd_cmd_t;

lcd_cmd_t lcd_st7789v[] = {
    {0x11, {0}, 0 | 0x80},
    {0x3A, {0X05}, 1},
    {0xB2, {0X0B, 0X0B, 0X00, 0X33, 0X33}, 5},
    {0xB7, {0X75}, 1},
    {0xBB, {0X28}, 1},
    {0xC0, {0X2C}, 1},
    {0xC2, {0X01}, 1},
    {0xC3, {0X1F}, 1},
    {0xC6, {0X13}, 1},
    {0xD0, {0XA7}, 1},
    {0xD0, {0XA4, 0XA1}, 2},
    {0xD6, {0XA1}, 1},
    {0xE0, {0XF0, 0X05, 0X0A, 0X06, 0X06, 0X03, 0X2B, 0X32, 0X43, 0X36, 0X11, 0X10, 0X2B, 0X32}, 14},
    {0xE1, {0XF0, 0X08, 0X0C, 0X0B, 0X09, 0X24, 0X2B, 0X22, 0X43, 0X38, 0X15, 0X16, 0X2F, 0X37}, 14},
};

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

/*
    // Update Embed initialization parameters
    for (uint8_t i = 0; i < (sizeof(lcd_st7789v) / sizeof(lcd_cmd_t)); i++) {
        Tft.writecommand(lcd_st7789v[i].cmd);
        for (int j = 0; j < (lcd_st7789v[i].len & 0x7f); j++) {
            Tft.writedata(lcd_st7789v[i].data[j]);
        }

        if (lcd_st7789v[i].len & 0x80) {
            delay(120);
        }
    }   
  */

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
  lv_disp_draw_buf_init( &draw_buf, buf1, NULL, screenWidth * screenHeight );

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.rotated = LV_DISP_ROT_270;
  //disp_drv.sw_rotate = 1;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  disp_drv.full_refresh = 0;
  lv_disp_drv_register( &disp_drv );

  /* Encoder setup
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_ENCODER;
  indev_drv.read_cb = readEncoder;
  static lv_indev_t *indev;
  indev=lv_indev_drv_register(&indev_drv);
  lv_group_t *group = lv_group_get_default();
  lv_indev_set_group (indev, group);
  */     

  ui_init();

  while(true) {
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    loadScreen(SCREEN_ID_INFO_PAGE, LV_SCR_LOAD_ANIM_OVER_RIGHT);    
 
    ui_tick();
    lv_timer_handler();    
    vTaskDelay(2000 / portTICK_PERIOD_MS);    
    loadScreen(SCREEN_ID_WIFI_PAGE, LV_SCR_LOAD_ANIM_OVER_LEFT);

    ui_tick();
    lv_timer_handler();    
    vTaskDelay(2000 / portTICK_PERIOD_MS);    
    loadScreen(SCREEN_ID_TEMP_PAGE, LV_SCR_LOAD_ANIM_OVER_LEFT);    

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