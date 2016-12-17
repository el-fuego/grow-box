
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "./settings.h"
#include "./icons.h"
#include "./menu.h"
#include "./formatters.h"
#include "./sensors/TemperatureAndHumidity.h"
#include "./sensors/Joystick.h"
#include "./sensors/Clock.h"
#include "./devices/TimeIntervalSwitch.h"
#include "./devices/ScheduleIntervalSwitch.h"
#include "./devices/IntensityControl.h"
#include "./devices/Humidifier.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

Settings currentSettings;
const Settings defaultSettings = {
  2,
  { 18, 20 },
  70,
  { 7*60, 22*60 },
  { 10, 1*60 },
  { 5, 1*60 },
  700,
  700,
  5
};

// TODO add control
unsigned int humidityExcessPercentage = 0;


Joystick joystick(A0, A1);
TemperatureAndHumidity internalTemperatureAndHumidity( 10 );
Clock clock;

// Relays
ScheduleIntervalSwitch dwcAeration( 2, currentSettings.dwcAeration, clock );
ScheduleIntervalSwitch watering( 3, currentSettings.watering, clock );
unsigned char powerSupplyPin = 4;
TimeIntervalSwitch lightening( 5, currentSettings.lightening, clock );
Humidifier humidifier( 11, currentSettings.humidity, internalTemperatureAndHumidity.humidity );

IntensityControl airCirculation( A2, currentSettings.airCirculation, 30 );
IntensityControl airInflow( A3, humidityExcessPercentage );

const MenuParameter temperatureParameters[] = {
  {"Day", currentSettings.temperature.day, to2Chars, "C "},
  {"Night", currentSettings.temperature.night, to2Chars, "C"}
};
const MenuParameter humidityParameters[] = {
  {"", currentSettings.humidity, to2Chars, "%"}
};
const MenuParameter lighteningParameters[] = {
  {"", currentSettings.lightening.from, toTime, " - "},
  {"", currentSettings.lightening.to, toTime, ""}
};
const MenuParameter wateringParameters[] = {
  {"For", currentSettings.watering.enableFor, toPeriod, " "},
  {"Every", currentSettings.watering.period, toPeriod, ""}
};
const MenuParameter dwcAerationParameters[] = {
  {"For", currentSettings.dwcAeration.enableFor, toPeriod, " "},
  {"Every", currentSettings.dwcAeration.period, toPeriod, ""}
};
const MenuParameter wateringSalinityParameters[] = {
  {"", currentSettings.wateringSalinity, to4Chars, "ppt"}
};
const MenuParameter dwcSalinityParameters[] = {
  {"", currentSettings.dwcSalinity, to4Chars, "ppt"}
};
const MenuParameter airCirculationParameters[] = {
  {"", currentSettings.airCirculation, to2Chars, "%"}
};
//const MenuParameter currentTimeParameters[] = {
//  {"", clock.dateTime, toTime, ""}
//};

const Menu menu[] = {
  {"Temperature   ", 2, temperatureParameters},
  {"Humidity      ", 1, humidityParameters},
  {"Lightening    ", 2, lighteningParameters},
  {"Watering      ", 2, wateringParameters},
  {"Aeration      ", 2, dwcAerationParameters},
  {"Watering Sal. ", 1, wateringSalinityParameters},
  {"DWC Salinity  ", 1, dwcSalinityParameters},
  {"Air circulat. ", 1, airCirculationParameters}
//  {"Current Time  ", 1, currentTimeParameters}
};

const unsigned char MENU_ITEMS_COUNT = sizeof(menu) / sizeof(*menu);

enum Modes { MainScreen, MenuSelection, ParameterEditing };
Modes mode = MainScreen;


unsigned char selectedMenuItemIndex = 0;
unsigned char selectedParameterIndex = 0;
void printMenu() {
  lcd.home();
  lcd.print(">" + menu[selectedMenuItemIndex].text);
  
  unsigned char nextMenuItemIndex = selectedMenuItemIndex + 1;
  if (nextMenuItemIndex >= MENU_ITEMS_COUNT ) {
    nextMenuItemIndex = 0;
  }
  lcd.setCursor(1, 1);
  lcd.print(menu[nextMenuItemIndex].text);
};

void printParamaters() {
  lcd.home();
  lcd.print(" " + menu[selectedMenuItemIndex].text);
  lcd.setCursor(1, 1);
  Menu item = menu[selectedMenuItemIndex];
  
  for (int i=0; i < item.parametersCount; i++) {
    MenuParameter param = item.pParameters[i];
    
    lcd.print(param.textBefore + param.valueFormatter(param.value) + param.textAfter);
  }
}

