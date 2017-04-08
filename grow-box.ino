
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "./src/settings.h"
//#include "./src/icons.h"
#include "./src/menu.h"
#include "./src/formatters.h"
#include "./src/sensors/TemperatureAndHumidity.h"
#include "./src/sensors/Joystick.h"
#include "./src/sensors/Clock.h"
#include "./src/devices/TimeIntervalSwitch.h"
#include "./src/devices/ScheduleIntervalSwitch.h"
#include "./src/devices/IntensityControl.h"
#include "./src/devices/Humidifier.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

Settings currentSettings;
const Settings defaultSettings = {
  2,
  { 20, 23 },
  65,
  { 4*60, 21*60 },
  { 0, 1*60 },
  { 0, 1*60 },
  700,
  700,
  0
};

// TODO add control
unsigned int humidityExcessPercentage = 0;


Joystick joystick(A0, A1);
TemperatureAndHumidity internalTemperatureAndHumidity( 10 );
Clock clock;

// Relays
ScheduleIntervalSwitch dwcAeration( 2, currentSettings.dwcAeration, clock );
ScheduleIntervalSwitch watering( 7, currentSettings.watering, clock );
unsigned char powerSupplyPin = 8;
TimeIntervalSwitch lightening( 9, currentSettings.lightening, clock );
Humidifier humidifier( 11, currentSettings.humidity, internalTemperatureAndHumidity.humidity );

IntensityControl airCirculation( A2, currentSettings.airCirculation, 30 );
IntensityControl airInflow( A3, humidityExcessPercentage );


void clearLcd() {
  lcd.clear();
}

void clearLcdAndSaveSettings() {
  lcd.clear();
  EEPROM.put( 0, currentSettings );
}


MenuController menuController(clearLcd, clearLcd);

void createMenu() {

  Menu *temperatureMenu = new Menu("Temperature   ", new MenuParameterController(clearLcd, clearLcdAndSaveSettings));
  temperatureMenu->controller->add(new MenuParameter("Day", currentSettings.temperature.day, to2Chars, "C "));
  temperatureMenu->controller->add(new MenuParameter("Night", currentSettings.temperature.night, to2Chars, "C"));
  menuController.add(temperatureMenu);
  
  Menu *humidityMenu = new Menu("Humidity      ", new MenuParameterController(clearLcd, clearLcdAndSaveSettings));
  humidityMenu->controller->add(new MenuParameter("", currentSettings.humidity, to2Chars, "%"));
  menuController.add(humidityMenu);
  
  Menu *lighteningMenu = new Menu("Lightening    ", new MenuParameterController(clearLcd, clearLcdAndSaveSettings));
  lighteningMenu->controller->add(new MenuParameter("", currentSettings.lightening.from, toTime, " - "));
  lighteningMenu->controller->add(new MenuParameter("", currentSettings.lightening.to, toTime, ""));
  menuController.add(lighteningMenu);
  
  Menu *wateringMenu = new Menu("Watering      ", new MenuParameterController(clearLcd, clearLcdAndSaveSettings));
  wateringMenu->controller->add(new MenuParameter("For", currentSettings.watering.enableFor, toPeriod, " "));
  wateringMenu->controller->add(new MenuParameter("Every", currentSettings.watering.period, toPeriod, ""));
  menuController.add(wateringMenu);
  
  Menu *dwcAerationMenu = new Menu("Aeration      ", new MenuParameterController(clearLcd, clearLcdAndSaveSettings));
  dwcAerationMenu->controller->add(new MenuParameter("For", currentSettings.dwcAeration.enableFor, toPeriod, " "));
  dwcAerationMenu->controller->add(new MenuParameter("Every", currentSettings.dwcAeration.period, toPeriod, ""));
  menuController.add(dwcAerationMenu);
  
  Menu *wateringSalinityMenu = new Menu("Watering Sal. ", new MenuParameterController(clearLcd, clearLcdAndSaveSettings));
  wateringSalinityMenu->controller->add(new MenuParameter("", currentSettings.wateringSalinity, to4Chars, "ppt"));
  menuController.add(wateringSalinityMenu);
  
  Menu *dwcSalinityMenu = new Menu("DWC Salinity  ", new MenuParameterController(clearLcd, clearLcdAndSaveSettings));
  dwcSalinityMenu->controller->add(new MenuParameter("", currentSettings.dwcSalinity, to4Chars, "ppt"));
  menuController.add(dwcSalinityMenu);
  
  Menu *airCirculationMenu = new Menu("Air circulat. ", new MenuParameterController(clearLcd, clearLcdAndSaveSettings));
  airCirculationMenu->controller->add(new MenuParameter("", currentSettings.airCirculation, to2Chars, "%"));
  menuController.add(airCirculationMenu);
  
//  Menu *timeMenu = new Menu("Current Time  ", new MenuParameterController(clearLcd, clearLcdAndSaveSettings));
//  timeMenu->controller->add(new MenuParameter("", clock.dateTime, toTime, ""));
//  menuController.add(timeMenu);
}

void printMenu() {
  lcd.home();
  lcd.print(">" + menuController.items[menuController.selectedIndex]->name);
  
  unsigned char nextMenuItemIndex = menuController.selectedIndex + 1;
  if (nextMenuItemIndex >= menuController.itemsCount ) {
    nextMenuItemIndex = 0;
  }
  lcd.setCursor(1, 1);
  lcd.print(menuController.items[nextMenuItemIndex]->name);
};

void printParameters() {
  lcd.home();
  lcd.print(" " + menuController.items[menuController.selectedIndex]->name);
  lcd.setCursor(1, 1);
  Menu *item = menuController.items[menuController.selectedIndex];
  
  for (int i=0; i < item->controller->itemsCount; i++) {
    MenuParameter *param = item->controller->items[i];
    
    lcd.print(param->textBefore + param->valueFormatter(param->value) + param->textAfter);
  }
}

//void printDeviceIcon(const char *icon, boolean isEnabled) {
//  lcd.print(isEnabled ? icon : " ");
//}

void printMainScreen() {
  lcd.home();
  lcd.print(airCirculation.isEnabled ? "C" : " ");
  lcd.print(lightening.isEnabled ? "L" : " ");
  lcd.print(watering.isEnabled ? "W" : " ");
  lcd.print(dwcAeration.isEnabled ? "A" : " ");
  lcd.print(humidifier.isEnabled ? "H" : " ");
  lcd.print(" " + toTime(clock.getIntTime()));
  lcd.print(" " + to2Chars(currentSettings.airCirculation));
  
  lcd.setCursor(0, 1);
  lcd.print("h" + to2Chars(internalTemperatureAndHumidity.humidity) + "% ");
  lcd.print("t" + to2Chars(internalTemperatureAndHumidity.temperature) + "C ");
  lcd.print(" " + to2Chars(airCirculation.getPinValue()));
}

void updateScreen() {
  if(menuController.isActive) {
    if (menuController.hasActiveController()) {
      printParameters();
    } else {
      printMenu();
    }
  } else {
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
  createMenu();
  
  initSensorsAndDevices();
}

void loop() {
  updateSensors();
  
  if (joystick.direction != Center) {
    menuController.navigate(joystick.direction);
  }
  
  updateScreen();
  updateDevices();
}
