#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// دکمه‌ها
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
  MENU_EDIT_WIRE,
  MENU_EDIT_DIR
};

MenuState currentMenu = MENU_MAIN;
int selectedItem = 0;
int topIndex = 0; // برای اسکرول
unsigned long lastPress = 0;

// تنظیمات ذخیره‌شونده
int turns;
int rpm;
float pitch;
float coilWidth;
float wireDia;
bool directionCW;

// توابع کمکی برای EEPROM
void saveSettings() {
  EEPROM.put(0, turns);
  EEPROM.put(4, rpm);
  EEPROM.put(8, pitch);
  EEPROM.put(12, coilWidth);
  EEPROM.put(16, wireDia);
  EEPROM.put(20, directionCW);
  EEPROM.commit();
}

void loadSettings() {
  EEPROM.get(0, turns);
  EEPROM.get(4, rpm);
  EEPROM.get(8, pitch);
  EEPROM.get(12, coilWidth);
  EEPROM.get(16, wireDia);
  EEPROM.get(20, directionCW);

  if (turns <= 0) { // مقدار پیش‌فرض برای بار اول
    turns = 1200;
    rpm = 800;
    pitch = 0.3;
    coilWidth = 20.0;
    wireDia = 0.25;
    directionCW = true;
    saveSettings();
  }
}

bool buttonPressed(int pin) {
  if (digitalRead(pin) == LOW && millis() - lastPress > 200) {
    lastPress = millis();
    return true;
  }
  return false;
}

// ---------------- MENU DEFINITIONS -----------------

const char* mainMenuItems[] = {
  "Start",
  "Settings",
  "Manual",
  "Info"
};
const int mainMenuLength = sizeof(mainMenuItems) / sizeof(mainMenuItems[0]);

const char* settingsItems[] = {
  "Turns",
  "RPM",
  "Pitch",
  "Width",
  "Wire",
  "Direction",
  "Back"
};
const int settingsLength = sizeof(settingsItems) / sizeof(settingsItems[0]);

// ---------------- DISPLAY FUNCTIONS -----------------

void showMenu() {
  lcd.clear();

  switch (currentMenu) {

    case MENU_MAIN:
      for (int i = 0; i < 2; i++) {
        int idx = topIndex + i;
        if (idx >= mainMenuLength) break;
        lcd.setCursor(0, i);
        lcd.print(idx == selectedItem ? ">" : " ");
        lcd.print(mainMenuItems[idx]);
      }
      break;

    case MENU_SETTINGS:
      for (int i = 0; i < 2; i++) {
        int idx = topIndex + i;
        if (idx >= settingsLength) break;
        lcd.setCursor(0, i);
        lcd.print(idx == selectedItem ? ">" : " ");
        lcd.print(settingsItems[idx]);
      }
      break;

    case MENU_START:
      lcd.setCursor(0, 0);
      lcd.print("Start winding...");
      lcd.setCursor(0, 1);
      lcd.print("OK=Back");
      break;

    case MENU_MANUAL:
      lcd.setCursor(0, 0);
      lcd.print("Manual Mode");
      lcd.setCursor(0, 1);
      lcd.print("OK=Back");
      break;

    case MENU_INFO:
      lcd.setCursor(0, 0);
      lcd.print("Coil Winder v1.0");
      lcd.setCursor(0, 1);
      lcd.print("By Amir & GPT");
      break;

    case MENU_EDIT_TURNS:
      lcd.setCursor(0, 0);
      lcd.print("Turns: ");
      lcd.print(turns);
      lcd.setCursor(0, 1);
      lcd.print("OK=Save BACK");
      break;

    case MENU_EDIT_RPM:
      lcd.setCursor(0, 0);
      lcd.print("RPM: ");
      lcd.print(rpm);
      lcd.setCursor(0, 1);
      lcd.print("OK=Save BACK");
      break;

    case MENU_EDIT_PITCH:
      lcd.setCursor(0, 0);
      lcd.print("Pitch: ");
      lcd.print(pitch, 2);
      lcd.setCursor(0, 1);
      lcd.print("OK=Save BACK");
      break;

    case MENU_EDIT_WIDTH:
      lcd.setCursor(0, 0);
      lcd.print("Width: ");
      lcd.print(coilWidth, 1);
      lcd.setCursor(0, 1);
      lcd.print("OK=Save BACK");
      break;

    case MENU_EDIT_WIRE:
      lcd.setCursor(0, 0);
      lcd.print("Wire: ");
      lcd.print(wireDia, 2);
      lcd.setCursor(0, 1);
      lcd.print("OK=Save BACK");
      break;

    case MENU_EDIT_DIR:
      lcd.setCursor(0, 0);
      lcd.print("Dir: ");
      lcd.print(directionCW ? "CW" : "CCW");
      lcd.setCursor(0, 1);
      lcd.print("OK=Save BACK");
      break;
  }
}

// ---------------- SETUP -----------------

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_OK, INPUT_PULLUP);
  pinMode(BTN_BACK, INPUT_PULLUP);

  EEPROM.begin(64);
  loadSettings();

  showMenu();
}

// ---------------- LOOP -----------------

