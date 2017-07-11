#ifndef DEVICE_H
#define DEVICE_H

class Device {
  protected:
  	unsigned char pin = 13;
  	void writeToPin();
  	void writeToPinInverted();
  public:
  	Device(unsigned char _pin);
  	void init();
    virtual void update();
    bool isEnabled;
};

#endif;