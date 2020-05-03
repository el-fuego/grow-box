#include <EEPROM.h>
#include <Wire.h>

#include <Arduino-devices.h>
#include "devices/outputs/PCA9685.h"

#include <Arduino-progmem-menu.h>
#include "outputs/lcd-pcd8544/LcdPcd8544Output.h"
#include "inputs/analog-joystick/AnalogJoystick.h"

#include "./src/settings.h"
#include "./src/menu.h"
//#include "./src/icons.h"

// Menu input and output
PCD8544 lcd(6, 5, 4, 2, 3);
Menu::AnalogJoystickInput menuInput(A6, A7);
Menu::LcdPcd8544Output menuOutput(&lcd);

// Shared sensors
DS3231_Sensor clock;
Am2320_Sensor externalTemperatureAndHumidity;

struct SectionDevices {
  // Sensors
  BaseDHT *internalTemperatureAndHumidity;

  // Relays
  TimeIntervalSwitch *lightening;
  TurnOnWhenLower *humidifier;
  TimeIntervalSwitch *lighteningFans;
  TurnOnWhenHigher *dryer;
  ScheduleIntervalSwitch *airInflow;
//  TurnOnWhenHigher *cooling;

  // PWM intensity
//  IntensityControl *airCirculation;
};

PCA9685_Output *pin_extender = new PCA9685_Output(0x41);

// Top Section
BME280_Sensor topSectionInternalTemperatureAndHumidity(BME280I2C::I2CAddr_0x77);
SectionDevices topSectionDevices = {
  &topSectionInternalTemperatureAndHumidity,
  new TimeIntervalSwitch( pin_extender, 10, s1_settings.lightening, clock ),
  new TurnOnWhenLower( pin_extender, 11, s1_settings.humidity, topSectionInternalTemperatureAndHumidity.humidity, 10 ),
  new TimeIntervalSwitch( pin_extender, 12, s1_settings.lightening, clock ),
  new TurnOnWhenHigher( pin_extender, 14, s1_settings.humidity, topSectionInternalTemperatureAndHumidity.humidity, 15 ),
  new ScheduleIntervalSwitch( pin_extender, 14, s1_settings.airInflow, clock ),
//  new TurnOnWhenHigher( pin_extender, 14, s1_settings.temperature.day, topSectionInternalTemperatureAndHumidity.temperature, 2 ),
//  new IntensityControl( pin_extender, 13, s1_settings.airCirculation, 20)
};

// Middle Section
Si7021_Sensor middleSectionInternalTemperatureAndHumidity;
SectionDevices middleSectionDevices = {
  &middleSectionInternalTemperatureAndHumidity,
  new TimeIntervalSwitch( pin_extender, 5, s2_settings.lightening, clock ),
  new TurnOnWhenLower( pin_extender, 6, s2_settings.humidity, middleSectionInternalTemperatureAndHumidity.humidity, 10 ),
  new TimeIntervalSwitch( pin_extender, 7, s2_settings.lightening, clock ),
  new TurnOnWhenHigher( pin_extender, 9, s2_settings.humidity, middleSectionInternalTemperatureAndHumidity.humidity, 15 ),
  new ScheduleIntervalSwitch( pin_extender, 9, s2_settings.airInflow, clock ),
//  new TurnOnWhenHigher( pin_extender, 9, s2_settings.temperature.day, middleSectionInternalTemperatureAndHumidity.temperature, 2 ),
//  new IntensityControl( pin_extender, 8, s2_settings.airCirculation, 20)
};

// Bottom Section
BME280_Sensor bottomSectionInternalTemperatureAndHumidity(BME280I2C::I2CAddr_0x76);
SectionDevices bottomSectionDevices = {
  &bottomSectionInternalTemperatureAndHumidity,
  new TimeIntervalSwitch( pin_extender, 0, s3_settings.lightening, clock ),
  new TurnOnWhenLower( pin_extender, 1, s3_settings.humidity, bottomSectionInternalTemperatureAndHumidity.humidity, 10 ),
  new TimeIntervalSwitch( pin_extender, 2, s3_settings.lightening, clock ),
  new TurnOnWhenHigher( pin_extender, 4, s3_settings.humidity, bottomSectionInternalTemperatureAndHumidity.humidity, 15 ),
  new ScheduleIntervalSwitch( pin_extender, 4, s3_settings.airInflow, clock ),
//  new TurnOnWhenHigher( pin_extender, 4, s3_settings.temperature.day, bottomSectionInternalTemperatureAndHumidity.temperature, 2 ),
//  new IntensityControl( pin_extender, 3, s3_settings.airCirculation, 20)
};


//void printDeviceIcon(const char* icon, boolean isEnabled) {
//  lcd.print(isEnabled ? icon : " ");
//}

void printFormatted(char* (*formatValue)(unsigned int value), unsigned int* value) {
  char* formattedValue = formatValue(value);
  lcd.print(formattedValue);
  free(formattedValue);
}