void loop() {

  // ---------- MAIN MENU ----------
  if (currentMenu == MENU_MAIN) {
    if (buttonPressed(BTN_UP)) {
      if (selectedItem > 0) {
        selectedItem--;
        if (selectedItem < topIndex) topIndex--;
        showMenu();
      }
    }
    if (buttonPressed(BTN_DOWN)) {
      if (selectedItem < mainMenuLength - 1) {
        selectedItem++;
        if (selectedItem > topIndex + 1) topIndex++;
        showMenu();
      }
    }
    if (buttonPressed(BTN_OK)) {
      switch (selectedItem) {
        case 0: currentMenu = MENU_START; break;
        case 1: currentMenu = MENU_SETTINGS; selectedItem = 0; topIndex = 0; break;
        case 2: currentMenu = MENU_MANUAL; break;
        case 3: currentMenu = MENU_INFO; break;
      }
      showMenu();
    }
  }

  // ---------- SETTINGS MENU ----------
  else if (currentMenu == MENU_SETTINGS) {
    if (buttonPressed(BTN_UP)) {
      if (selectedItem > 0) {
        selectedItem--;
        if (selectedItem < topIndex) topIndex--;
        showMenu();
      }
    }
    if (buttonPressed(BTN_DOWN)) {
      if (selectedItem < settingsLength - 1) {
        selectedItem++;
        if (selectedItem > topIndex + 1) topIndex++;
        showMenu();
      }
    }

    if (buttonPressed(BTN_OK)) {
      switch (selectedItem) {
        case 0: currentMenu = MENU_EDIT_TURNS; break;
        case 1: currentMenu = MENU_EDIT_RPM; break;
        case 2: currentMenu = MENU_EDIT_PITCH; break;
        case 3: currentMenu = MENU_EDIT_WIDTH; break;
        case 4: currentMenu = MENU_EDIT_WIRE; break;
        case 5: currentMenu = MENU_EDIT_DIR; break;
        case 6: currentMenu = MENU_MAIN; selectedItem = 0; topIndex = 0; break;
      }
      showMenu();
    }

    if (buttonPressed(BTN_BACK)) {
      currentMenu = MENU_MAIN;
      selectedItem = 0;
      topIndex = 0;
      showMenu();
    }
  }

  // ---------- EDITING MENUS ----------
  else if (currentMenu == MENU_EDIT_TURNS) {
    if (buttonPressed(BTN_UP)) { turns += 10; showMenu(); }
    if (buttonPressed(BTN_DOWN)) { turns = max(0, turns - 10); showMenu(); }
    if (buttonPressed(BTN_OK)) { saveSettings(); currentMenu = MENU_SETTINGS; showMenu(); }
    if (buttonPressed(BTN_BACK)) { currentMenu = MENU_SETTINGS; showMenu(); }
  }

  else if (currentMenu == MENU_EDIT_RPM) {
    if (buttonPressed(BTN_UP)) { rpm += 50; showMenu(); }
    if (buttonPressed(BTN_DOWN)) { rpm = max(0, rpm - 50); showMenu(); }
    if (buttonPressed(BTN_OK)) { saveSettings(); currentMenu = MENU_SETTINGS; showMenu(); }
    if (buttonPressed(BTN_BACK)) { currentMenu = MENU_SETTINGS; showMenu(); }
  }

  else if (currentMenu == MENU_EDIT_PITCH) {
    if (buttonPressed(BTN_UP)) { pitch += 0.01; showMenu(); }
    if (buttonPressed(BTN_DOWN)) { pitch = max(0.0f, pitch - 0.01f); showMenu(); }
    if (buttonPressed(BTN_OK)) { saveSettings(); currentMenu = MENU_SETTINGS; showMenu(); }
    if (buttonPressed(BTN_BACK)) { currentMenu = MENU_SETTINGS; showMenu(); }
  }

  else if (currentMenu == MENU_EDIT_WIDTH) {
    if (buttonPressed(BTN_UP)) { coilWidth += 0.5; showMenu(); }
    if (buttonPressed(BTN_DOWN)) { coilWidth = max(0.0f, coilWidth - 0.5f); showMenu(); }
    if (buttonPressed(BTN_OK)) { saveSettings(); currentMenu = MENU_SETTINGS; showMenu(); }
    if (buttonPressed(BTN_BACK)) { currentMenu = MENU_SETTINGS; showMenu(); }
  }

  else if (currentMenu == MENU_EDIT_WIRE) {
    if (buttonPressed(BTN_UP)) { wireDia += 0.01; showMenu(); }
    if (buttonPressed(BTN_DOWN)) { wireDia = max(0.0f, wireDia - 0.01f); showMenu(); }
    if (buttonPressed(BTN_OK)) { saveSettings(); currentMenu = MENU_SETTINGS; showMenu(); }
    if (buttonPressed(BTN_BACK)) { currentMenu = MENU_SETTINGS; showMenu(); }
  }

  else if (currentMenu == MENU_EDIT_DIR) {
    if (buttonPressed(BTN_UP) || buttonPressed(BTN_DOWN)) { directionCW = !directionCW; showMenu(); }
    if (buttonPressed(BTN_OK)) { saveSettings(); currentMenu = MENU_SETTINGS; showMenu(); }
    if (buttonPressed(BTN_BACK)) { currentMenu = MENU_SETTINGS; showMenu(); }
  }

  // ---------- OTHER MENUS ----------
  else {
    if (buttonPressed(BTN_BACK) || buttonPressed(BTN_OK)) {
      currentMenu = MENU_MAIN;
      selectedItem = 0;
      topIndex = 0;
      showMenu();
    }
  }
}