void printDeviceIcon(const char *icon, boolean isEnabled) {
  lcd.print(isEnabled ? icon : " ");
}

void printMainScreen() {
  lcd.home();
  lcd.print(airCirculation.isEnabled ? "C" : " ");
  lcd.print(lightening.isEnabled ? "L" : " ");
  lcd.print(watering.isEnabled ? "W" : " ");
  lcd.print(dwcAeration.isEnabled ? "A" : " ");
  lcd.print(humidifier.isEnabled ? "H" : " ");
  lcd.print(" " + toTime(clock.getIntTime()) + " ");
  lcd.print(" " + to4Chars(currentSettings.airCirculation));
  
  lcd.setCursor(0, 1);
  lcd.print("h" + to2Chars(internalTemperatureAndHumidity.humidity) + "% ");
  lcd.print("t" + to2Chars(internalTemperatureAndHumidity.temperature) + "C ");
  lcd.print(" " + to4Chars(airCirculation.getPinValue()));
}


void selectPrevMenu() {
  if (selectedMenuItemIndex == 0) {
    selectedMenuItemIndex = MENU_ITEMS_COUNT - 1;
  } else {
    selectedMenuItemIndex--;
  }
}

void selectNextMenu() {
  selectedMenuItemIndex++;
  if (selectedMenuItemIndex >= MENU_ITEMS_COUNT) {
    selectedMenuItemIndex = 0;
  }
}

void exitMenu() {
  mode = MainScreen;
  selectedMenuItemIndex = 0;
  lcd.clear();
}

void enterMenuSelection() {
  mode = MenuSelection;
  selectedParameterIndex = 0;
  lcd.clear();
  EEPROM.put( 0, currentSettings );
}

void enterParametersEditing() {
  mode = ParameterEditing;
  lcd.clear();
}

void navigateBetweenMenus(unsigned char button) {
  switch(button) {  
    case Up:
      selectPrevMenu();
      break;
    case Down:
      selectNextMenu();
      break;
    case Left:
      exitMenu();
      break;
    case Right:
      enterParametersEditing();
      break;
  }
}

void selectPrevParameter() {
  selectedParameterIndex--;
}

void selectNextParameter() {
  if (selectedParameterIndex < menu[selectedMenuItemIndex].parametersCount - 1) {
    selectedParameterIndex++;
  }
}

void increaseParameterValue() {
  menu[selectedMenuItemIndex].pParameters[selectedParameterIndex].value++;
}

void decreaseParameterValue() {
  if (menu[selectedMenuItemIndex].pParameters[selectedParameterIndex].value > 0) {
    menu[selectedMenuItemIndex].pParameters[selectedParameterIndex].value--;
  }
}

void navigateBetweenParameters(unsigned char button) {
  switch(button) {  
    case Up:
      increaseParameterValue();
      break;
    case Down:
      decreaseParameterValue();
      break;
    case Left:
      if (selectedParameterIndex == 0) {
        enterMenuSelection();
      } else {
        selectPrevParameter();
      }
      break;
    case Right:
      selectNextParameter();
      break;
  }
}


void navigate(unsigned char button) {
  switch(mode) {  
    case MenuSelection:
      navigateBetweenMenus(button);
      break;
    case ParameterEditing:
      navigateBetweenParameters(button);
      break;
    default:
      enterMenuSelection();
  }
}

void updateScreen() {
  switch(mode) {  
    case MenuSelection:
      printMenu();
      break;
    case ParameterEditing:
      printParamaters();
      break;
    default:
      printMainScreen();
  }
}


void updateDevices() {
  lightening.update();
  watering.update();
  dwcAeration.update();
  humidifier.update();
}

void updateSensors() {
  joystick.update();
  internalTemperatureAndHumidity.update();
  clock.update();
}

void loadSettings() {
  EEPROM.get( 0, currentSettings );
  
  if (currentSettings.structVersion != defaultSettings.structVersion) {
    EEPROM.put( 0, defaultSettings );
    currentSettings = defaultSettings;
  }
}

void turnPowerOn() {
  pinMode(powerSupplyPin, OUTPUT);
  digitalWrite(powerSupplyPin, LOW);
}

void initSensorsAndDevices() {
  joystick.init();
  internalTemperatureAndHumidity.init();
  clock.init();
  
  lightening.init();
  watering.init();
  dwcAeration.init();
  humidifier.init();
}

void setup() {
  Wire.begin();
  
  lcd.init();
  lcd.backlight();
  
  loadSettings();
  initSensorsAndDevices();

  turnPowerOn();
}

void loop() {
  updateSensors();
  
  if (joystick.direction != Center) {
    navigate(joystick.direction);
  }
  
  updateScreen();
  updateDevices();
}
