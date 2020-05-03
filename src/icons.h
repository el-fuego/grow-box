#ifndef ICONS_H
#define ICONS_H

const unsigned char humidityIcon[8] = {
  0b00100,
  0b00100,
  0b01010,
  0b01010,
  0b10001,
  0b10001,
  0b10001,
  0b01110
};

const unsigned char temperatureIcon[8] = {
  0b00100,
  0b01010,
  0b01010,
  0b01110,
  0b01110,
  0b11111,
  0b11111,
  0b01110
};

const unsigned char wateringIcon[8] = {
  0b00100,
  0b00000,
  0b01010,
  0b00000,
  0b10101,
  0b00000,
  0b11111,
  0b01110
};

const unsigned char aerationIcon[8] = {
  0b00010,
  0b00101,
  0b00010,
  0b01000,
  0b10100,
  0b01000,
  0b00010,
  0b00101
};

const unsigned char wateringSalinityIcon[8] = {
  0b01110,
  0b11111,
  0b11011,
  0b11111,
  0b11011,
  0b11111,
  0b11011,
  0b11111
};

const unsigned char dwcSalinityIcon[8] = {
  0b01110,
  0b11111,
  0b10011,
  0b10101,
  0b10101,
  0b10101,
  0b10011,
  0b11111
};


#endif
