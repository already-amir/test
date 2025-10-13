#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BTN_UP     12
#define BTN_DOWN   13
#define BTN_OK     14
#define BTN_BACK   27



enum menu_state {
  MENU_MAIN,
  MENU_START,
  MENU_START_PAUSE,
  END_START_SUCCESS,
  END_START_UNSUCCESS,

  // *********************************** DO LATER
};

menu_state curr_menu = MENU_MAIN;
int selected_item = 0;
int top_index = 0;
unsigned long last_press = 0;

int turns = 0;
int rpm;
float pitch;
float coil_width;
float wire_width;
bool cw_dir;

void save_settings(){
  EEPROM.put(0,turns);
  EEPROM.put(4,rpm);
  EEPROM.put(8,pitch);
  EEPROM.put(12,coil_width);
  EEPROM.put(16,wire_width);
  EEPROM.put(20,cw_dir);

}

void load_setings(){
  EEPROM.get(0,turns);
  EEPROM.get(4,rpm);
  EEPROM.get(8,pitch);
  EEPROM.get(12,coil_width);
  EEPROM.get(16,wire_width);
  EEPROM.get(20,cw_dir);

  if (turns == 0){
    turns=1000;
    rpm=600;
    pitch=0.3;
    coil_width=20;
    wire_width=0.25;
    cw_dir=true;
    
    save_settings();
  }
}



void setup() {
 

}

void loop() {
  // put your main code here, to run repeatedly:

}
