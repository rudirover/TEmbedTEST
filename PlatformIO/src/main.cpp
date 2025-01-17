#include "main.h"


  static const uint16_t screenWidth  = 170;
  static const uint16_t screenHeight = 320;
  static lv_disp_draw_buf_t draw_buf;
  static lv_color_t buf[ screenWidth * screenHeight / 10 ];  
  TFT_eSPI Tft = TFT_eSPI(screenWidth, screenHeight); // TFT instance  
  //TFT_eSPI Tft = TFT_eSPI(); // TFT instance

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("***** T-Embed Board *****");


  // Print some info from TFT_eSPI
  Tft.init(); // don't forget to initialize TFT!!!
  
  /*
  int x= Tft.width();
  int y=Tft.height();
  Serial.print("Width  X=");
  Serial.println(x);
  Serial.print("Height Y=");
  Serial.println(y);
  Serial.println("");

/*

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
  
}

 
void loop()
{
    Serial.println("***** T-Embed Board *****");
  //lv_timer_handler(); /* let the GUI do its work */
  delay( 1000 );
}


/*
void setBackLightLevel(byte level)
{
    analogWrite(TFT_BL, level);
}
*/


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