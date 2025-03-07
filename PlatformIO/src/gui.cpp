#include "gui.h"

TFT_eSPI Tft = TFT_eSPI(SCREENWIDTH, SCREENHEIGHT); // TFT instance
RotaryEncoder Encoder = RotaryEncoder(PIN_ENCODE_A, PIN_ENCODE_B);
OneButton Button =  OneButton(PIN_ENCODE_BTN);

lv_color_t *buf1[ SCREENWIDTH * SCREENHEIGHT]; 
lv_disp_draw_buf_t draw_buf;

String selectedPASS="";
String selectedSSID="";



int guiState = INFOPAGE_STATE;

void guiTask(void *param) {
  ssidInfo_t networkInfo;
  String dropDownList;

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

  Button.attachClick(buttonClicked);
  Button.attachLongPressStart(buttonLongPressed);

  // Trying to do something with lvgl with succes now!
  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println( LVGL_Arduino );
  Serial.println( "I am LVGL_Arduino" );

  vTaskDelay(500 / portTICK_PERIOD_MS);

  // Initialize the display
  lv_init();
  
  lv_disp_draw_buf_init( &draw_buf, buf1, NULL, DISP_BUF_SIZE );

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  disp_drv.hor_res = SCREENWIDTH;
  disp_drv.ver_res = SCREENHEIGHT;
  disp_drv.rotated = LV_DISP_ROT_270;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  disp_drv.full_refresh = 1;
  lv_disp_drv_register( &disp_drv );     

  ui_init();     

  while(true) {
    lv_timer_handler();
    Encoder.tick();
    RotaryEncoder::Direction direction=Encoder.getDirection();
    if(direction != RotaryEncoder::Direction::NOROTATION) readEncoder(direction);
    Button.tick();


    switch(guiState){
      case WIFISCANNING_STATE:
        if(uxQueueMessagesWaiting(networkScanQueueHandle)>0){
          dropDownList="";
          do {
            xQueueReceive(networkScanQueueHandle, &networkInfo, portMAX_DELAY);
            Serial.print("xQueueReceive: ");
            Serial.println(networkInfo.count);
            dropDownList=dropDownList+networkInfo.ssidName+"\n";
          } while (networkInfo.count != 1);
          lv_obj_add_flag(objects.wifi_spinner, LV_OBJ_FLAG_HIDDEN);
          Serial.print("list: ");
          Serial.println(dropDownList); 
          lv_dropdown_set_options(objects.wifi_ssid_drop_down, dropDownList.c_str());
          lv_dropdown_open(objects.wifi_ssid_drop_down);
          lv_group_focus_obj(objects.wifi_ssid_drop_down);        
          lv_group_set_editing(groups.wifiPageGroup, true);          
          guiState=WIFISSIDDROP_STATE;                             
        }
        break;
    }
  }
}

