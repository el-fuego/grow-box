#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Arduino-devices.h>
#include <Arduino-progmem-menu.h>
#include "outputs/lcd-i2c-text/LcdI2cTextOutput.h"
#include "inputs/analog-joystick/AnalogJoystick.h"

#include "./src/settings.h"
#include "./src/menu.h"

// Menu input and output
LiquidCrystal_I2C lcd(0x27, 16, 2);
Menu::AnalogJoystickInput menuInput(A0, A1);
Menu::LcdI2cTextOutput menuOutput(&lcd);

// Sensors
DHT11_Sensor internalTemperatureAndHumidity( 10 );
DS3231_Sensor clock;

// Relays
ScheduleIntervalSwitch dwcAeration( 2, currentSettings.dwcAeration, clock );
ScheduleIntervalSwitch watering( 7, currentSettings.watering, clock );
TimeIntervalSwitch lightening( 9, currentSettings.lightening, clock );

TurnOnWhenLower humidifier( 11, currentSettings.humidity, internalTemperatureAndHumidity.humidity, 5 );
TurnOnWhenHigher airInflow( 12, currentSettings.humidity, internalTemperatureAndHumidity.humidity, 5 );

// Analog intensity
IntensityControl airCirculation( A2, currentSettings.airCirculation, 30);

// Current sensor values and working devices information
void printMainScreen() {
  lcd.setCursor(0, 0);
  lcd.print(airCirculation.isEnabled ? "C" : " ");
  lcd.print(lightening.isEnabled ? "L" : " ");
  lcd.print(watering.isEnabled ? "W" : " ");
  lcd.print(dwcAeration.isEnabled ? "A" : " ");
  lcd.print(humidifier.isEnabled ? "H" : (airInflow.isEnabled ? "I" : " "));

  lcd.print("      ");
  lcd.print(Menu::toTime24(clock.getIntTime()));
  
  lcd.setCursor(0, 1);
  lcd.print("h");
  lcd.print(Menu::to2Digits(internalTemperatureAndHumidity.humidity));
  lcd.print("% ");
  
  lcd.print("t");
  lcd.print(Menu::to2Digits(internalTemperatureAndHumidity.temperature));
  lcd.print("C ");
}

// Turn ON|OFF relays and set intensity values
void updateDevices() {
  lightening.update();
  watering.update();
  dwcAeration.update();
  airInflow.update();
  humidifier.update();
  airCirculation.update();
}

// Read current values from sensors
void updateSensors() {
  internalTemperatureAndHumidity.update();
  clock.update();
}

// Load setting, stored at EEPROM
void loadSettings() {
  EEPROM.get( 0, currentSettings );
  
  if (currentSettings.structVersion != defaultSettings.structVersion) {
    EEPROM.put( 0, defaultSettings );
    currentSettings = defaultSettings;
  }
}

// Set-up ports
void initSensorsAndDevices() {
  internalTemperatureAndHumidity.init();
  clock.init();
  
  lightening.init();
  watering.init();
  dwcAeration.init();
  airInflow.init();
  humidifier.init();
  airCirculation.init();
}

// All devices set-up
void setup() {
  Wire.begin();
  loadSettings();

  // make inverted for strange relay
  dwcAeration.makeOutputInverted();
  watering.makeOutputInverted();
  lightening.makeOutputInverted();

  lcd.init();
  lcd.backlight();

  Menu::controller->init(&settingsMenu, &menuInput, &menuOutput);

  initSensorsAndDevices();
}

// Update sensors and devices, display menu if visible, save settings on menu exit
void loop() {
  updateSensors();
  updateDevices();

  bool wasActive = settingsMenu.isActive;
  Menu::controller->update();

  // is out from menu
  if (!settingsMenu.isActive) {
    printMainScreen();

    // save settings on menu exit
    if (wasActive) {
      EEPROM.put( 0, currentSettings );
    }
  }
}
