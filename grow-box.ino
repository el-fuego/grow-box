
#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "./src/settings.h"
//#include "./src/icons.h"
#include "./src/menu/MenuItem.h"
#include "./src/menu/Menu.h"
#include "./src/menu/Parameter.h"
#include "./src/menu/Parameters.h"
#include "./src/formatters.h"
#include "./src/sensors/TemperatureAndHumidity.h"
#include "./src/sensors/Joystick.h"
#include "./src/sensors/Clock.h"
#include "./src/devices/TimeIntervalSwitch.h"
#include "./src/devices/ScheduleIntervalSwitch.h"
#include "./src/devices/IntensityControl.h"
#include "./src/devices/relay/TurnOnWhenHigher.h"
#include "./src/devices/relay/TurnOnWhenLower.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

Settings currentSettings;
const Settings defaultSettings = {
  2,
  { 20, 23 },
  55,
  { 5*60, 21*60 },
  { 0, 1*60 },
  { 0, 1*60 },
  700,
  700,
  0
};

Joystick joystick(A0, A1);
TemperatureAndHumidity internalTemperatureAndHumidity( 10 );
Clock clock;

// Relays
ScheduleIntervalSwitch dwcAeration( 2, currentSettings.dwcAeration, clock );
ScheduleIntervalSwitch watering( 7, currentSettings.watering, clock );
unsigned char powerSupplyPin = 8;
TimeIntervalSwitch lightening( 9, currentSettings.lightening, clock );
TurnOnWhenLower humidifier( 11, currentSettings.humidity, internalTemperatureAndHumidity.humidity );
TurnOnWhenHigher airInflow( 12, currentSettings.humidity, internalTemperatureAndHumidity.humidity );

IntensityControl airCirculation( A2, currentSettings.airCirculation, 30 );


void clearLcd() {
  lcd.clear();
}

void clearLcdAndSaveSettings() {
  lcd.clear();
  EEPROM.put( 0, currentSettings );
}


Menu menu(clearLcd, clearLcd);

void createMenu() {
  MenuItem* temperature = new MenuItem("Temperature   ", new Parameters(clearLcd, clearLcdAndSaveSettings));
  temperature->parameters->add(new Parameter("Day", currentSettings.temperature.day, to2Chars, "C "));
  temperature->parameters->add(new Parameter("Night", currentSettings.temperature.night, to2Chars, "C"));
  menu.add(temperature);
  
  MenuItem* humidity = new MenuItem("Humidity      ", new Parameters(clearLcd, clearLcdAndSaveSettings));
  humidity->parameters->add(new Parameter("", currentSettings.humidity, to2Chars, "%"));
  menu.add(humidity);
  
  MenuItem* lightening = new MenuItem("Lightening    ", new Parameters(clearLcd, clearLcdAndSaveSettings));
  lightening->parameters->add(new Parameter("", currentSettings.lightening.from, toTime, " - "));
  lightening->parameters->add(new Parameter("", currentSettings.lightening.to, toTime, ""));
  menu.add(lightening);
  
  MenuItem* watering = new MenuItem("Watering      ", new Parameters(clearLcd, clearLcdAndSaveSettings));
  watering->parameters->add(new Parameter("For", currentSettings.watering.enableFor, toPeriod, " "));
  watering->parameters->add(new Parameter("Every", currentSettings.watering.period, toPeriod, ""));
  menu.add(watering);
  
  MenuItem* dwcAeration = new MenuItem("Aeration      ", new Parameters(clearLcd, clearLcdAndSaveSettings));
  dwcAeration->parameters->add(new Parameter("For", currentSettings.dwcAeration.enableFor, toPeriod, " "));
  dwcAeration->parameters->add(new Parameter("Every", currentSettings.dwcAeration.period, toPeriod, ""));
  menu.add(dwcAeration);
  
  MenuItem* wateringSalinity = new MenuItem("Watering Sal. ", new Parameters(clearLcd, clearLcdAndSaveSettings));
  wateringSalinity->parameters->add(new Parameter("", currentSettings.wateringSalinity, to4Chars, "ppt"));
  menu.add(wateringSalinity);
  
  MenuItem* dwcSalinity = new MenuItem("DWC Salinity  ", new Parameters(clearLcd, clearLcdAndSaveSettings));
  dwcSalinity->parameters->add(new Parameter("", currentSettings.dwcSalinity, to4Chars, "ppt"));
  menu.add(dwcSalinity);
  
  MenuItem* airCirculation = new MenuItem("Air circulat. ", new Parameters(clearLcd, clearLcdAndSaveSettings));
  airCirculation->parameters->add(new Parameter("", currentSettings.airCirculation, to2Chars, "%"));
  menu.add(airCirculation);
  
//  MenuItem* time = new MenuItem("Current Time  ", new Parameters(clearLcd, clearLcdAndSaveSettings));
//  time->parameters->add(new Parameter("", clock.dateTime, toTime, ""));
//  menu.add(time);
}

void printMenu() {
  lcd.home();
  lcd.print(">" + menu.get(menu.selectedIndex)->name);
  
  unsigned char nextMenuItemIndex = menu.selectedIndex + 1;
  if (nextMenuItemIndex >= menu.itemsCount ) {
    nextMenuItemIndex = 0;
  }
  lcd.setCursor(1, 1);
  lcd.print(menu.get(nextMenuItemIndex)->name);
};

void printParameters() {
  lcd.home();
  lcd.print(" " + menu.get(menu.selectedIndex)->name);
  lcd.setCursor(1, 1);
  MenuItem* item = menu.get(menu.selectedIndex);
  
  for (int i=0; i < item->parameters->itemsCount; i++) {
    Parameter* param = item->parameters->get(i);
    
    lcd.print(param->textBefore + param->valueFormatter(param->value) + param->textAfter);
  }
}

//void printDeviceIcon(const char* icon, boolean isEnabled) {
//  lcd.print(isEnabled ? icon : " ");
//}

void printMainScreen() {
  lcd.home();
  lcd.print(airCirculation.isEnabled ? "C" : " ");
  lcd.print(lightening.isEnabled ? "L" : " ");
  lcd.print(watering.isEnabled ? "W" : " ");
  lcd.print(dwcAeration.isEnabled ? "A" : " ");
  lcd.print(humidifier.isEnabled ? "H" : (airInflow.isEnabled ? "I" : " "));
  lcd.print(" " + toTime(clock.getIntTime()));
  
  lcd.setCursor(0, 1);
  lcd.print("h" + to2Chars(internalTemperatureAndHumidity.humidity) + "% ");
  lcd.print("t" + to2Chars(internalTemperatureAndHumidity.temperature) + "C ");
}

void updateScreen() {
  if(menu.isActive) {
    if (menu.isParamsActive()) {
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
  airInflow.update();
  humidifier.update();
  airCirculation.update();
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
  airInflow.init();
  humidifier.init();
  airCirculation.init();
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
    menu.navigate(joystick.direction);
  }
  
  updateScreen();
  updateDevices();
}