void buttonClicked(){
  char selection[33];
  uint16_t btn;
  switch (guiState){
    case WIFIPAGE_STATE: 
      lv_group_add_obj(groups.wifiPageGroup, objects.wifi_ssid_drop_down);
      lv_group_add_obj(groups.wifiPageGroup, objects.wifi_pass_text);
      lv_group_add_obj(groups.wifiPageGroup, objects.wifi_pass_keyb);
      lv_group_add_obj(groups.wifiPageGroup, objects.wifi_pass_input);                    
      guiState = WIFISSIDFOCUS_STATE;
      break;
    case WIFISSIDFOCUS_STATE:
      lv_obj_clear_flag(objects.wifi_spinner, LV_OBJ_FLAG_HIDDEN);
      Serial.print("networkScanTaskHandler: ");
      Serial.println(uint32_t(networkScanTaskHandle));
      vTaskResume(networkScanTaskHandle);
      guiState = WIFISCANNING_STATE;      
      break;
    case WIFISSIDDROP_STATE:
      lv_group_send_data(groups.wifiPageGroup, LV_KEY_ENTER);          
      lv_dropdown_get_selected_str(objects.wifi_ssid_drop_down, selection, sizeof(selection));
      //Serial.print("selection: ");
      //Serial.println(selection);
      selectedSSID=selection;
      if(selectedSSID==connectedSSID){
        selectedPASS==connectedPASS;
      } else {
        selectedPASS="New Password";
      }
      lv_textarea_set_text(objects.wifi_pass_text, selectedPASS.c_str());
      lv_group_focus_obj(objects.wifi_ssid_drop_down);
      //Serial.print("selectedStr: ");
      //Serial.println(selectedSSID);
      guiState=WIFISSIDFOCUS_STATE;             
      break;
    case WIFIPASSFOCUS_STATE:
      lv_obj_clear_flag(objects.wifi_pass_input, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(objects.wifi_pass_keyb, LV_OBJ_FLAG_HIDDEN);
      lv_group_focus_obj(objects.wifi_pass_keyb);        
      lv_textarea_set_text(objects.wifi_pass_input, lv_textarea_get_text(objects.wifi_pass_text));
      lv_group_set_editing(groups.wifiPageGroup, true);    
      guiState=WIFIPASSEDIT_STATE;
      break; 
    case WIFIPASSEDIT_STATE:
      lv_event_send(objects.wifi_pass_keyb, LV_EVENT_VALUE_CHANGED, NULL);      
      btn=lv_keyboard_get_selected_btn(objects.wifi_pass_keyb);
      Serial.print("Btn: ");
      Serial.println(btn);      
      if(btn==39){// OK btn pressed
        lv_obj_add_flag(objects.wifi_pass_input, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(objects.wifi_pass_keyb, LV_OBJ_FLAG_HIDDEN);
        lv_group_focus_obj(objects.wifi_pass_text);        
        lv_textarea_set_text(objects.wifi_pass_text, lv_textarea_get_text(objects.wifi_pass_input));
        lv_group_set_editing(groups.wifiPageGroup, false);
        guiState=WIFIPASSFOCUS_STATE;  
      }
      if(btn==35){// Cancel btn pressed}
        lv_obj_add_flag(objects.wifi_pass_input, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(objects.wifi_pass_keyb, LV_OBJ_FLAG_HIDDEN);
        lv_group_focus_obj(objects.wifi_pass_text); 
        lv_group_set_editing(groups.wifiPageGroup, false);
        guiState=WIFIPASSFOCUS_STATE; 
      }                          
      break;    
  }      
}

void buttonLongPressed(){
  switch (guiState){
    case WIFISSIDFOCUS_STATE:
    case WIFIPASSFOCUS_STATE: 
      lv_group_remove_all_objs(groups.wifiPageGroup);
      guiState = WIFIPAGE_STATE;
      break;
    case WIFIPASSEDIT_STATE:
      lv_obj_add_flag(objects.wifi_pass_input, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(objects.wifi_pass_keyb, LV_OBJ_FLAG_HIDDEN);
      lv_group_focus_obj(objects.wifi_pass_text);
      guiState=WIFIPASSFOCUS_STATE;
      break;             
  }      
}


void readEncoder(RotaryEncoder::Direction direction){
  switch(guiState) {
  case INFOPAGE_STATE:
    if(direction == RotaryEncoder::Direction::CLOCKWISE){
      loadScreen(SCREEN_ID_TEMP_PAGE, LV_SCR_LOAD_ANIM_OVER_LEFT);
      guiState=TEMPPAGE_STATE;        
    }        
    break;
  case TEMPPAGE_STATE:
    if(direction == RotaryEncoder::Direction::CLOCKWISE){
      loadScreen(SCREEN_ID_WIFI_PAGE, LV_SCR_LOAD_ANIM_OVER_LEFT);
      guiState=WIFIPAGE_STATE;        
    }
    if(direction == RotaryEncoder::Direction::COUNTERCLOCKWISE){
      loadScreen(SCREEN_ID_INFO_PAGE, LV_SCR_LOAD_ANIM_OVER_RIGHT);
      guiState=INFOPAGE_STATE;         
    }       
    break;
  case WIFIPAGE_STATE:
    if(direction == RotaryEncoder::Direction::COUNTERCLOCKWISE){
      loadScreen(SCREEN_ID_TEMP_PAGE, LV_SCR_LOAD_ANIM_OVER_RIGHT);
      guiState=TEMPPAGE_STATE;        
    }         
    break;
  case WIFISSIDFOCUS_STATE:
    lv_group_focus_obj(objects.wifi_pass_text);
    guiState=WIFIPASSFOCUS_STATE;      
    break;
  case WIFISSIDDROP_STATE:
    if(direction == RotaryEncoder::Direction::CLOCKWISE){  
      lv_group_send_data(groups.wifiPageGroup, LV_KEY_UP);       
    }  
    if(direction == RotaryEncoder::Direction::COUNTERCLOCKWISE){  
      lv_group_send_data(groups.wifiPageGroup, LV_KEY_DOWN);       
    }     
    break;
  case WIFIPASSFOCUS_STATE:
    lv_group_focus_obj(objects.wifi_ssid_drop_down);
    guiState=WIFISSIDFOCUS_STATE;      
    break;
  case WIFIPASSEDIT_STATE:
    if(direction == RotaryEncoder::Direction::CLOCKWISE){  
      lv_group_send_data(groups.wifiPageGroup, LV_KEY_LEFT);       
    }  
    if(direction == RotaryEncoder::Direction::COUNTERCLOCKWISE){  
      lv_group_send_data(groups.wifiPageGroup, LV_KEY_RIGHT);       
    } 
    break;       
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

    Tft.setAddrWindow( area->x1, area->y1, w, h );    
    Tft.pushColors( ( uint16_t * )&color_p->full, w * h );

    lv_disp_flush_ready( disp );  
}
