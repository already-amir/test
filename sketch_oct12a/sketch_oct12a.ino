
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// دکمه‌ها (GPIO های پیشنهادی؛ می‌تونی تغییر بدی)
const int BTN_UP_PIN    = 12;
const int BTN_DOWN_PIN  = 13;
const int BTN_ENTER_PIN = 14;
const int BTN_BACK_PIN  = 27;

// پین‌های استپر (مثال)
const int STEP_PIN = 25;
const int DIR_PIN  = 26;
const int ENABLE_PIN = 27; // اگر درایور داری، فعال/غیرفعال کن

// ====== پارامترهای پیش‌فرض ======
volatile long currentTurns = 0;
long targetTurns = 1200;      // تعداد دور هدف (قابل تنظیم)
int rpmTarget = 120;          // دور بر دقیقه هدف
float pitch_mm = 0.5;         // گام هد (اختیاری)
int stepsPerTurn = 200;       // تعداد step برای یک دور از سیم‌پیچ (بسته به گیربکس / موتور)
bool isRunning = false;
bool isPaused = false;

// برای لاگ ساده
struct RunLog {
  unsigned long startTime;
  unsigned long endTime;
  long turnsDone;
  bool completed;
};
#define MAX_LOGS 10
RunLog logs[MAX_LOGS];
int logIndex = 0;

// حالت‌های منو
enum MenuState {
  MENU_MAIN,
  MENU_START,
  MENU_SETTINGS,
  MENU_SETTINGS_TURNS,
  MENU_SETTINGS_RPM,
  MENU_SETTINGS_PITCH,
  MENU_MANUAL,
  MENU_RUNNING,
  MENU_LOGS,
  MENU_EDITING
};
MenuState menu = MENU_MAIN;

// برای ویرایش عددی
long editValue = 0;

// دِبانس ساده دکمه‌ها
unsigned long lastDebounce[4] = {0,0,0,0};
const unsigned long debounceDelay = 50;
bool lastBtnState[4] = {HIGH, HIGH, HIGH, HIGH};

// برای پالس‌دهی استپر (non-blocking)
unsigned long lastStepTime_us = 0;
unsigned long stepInterval_us = 1000; // مقدار اولیه؛ تغییر می‌کند با RPM
volatile long stepCount = 0; // شمارش step کلی
int dirNow = 1; // 1 یا 0

// helper برای خواندن دکمه با دِبانس
bool readButtonRaw(int pin) {
  return digitalRead(pin) == LOW; // چون INPUT_PULLUP استفاده میکنیم، LOW = pressed
}
bool readButtonDebounced(int idx, int pin) {
  bool reading = readButtonRaw(pin);
  unsigned long now = millis();
  if (reading != (lastBtnState[idx]==LOW)) {
    lastDebounce[idx] = now;
    lastBtnState[idx] = reading ? LOW : HIGH;
  }
  if ((now - lastDebounce[idx]) > debounceDelay) {
    return reading;
  }
  return false;
}

// نمایشگر: چاپ دو خط (هر خط حداکثر 16)
void lcdLine(int row, const String &s) {
  lcd.setCursor(0, row);
  String tmp = s;
  if (tmp.length() < 16) {
    // پر کردن با فاصله
    while (tmp.length() < 16) tmp += ' ';
  } else if (tmp.length() > 16) {
    tmp = tmp.substring(0, 16);
  }
  lcd.print(tmp);
}

// به‌روز کردن interval بر اساس rpmTarget و stepsPerTurn
void updateStepInterval() {
  if (rpmTarget <= 0 || stepsPerTurn <= 0) {
    stepInterval_us = 1000000;
    return;
  }
  // هر دور = stepsPerTurn step
  // rpm => rev/min => rev/s = rpm/60
  // steps per second = rev/s * stepsPerTurn
  // interval_us = 1e6 / steps_per_second
  double steps_per_sec = (double)rpmTarget / 60.0 * (double)stepsPerTurn;
  if (steps_per_sec <= 0.000001) stepInterval_us = 1000000;
  else stepInterval_us = (unsigned long)(1000000.0 / steps_per_sec);
}

// لاگ جدید اضافه کن
void addLog(unsigned long s, unsigned long e, long turns, bool completed) {
  logs[logIndex].startTime = s;
  logs[logIndex].endTime = e;
  logs[logIndex].turnsDone = turns;
  logs[logIndex].completed = completed;
  logIndex = (logIndex + 1) % MAX_LOGS;
}

// شروع/توقف موتور (ساده)
void motorEnable(bool en) {
  if (ENABLE_PIN >= 0) digitalWrite(ENABLE_PIN, en ? LOW : HIGH); // فرضا LOW = enable
}
void motorSetDir(bool forward) {
  dirNow = forward ? 1 : 0;
  digitalWrite(DIR_PIN, forward ? HIGH : LOW);
}
void motorStepPulse() {
  // یک پالس STEP (تک پالس)
  digitalWrite(STEP_PIN, HIGH);
  // کوتاه یک تا چند میکرو
  delayMicroseconds(2);
  digitalWrite(STEP_PIN, LOW);
}

