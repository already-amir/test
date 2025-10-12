#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // آدرس I2C LCD ممکن است 0x3F باشد، اگر چیزی نمایش نداد تغییرش بده

// پین‌های دکمه‌ها
#define BTN_UP     12
#define BTN_DOWN   13
#define BTN_OK     14
#define BTN_BACK   27

// ساختار منوها
enum MenuState {
  MENU_MAIN,
  MENU_START,
  MENU_SETTINGS,
  MENU_MANUAL,
  MENU_INFO,
  MENU_EDIT_TURNS,
  MENU_EDIT_RPM,
  MENU_EDIT_PITCH,
  MENU_EDIT_WIDTH,
  MENU_EDIT_WIRE
};

MenuState currentMenu = MENU_MAIN;
int selectedItem = 0; // برای پیمایش بین آیتم‌ها
unsigned long lastPress = 0;

// توابع کمکی
bool buttonPressed(int pin) {
  if (digitalRead(pin) == LOW && millis() - lastPress > 200) {
    lastPress = millis();
    return true;
  }
  return false;
}

void showMenu() {
  lcd.clear();
  switch (currentMenu) {
    case MENU_MAIN:
      lcd.setCursor(0, 0);
      lcd.print(selectedItem == 0 ? ">Start" : " Start");
      lcd.setCursor(0, 1);
      lcd.print(selectedItem == 1 ? ">Settings" : " Settings");
      break;

    case MENU_START:
      lcd.setCursor(0, 0);
      lcd.print("Start winding...");
      lcd.setCursor(0, 1);
      lcd.print("OK=Back");
      break;

    case MENU_SETTINGS:
      lcd.setCursor(0, 0);
      if (selectedItem == 0) lcd.print(">Turns");
      else lcd.print(" Turns");
      lcd.setCursor(0, 1);
      if (selectedItem == 1) lcd.print(">RPM");
      else lcd.print(" RPM");
      break;

    case MENU_MANUAL:
      lcd.setCursor(0, 0);
      lcd.print("Manual move");
      lcd.setCursor(0, 1);
      lcd.print("OK=Back");
      break;

    case MENU_INFO:
      lcd.setCursor(0, 0);
      lcd.print("Coil Winder UI");
      lcd.setCursor(0, 1);
      lcd.print("By Amir & GPT");
      break;

    case MENU_EDIT_TURNS:
      lcd.setCursor(0, 0);
      lcd.print("Set Turns: 1200");
      lcd.setCursor(0, 1);
      lcd.print("OK=Save  BACK");
      break;

    case MENU_EDIT_RPM:
      lcd.setCursor(0, 0);
      lcd.print("Set RPM: 800");
      lcd.setCursor(0, 1);
      lcd.print("OK=Save  BACK");
      break;

    default:
      lcd.setCursor(0, 0);
      lcd.print("Unknown menu");
      break;
  }
}

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_OK, INPUT_PULLUP);
  pinMode(BTN_BACK, INPUT_PULLUP);

  showMenu();
}

void loop() {
  // کنترل منو اصلی
  if (currentMenu == MENU_MAIN) {
    if (buttonPressed(BTN_UP)) {
      selectedItem = (selectedItem - 1 + 2) % 2;
      showMenu();
    }
    if (buttonPressed(BTN_DOWN)) {
      selectedItem = (selectedItem + 1) % 2;
      showMenu();
    }
    if (buttonPressed(BTN_OK)) {
      if (selectedItem == 0) currentMenu = MENU_START;
      else currentMenu = MENU_SETTINGS;
      selectedItem = 0;
      showMenu();
    }
  }

  // تنظیمات
  else if (currentMenu == MENU_SETTINGS) {
    if (buttonPressed(BTN_UP)) {
      selectedItem = (selectedItem - 1 + 2) % 2;
      showMenu();
    }
    if (buttonPressed(BTN_DOWN)) {
      selectedItem = (selectedItem + 1) % 2;
      showMenu();
    }
    if (buttonPressed(BTN_OK)) {
      if (selectedItem == 0) currentMenu = MENU_EDIT_TURNS;
      else if (selectedItem == 1) currentMenu = MENU_EDIT_RPM;
      showMenu();
    }
    if (buttonPressed(BTN_BACK)) {
      currentMenu = MENU_MAIN;
      selectedItem = 0;
      showMenu();
    }
  }

  // سایر منوها
  else if (currentMenu == MENU_START || currentMenu == MENU_EDIT_TURNS || currentMenu == MENU_EDIT_RPM) {
    if (buttonPressed(BTN_BACK) || buttonPressed(BTN_OK)) {
      currentMenu = MENU_MAIN;
      selectedItem = 0;
      showMenu();
    }
  }
}