void printSectionMainScreen(SectionDevices devices, int startLine) {
  lcd.setCursor(0, startLine);
//  lcd.print(devices.airCirculation->isEnabled ? "C" : " ");
  lcd.print(devices.lightening->isEnabled ? "L" : " ");
  lcd.print(devices.humidifier->isEnabled ? "H" : (devices.dryer->isEnabled ? "D" : " "));
//  lcd.print(devices.humidifier->isEnabled ? "H" : (devices.cooling->isEnabled ? "C" : " "));
  lcd.print(devices.airInflow->isEnabled ? "I" : " ");

  lcd.setCursor(0, startLine + 1);
  lcd.print("h");
  printFormatted(Menu::to2Digits, devices.internalTemperatureAndHumidity->humidity);
  lcd.print("% ");

  lcd.print("t");
  printFormatted(Menu::to2Digits, devices.internalTemperatureAndHumidity->temperature);
  lcd.print("C ");
}

// Current sensor values and working devices information
void printMainScreen() {
  lcd.setCursor(49, 0);
  lcd.write(0);
  printFormatted(Menu::toTime24, clock.getIntTime());

  lcd.setCursor(54, 2);
  lcd.write(0);
  lcd.print("ext:");

  lcd.setCursor(54, 3);
  lcd.write(0);
  lcd.print("h");
  printFormatted(Menu::to2Digits, externalTemperatureAndHumidity.humidity);
  lcd.print("%");

  lcd.setCursor(54, 4);
  lcd.write(0);
  lcd.print("t");
  printFormatted(Menu::to2Digits, externalTemperatureAndHumidity.temperature);
  lcd.print("C");

  printSectionMainScreen(topSectionDevices, 0);
  printSectionMainScreen(middleSectionDevices, 2);
  printSectionMainScreen(bottomSectionDevices, 4);
}

// Turn ON|OFF relays and set intensity values
void updateSectionDevices(SectionDevices devices) {
  devices.lightening->update();
  devices.lighteningFans->update();
  devices.airInflow->update();
  devices.dryer->update();
  devices.humidifier->update();
//  devices.airCirculation->update();
//  devices.cooling->update();
  devices.airInflow->output->write(
    devices.airInflow->pin, devices.airInflow->isEnabled
    || devices.dryer->isEnabled
//    || (devices.cooling->isEnabled && !devices.humidifier->isEnabled)
  );
}

// Read current values from sensors
void updateSensors() {
  topSectionDevices.internalTemperatureAndHumidity->update();
  middleSectionDevices.internalTemperatureAndHumidity->update();
  bottomSectionDevices.internalTemperatureAndHumidity->update();
  clock.update();
  externalTemperatureAndHumidity.update();
}

// Load setting, stored at EEPROM
void loadSettings() {
  EEPROM.get( 0, s1_settings );

  if (s1_settings.structVersion != defaultSettings.structVersion) {
    EEPROM.put( 0, defaultSettings );
    EEPROM.put( sizeof(defaultSettings), defaultSettings );
    EEPROM.put( sizeof(defaultSettings) * 2, defaultSettings );
    s1_settings = defaultSettings;
    s2_settings = defaultSettings;
    s3_settings = defaultSettings;
    return;
  }

  EEPROM.get( sizeof(defaultSettings), s2_settings );
  EEPROM.get( sizeof(defaultSettings) * 2, s3_settings );
}

void saveSettings() {
  EEPROM.put( 0, s1_settings );
  EEPROM.put( sizeof(defaultSettings), s2_settings );
  EEPROM.put( sizeof(defaultSettings) * 2, s3_settings );
}

//void initIcons() {
//   static const byte glyph[] = { B00010000, B00110100, B00110000, B00110100, B00010000 };
//   lcd.createChar(0, glyph);
//}

// Set-up ports
void initSectionDevices(SectionDevices devices) {
  devices.internalTemperatureAndHumidity->init();
  devices.lightening->init();
  devices.lighteningFans->init();
  devices.airInflow->init();
  devices.dryer->init();
  devices.humidifier->init();
//  devices.airCirculation->init();
//  devices.cooling->init();
}

// All devices set-up
void setup() {
  Wire.begin();

  clock.init();
  loadSettings();

  lcd.begin(84, 48);
  lcd.setContrast(63); // 127 max

  Menu::controller->init(&settingsMenu, &menuInput, &menuOutput);

//  initIcons();
  externalTemperatureAndHumidity.init();
  topSectionInternalTemperatureAndHumidity.init();
  middleSectionInternalTemperatureAndHumidity.init();
  bottomSectionInternalTemperatureAndHumidity.init();
  initSectionDevices(topSectionDevices);
  initSectionDevices(middleSectionDevices);
  initSectionDevices(bottomSectionDevices);
}

// Update sensors and devices, display menu if visible, save settings on menu exit
void loop() {
  updateSensors();
  updateSectionDevices(topSectionDevices);
  updateSectionDevices(middleSectionDevices);
  updateSectionDevices(bottomSectionDevices);

  bool wasActive = settingsMenu.isActive;
  Menu::controller->update();

  // is out from menu
  if (!settingsMenu.isActive) {
    printMainScreen();

    // save settings on menu exit
    if (wasActive) {
      saveSettings();
    }
  }
}