// شروع پروسه پیچش
unsigned long runStartMillis = 0;
void startWinding() {
  if (isRunning) return;
  isRunning = true;
  isPaused = false;
  stepCount = 0;
  currentTurns = 0;
  runStartMillis = millis();
  updateStepInterval();
  motorEnable(true);
  motorSetDir(true); // جهت پیش‌فرض
}

// توقف نرم
void stopWinding(bool completed=false) {
  if (!isRunning) return;
  isRunning = false;
  isPaused = false;
  motorEnable(false);
  unsigned long endTime = millis();
  addLog(runStartMillis, endTime, currentTurns, completed);
}

// ادامه/مکث
void togglePause() {
  if (!isRunning) return;
  isPaused = !isPaused;
  motorEnable(!isPaused);
}

// نمایش منوی اصلی
void showMainMenu(int cursor) {
  // cursor: 0..n
  if (cursor == 0) lcdLine(0, ">Start winding    ");
  else lcdLine(0, " Start winding    ");
  if (cursor == 1) lcdLine(1, (cursor==1?">Settings        ":" Settings         "));
  else if (cursor == 2) lcdLine(1, (cursor==2?">Manual move     ":" Manual move      "));
  // وقتی فقط 2 ردیف داریم، برای نمایش سایر آیتم‌ها از back/next استفاده می‌کنیم
}

// نمایش وضعیت در حالت RUNNING یا STOP
void showStatus() {
  // خط اول: RPM:xxx Turn:yyyy
  char buf1[17];
  snprintf(buf1,16,"RPM:%03d Turn:%04ld", rpmTarget, currentTurns);
  lcdLine(0, String(buf1));
  // خط دوم: T:0.8N Run► یا Stop■
  String st = (isRunning ? "Run►" : "Stop■");
  char buf2[17];
  snprintf(buf2,16,"T:%.2f %s", pitch_mm, st.c_str());
  lcdLine(1, String(buf2));
}

// صفحه ویرایش عدد ساده (name + value)
void showEditPage(const String &name, long value) {
  String l1 = name;
  while (l1.length() < 16) l1 += ' ';
  lcdLine(0, l1);
  char vbuf[16];
  snprintf(vbuf, 16, "Set:%10ld", value);
  lcdLine(1, String(vbuf));
}

void setup() {
  // init pins
  pinMode(BTN_UP_PIN, INPUT_PULLUP);
  pinMode(BTN_DOWN_PIN, INPUT_PULLUP);
  pinMode(BTN_ENTER_PIN, INPUT_PULLUP);
  pinMode(BTN_BACK_PIN, INPUT_PULLUP);

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  if (ENABLE_PIN >= 0) pinMode(ENABLE_PIN, OUTPUT);

  digitalWrite(STEP_PIN, LOW);
  digitalWrite(DIR_PIN, LOW);
  if (ENABLE_PIN >= 0) digitalWrite(ENABLE_PIN, HIGH); // disabled initially

  Serial.begin(115200);
  Wire.begin(); // use default SDA/SCL (21/22)

  lcd.init();
  lcd.backlight();

  updateStepInterval();
  showStatus();
  delay(400);
  lcdLine(0,"  Coil Winder     ");
  lcdLine(1," Press ENTER      ");
  delay(800);
}

// متغیر کمکی برای منو و ویرایش
int mainCursor = 0;
int mainMenuPage = 0; // اگر آیتم‌ها بیشتر بود
int settingsCursor = 0;

bool lastEnter = false;
bool lastBack = false;

unsigned long lastUiUpdate = 0;
const unsigned long UI_REFRESH_MS = 200;

// تابع برای پردازش stepها (باید در loop فراخوانی شود)
void stepperService() {
  if (!isRunning || isPaused) return;

  unsigned long now_us = micros();
  if (now_us - lastStepTime_us >= stepInterval_us) {
    // یک step
    lastStepTime_us = now_us;
    motorStepPulse();
    stepCount++;
    // هر stepsPerTurn step = 1 turn
    if (stepCount >= stepsPerTurn) {
      stepCount = 0;
      currentTurns++;
      // اگر رسیدیم به هدف -> stop
      if (currentTurns >= targetTurns) {
        stopWinding(true);
      }
    }
  }
}

