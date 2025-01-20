#include "ui.h"

const uint16_t screenWidth  = SCREENWIDTH;
const uint16_t screenHeight = SCREENHEIGHT;
lv_color_t buf[ screenWidth * screenHeight / 10 ];  
TFT_eSPI Tft = TFT_eSPI(screenWidth, screenHeight); // TFT instance 
lv_disp_draw_buf_t draw_buf;
lv_group_t *group;
RotaryEncoder encoder = RotaryEncoder(PIN_ENCODE_A, PIN_ENCODE_B, RotaryEncoder::LatchMode::TWO03);
OneButton button=OneButton(PIN_ENCODE_BTN, true);

lv_obj_t *btn1;

void uiSetup() {

  // Init serial port
  Serial.begin(115200);
  Serial.println("***** T-Embed Board *****");  

  // Turn on lcd
  pinMode(POWER_ON, OUTPUT);
  digitalWrite(POWER_ON, HIGH);

  // Turn on black light
  setBackLightLevel(255);

  // Initialize TFT
  Tft.init(); // don't forget to initialize TFT!!!
  //Tft.setRotation(3);
  
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
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.rotated = LV_DISP_ROT_90;
  disp_drv.sw_rotate = 1;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_ENCODER;
  indev_drv.read_cb = readEncoder;
  static lv_indev_t *indev;
  indev=lv_indev_drv_register(&indev_drv);
      lv_group_t *group = lv_group_get_default();
lv_indev_set_group (indev, group);      
    //lv_group_set_default(group);


  //Create screen objects
  //lv_obj_t *temperatureBtn; 
  //lv_obj_t *temperatureLabel; 
  //static lv_style_t temperatureStyle;  
  //lv_obj_t *btn1;
  //lv_obj_t *btn2;
  //lv_obj_t *btn3;  
  lv_obj_t *screenMain;
  lv_obj_t *label;  


  screenMain = lv_scr_act();

  // Create buttons and add them to the group
     btn1 = lv_btn_create(screenMain);
    lv_obj_align(btn1, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_set_size(btn1, 100, 50);

    label = lv_label_create(btn1);
    lv_label_set_text(label, "Button 1");
    lv_obj_center(label);


    lv_obj_t * btn2 = lv_btn_create(screenMain);
    lv_obj_align(btn2, LV_ALIGN_TOP_LEFT, 120, 10);
    lv_obj_set_size(btn2, 100, 50);

    label = lv_label_create(btn2);
    lv_label_set_text(label, "Button 2");
    lv_obj_center(label);


    lv_obj_t * btn3 = lv_btn_create(screenMain);
    lv_obj_align(btn3, LV_ALIGN_TOP_LEFT, 230, 10);
    lv_obj_set_size(btn3, 100, 50);

    label = lv_label_create(btn3);
    lv_label_set_text(label, "Button 3");
    lv_obj_center(label);    
  

    // Add buttons to the group for focus management
    lv_group_add_obj(group, btn1);
    lv_group_add_obj(group, btn2);
    lv_group_add_obj(group, btn3);

    // Set the first button as the initial focused object
    lv_group_focus_obj(btn1);


/*
  lv_style_init(&temperatureStyle);
  lv_style_set_text_font(&temperatureStyle, &lv_font_montserrat_48);

  temperatureBtn = lv_btn_create(screenMain);
  lv_obj_add_event_cb(temperatureBtn, temperatureBtnClicked, LV_EVENT_CLICKED, NULL);
  lv_obj_set_size(temperatureBtn, 300, 64);
  lv_obj_set_pos(temperatureBtn, 10, 0);  


  temperatureLabel = lv_label_create(temperatureBtn);
  lv_obj_add_style(temperatureLabel, &temperatureStyle, 0);  
  lv_label_set_long_mode(temperatureLabel, LV_LABEL_LONG_DOT);
  lv_label_set_text(temperatureLabel, "20.3 °C");
  lv_obj_set_style_text_align(temperatureLabel, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_size(temperatureLabel, 300, 64);
  lv_obj_set_pos(temperatureLabel, 0, 0);

  btn1 = lv_btn_create(screenMain);
  //lv_obj_add_event_cb(btn1, event_handler_btn);
  lv_obj_set_size(btn1,70, 32);
  lv_obj_set_pos(btn1, 32, 100);

  lv_obj_t * label1 = lv_label_create(btn1);
  lv_label_set_text(label1, "Hello");


  btn2 = lv_btn_create(screenMain);
  //lv_obj_add_event_cb(btn2, event_handler_btn);
  lv_obj_set_size(btn2,70, 32);
  lv_obj_set_pos(btn2, 142, 100);

  lv_obj_t * label2 = lv_label_create(btn2);
  lv_label_set_text(label2, "Goodbye");


    // Create a group for navigation
    lv_group_t *group = lv_group_create();
    lv_group_set_default(group);
    
    lv_group_add_obj(group, temperatureBtn);
    lv_group_add_obj(group, btn1);
    lv_group_add_obj(group, btn2);
  
    //lv_group_focus_obj(temperatureBtn);
    */
    

  //lv_scr_load(screenMain);

}


void uiLoop() {
    lv_timer_handler(); /* let the GUI do its work */
    encoder.tick();
    Serial.println(btn1->state);
}

void temperatureBtnClicked(lv_event_t *event){
    Serial.print("temperatureBtnClicked");
}

/* Reading input device (simulated encoder here) */
void readEncoder(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
  RotaryEncoder::Direction dir=encoder.getDirection();
  //Serial.println(encoder.getPosition());
  data->enc_diff = int16_t(dir);
  //Serial.println(data->enc_diff);
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
    Tft.startWrite();
    Tft.setAddrWindow( area->x1, area->y1, w, h );
    Tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    Tft.endWrite();

    lv_disp_flush_ready( disp );
    //Serial.println("Leaving LVGL callback.");
}