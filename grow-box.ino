#include <EEPROM.h>
#include <Wire.h>

// https://github.com/duinoWitchery/hd44780
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include <Arduino-devices.h>
#include "sensors/clocks/DS3231.h"
#include "sensors/temperature-and-humidity/BME280.h"
#include "devices/switch-by-level/TurnOnWhenHigher.h"
#include "devices/switch-by-level/TurnOnWhenLower.h"
#include "devices/switch-by-time/ScheduleIntervalSwitch.h"
#include "devices/switch-by-time/ClockTimeIntervalSwitch.h"

#include <Arduino-progmem-menu.h>
#include "outputs/lcd-hd44780/LcdHd44780Output.h"
#include "inputs/analog-joystick/AnalogJoystick.h"

#include "./src/settings.h"
#include "./src/menu.h"
// #include "./src/icons.h"

#define LIGHTENING_PIN 8
#define HUMIDIFIER_PIN 7
#define LIGHTENING_FANS_PIN 6
#define VENTILATION_PIN 5

// see: loadSettings()
const DateTime CURRENT_DATE(2025, 4, 23, 14, 58, 0, 3);

// Menu input and output
hd44780_I2Cexp lcd(0x3F); // or lcd(0x27);
Menu::AnalogJoystickInput menuInput(A2, A3, true, false);
Menu::LcdHd44780Output menuOutput(&lcd);

// Shared sensors
DS3231_Sensor clock; // Create clock, connected to I2C
BME280_Sensor internalTemperatureAndHumidity(BME280I2C::I2CAddr_0x77);


// Relays
ClockTimeIntervalSwitch lightening( LIGHTENING_PIN, settings.lightening.fromMinutes, settings.lightening.toMinutes );
ClockTimeIntervalSwitch lighteningFans( LIGHTENING_FANS_PIN, settings.lightening.fromMinutes, settings.lightening.toMinutes );

// ..based on sensors
TurnOnWhenLower humidifier( HUMIDIFIER_PIN, settings.humidity, internalTemperatureAndHumidity.humidity, 5 );
TurnOnWhenHigher dryer( VENTILATION_PIN, settings.humidity, internalTemperatureAndHumidity.humidity, 5 );
ScheduleIntervalSwitch ventilation( VENTILATION_PIN, settings.ventilation.enableForMinutes, settings.ventilation.periodMinutes );
TurnOnWhenHigher cooling( VENTILATION_PIN, settings.temperature.day, internalTemperatureAndHumidity.temperature, 2 );

// PWM intensity
// IntensityControl *airCirculation = new IntensityControl( 13, settings.airCirculation, 20);

bool isLightWasOn = false;

void printFormatted(char* (*formatValue)(unsigned int value), unsigned int* value) {
  char* formattedValue = formatValue(value);
  lcd.print(formattedValue);
  free(formattedValue);
}

void printMainScreen() {
  lcd.setCursor(0, 0);
  printFormatted(Menu::to2Digits, internalTemperatureAndHumidity.temperature);
  lcd.print((char)223);
  lcd.print("C ");
  printFormatted(Menu::to2Digits, internalTemperatureAndHumidity.humidity);
  lcd.print("% ");

  lcd.setCursor(11, 0);
  printFormatted(Menu::toTime24, clock.getIntTime());

  lcd.setCursor(0, 1);
  lcd.print("L");
  lcd.print(lightening.isEnabled ? "+" : "-");
  lcd.print(" H");
  lcd.print(humidifier.isEnabled ? "+" : "-");
  lcd.print(" V");
  lcd.print(ventilation.isEnabled ? "+" : "-");
  lcd.print(" D");
  lcd.print(dryer.isEnabled ? "+" : "-");
  lcd.print(" C");
  lcd.print(cooling.isEnabled ? "+" : "-");
}

// Read current values from sensors
void updateSensors() {
  internalTemperatureAndHumidity.update();
  clock.update();
}

// Turn ON|OFF relays and set intensity values
void updateDevices() {
  lightening.update(clock.getIntTime());
  lighteningFans.update(clock.getIntTime());
  humidifier.update();
  ventilation.update(clock.getIntTime());
  dryer.update();
  cooling.update();
//  airCirculation.update();
  digitalWrite( ventilation.pin, ventilation.isEnabled || dryer.isEnabled || (cooling.isEnabled && !humidifier.isEnabled));
}

void updateDevicesSettings() {
  lightening.fromMinutes = settings.lightening.fromMinutes;
  lightening.toMinutes = settings.lightening.toMinutes;
  humidifier.demandedValue = settings.humidity;
  dryer.demandedValue = settings.humidity;
  lighteningFans.fromMinutes = settings.lightening.fromMinutes;
  lighteningFans.toMinutes = settings.lightening.toMinutes;
  ventilation.enableForMinutes = settings.ventilation.enableForMinutes;
  ventilation.periodMinutes = settings.ventilation.periodMinutes;
  cooling.demandedValue = lightening.isEnabled ? settings.temperature.day : settings.temperature.night;
}

// Load setting, stored at EEPROM
void loadSettings() {
  EEPROM.get( 0, settings );

  if (settings.structVersion != defaultSettings.structVersion) {
    EEPROM.put( 0, defaultSettings );
    settings = defaultSettings;

    rtc.setDateTime(CURRENT_DATE); // Adjust date-time as defined 'dt' above
    return;
  }

  updateDevicesSettings();
}

void saveSettings() {
  EEPROM.put( 0, settings );
  updateDevicesSettings();
}

// void initIcons() {
//    static const byte glyph[] = { B00010000, B00110100, B00110000, B00110100, B00010000 };
//    lcd.createChar(0, glyph);
// }

// All devices set-up
void setup() {
  Wire.begin();

  clock.init();
  internalTemperatureAndHumidity.init();

  lightening.init();
  lighteningFans.init();
  humidifier.init();
  ventilation.init();
  dryer.init();
  cooling.init();
//  airCirculation.init();

  lcd.init();
  lcd.backlight();

  loadSettings();
  updateDevicesSettings();

//  initIcons();
  Menu::controller->init(&settingsMenu, &menuInput, &menuOutput);
}

// Update sensors and devices, display menu if visible, save settings on menu exit
void loop() {
  updateSensors();
  updateDevices();

  bool wasActive = settingsMenu.isActive;
  Menu::controller->update();

  if (isLightWasOn != lightening.isEnabled) {
    isLightWasOn = lightening.isEnabled;
    updateDevicesSettings();
  }

  // is out from menu
  if (!settingsMenu.isActive) {
    printMainScreen();

    // save settings on menu exit
    if (wasActive) {
      saveSettings();
    }
  }
}