void loop() {
  // خواندن دکمه‌ها (دِبانس ساده)
  bool btnUp = readButtonDebounced(0, BTN_UP_PIN);
  bool btnDown = readButtonDebounced(1, BTN_DOWN_PIN);
  bool btnEnter = readButtonDebounced(2, BTN_ENTER_PIN);
  bool btnBack = readButtonDebounced(3, BTN_BACK_PIN);

  // === در حالت اجرای پیچش، دکمه‌ها نقش توقف/مکث دارند ===
  if (isRunning) {
    // ENTER toggles pause, BACK stops
    if (btnEnter && !lastEnter) {
      togglePause();
    }
    if (btnBack && !lastBack) {
      stopWinding(false);
    }
    lastEnter = btnEnter;
    lastBack = btnBack;
    // سرویس stepper (non-blocking)
    stepperService();
    // نمایش وضعیت هر UI_REFRESH_MS میلی‌ثانیه
    if (millis() - lastUiUpdate > UI_REFRESH_MS) {
      lastUiUpdate = millis();
      // نمایش پیشرفت: خط اول RPM/Turn، خط دوم درصد یا tension
      char buf1[17];
      snprintf(buf1,16,"RPM:%03d Turn:%04ld", rpmTarget, currentTurns);
      lcdLine(0, String(buf1));
      // درصد
      int pct = (targetTurns>0) ? (int)((currentTurns * 100) / targetTurns) : 0;
      char buf2[17];
      snprintf(buf2,16,"Prog:%3d%% T:%.2f", pct, pitch_mm);
      lcdLine(1, String(buf2));
    }
    return;
  }

  // وقتی در منو هستیم (isRunning == false)
  // منوی اصلی
  switch (menu) {
    case MENU_MAIN:
      if (millis() - lastUiUpdate > 200) {
        lastUiUpdate = millis();
        // نمایش: دو گزینه همزمان (cursor روی یکی)
        // خط اول = گزینه بالا یا انتخاب
        // خط دوم = گزینه بعدی یا وضعیت
        if (mainCursor == 0) {
          lcdLine(0, ">Start winding    ");
          lcdLine(1, " Settings         ");
        } else if (mainCursor == 1) {
          lcdLine(0, " Start winding    ");
          lcdLine(1, ">Settings         ");
        } else if (mainCursor == 2) {
          lcdLine(0, " Manual move      ");
          lcdLine(1, " Logs             ");
        } else if (mainCursor == 3) {
          lcdLine(0, " Manual move      ");
          lcdLine(1, ">Logs             ");
        }
      }
      // ناوبری
      if (btnUp && !lastBtnState[0]) {
        mainCursor = (mainCursor - 1 + 4) % 4;
      }
      if (btnDown && !lastBtnState[1]) {
        mainCursor = (mainCursor + 1) % 4;
      }
      if (btnEnter && !lastEnter) {
        // انتخاب
        if (mainCursor == 0) menu = MENU_START;
        else if (mainCursor == 1) menu = MENU_SETTINGS;
        else if (mainCursor == 2) menu = MENU_MANUAL;
        else if (mainCursor == 3) menu = MENU_LOGS;
      }
      if (btnBack && !lastBack) {
        // کاری ندارد، شاید نمایش وضعیت
        showStatus();
      }
      break;

    case MENU_START:
      // صفحه تایید و شروع
      if (millis() - lastUiUpdate > 200) {
        lastUiUpdate = millis();
        char buf1[17];
        snprintf(buf1,16,"Start: %ld turns", targetTurns);
        lcdLine(0, String(buf1));
        lcdLine(1, "Enter=Start Back=Esc");
      }
      if (btnEnter && !lastEnter) {
        startWinding();
        menu = MENU_RUNNING;
      }
      if (btnBack && !lastBack) {
        menu = MENU_MAIN;
      }
      break;

    case MENU_SETTINGS:
      // نمایش سریع پارامترها؛ با UP/DOWN انتخاب، ENTER برای ویرایش
      if (millis() - lastUiUpdate > 200) {
        lastUiUpdate = millis();
        if (settingsCursor == 0) {
          char b1[17]; snprintf(b1,16,"Turns:%8ld", targetTurns);
          lcdLine(0,String(b1));
          lcdLine(1,">RPM          Back");
        } else if (settingsCursor == 1) {
          char b1[17]; snprintf(b1,16,"RPM:%10d", rpmTarget);
          lcdLine(0,String(b1));
          lcdLine(1,">Pitch(mm)    Back");
        } else if (settingsCursor == 2) {
          char b1[17]; snprintf(b1,16,"Pitch:%.2f mm", pitch_mm);
          lcdLine(0,String(b1));
          lcdLine(1," Back             ");
        }
      }
      if (btnUp && !lastBtnState[0]) {
        settingsCursor = (settingsCursor - 1 + 3) % 3;
      }
      if (btnDown && !lastBtnState[1]) {
        settingsCursor = (settingsCursor + 1) % 3;
      }
      if (btnEnter && !lastEnter) {
        if (settingsCursor == 0) {
          editValue = targetTurns;
          menu = MENU_SETTINGS_TURNS;
        } else if (settingsCursor == 1) {
          editValue = rpmTarget;
          menu = MENU_SETTINGS_RPM;
        } else if (settingsCursor == 2) {
          // pitch edit as integer *100
          editValue = (long)(pitch_mm * 100.0);
          menu = MENU_SETTINGS_PITCH;
        }
      }
      if (btnBack && !lastBack) {
        menu = MENU_MAIN;
      }
      break;

    case MENU_SETTINGS_TURNS:
      // ویرایش targetTurns با UP/DOWN و ENTER ذخیره و BACK لغو
      showEditPage("Turns:", editValue);
      if (btnUp && !lastBtnState[0]) {
        editValue += 10;
        if (editValue < 0) editValue = 0;
      }
      if (btnDown && !lastBtnState[1]) {
        editValue -= 10;
        if (editValue < 0) editValue = 0;
      }
      if (btnEnter && !lastEnter) {
        targetTurns = editValue;
        menu = MENU_SETTINGS;
      }
      if (btnBack && !lastBack) {
        menu = MENU_SETTINGS;
      }
      break;

    case MENU_SETTINGS_RPM:
      showEditPage("RPM:", editValue);
      if (btnUp && !lastBtnState[0]) {
        editValue += 1;
      }
      if (btnDown && !lastBtnState[1]) {
        editValue -= 1;
        if (editValue < 1) editValue = 1;
      }
      if (btnEnter && !lastEnter) {
        rpmTarget = (int)editValue;
        updateStepInterval();
        menu = MENU_SETTINGS;
      }
      if (btnBack && !lastBack) {
        menu = MENU_SETTINGS;
      }
      break;

    case MENU_SETTINGS_PITCH:
      showEditPage("Pitch*100:", editValue);
      if (btnUp && !lastBtnState[0]) {
        editValue += 1;
      }
      if (btnDown && !lastBtnState[1]) {
        editValue -= 1;
        if (editValue < 1) editValue = 1;
      }
      if (btnEnter && !lastEnter) {
        pitch_mm = ((float)editValue) / 100.0;
        menu = MENU_SETTINGS;
      }
      if (btnBack && !lastBack) {
        menu = MENU_SETTINGS;
      }
      break;

    case MENU_MANUAL:
      // محتوای ساده: jog left/right با UP/DOWN و ENTER برای step/rotate
      if (millis() - lastUiUpdate > 200) {
        lastUiUpdate = millis();
        lcdLine(0, "Manual Move       ");
        lcdLine(1, "Up:+1 Turn Dn:-1  ");
      }
      if (btnUp && !lastBtnState[0]) {
        // حرکت یک دور جلو
        // برای دمو: فقط افزایش شمارش دور
        currentTurns++;
        lcdLine(0, "Manual:+1 turn    ");
        delay(200);
      }
      if (btnDown && !lastBtnState[1]) {
        if (currentTurns > 0) currentTurns--;
        lcdLine(0, "Manual:-1 turn    ");
        delay(200);
      }
      if (btnBack && !lastBack) {
        menu = MENU_MAIN;
      }
      break;

    case MENU_LOGS:
      // نمایش آخرین لاگ (ساده)
      {
        int idx = (logIndex - 1 + MAX_LOGS) % MAX_LOGS;
        RunLog &r = logs[idx];
        if (r.startTime == 0 && r.endTime == 0 && r.turnsDone == 0) {
          lcdLine(0, "No logs yet       ");
          lcdLine(1, "Back to menu      ");
        } else {
          // نمایش خلاصه: turns + dur(s)
          unsigned long dur_s = (r.endTime - r.startTime) / 1000;
          char b1[17]; snprintf(b1,16,"Turns:%04ld Dur:%lus", r.turnsDone, dur_s);
          lcdLine(0, String(b1));
          lcdLine(1, r.completed ? "Completed         " : "Stopped           ");
        }
      }
      if (btnBack && !lastBack) {
        menu = MENU_MAIN;
      }
      break;

    default:
      menu = MENU_MAIN;
      break;
  }

  // ذخیره وضعیت دکمه‌ها به عنوان last
  lastBtnState[0] = readButtonRaw(BTN_UP_PIN) ? LOW : HIGH;
  lastBtnState[1] = readButtonRaw(BTN_DOWN_PIN) ? LOW : HIGH;
  lastEnter = readButtonRaw(BTN_ENTER_PIN);
  lastBack = readButtonRaw(BTN_BACK_PIN);

  // هر بار UI refresher کلی
  if (millis() - lastUiUpdate > 500) {
    lastUiUpdate = millis();
    if (!isRunning) showStatus();
  }

  // سرویس stepper در صورت نیاز (اگر به صورت کلی loop طولانی بشه)
  stepperService();
}
