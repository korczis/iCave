# iCave

Your Cave's Web Interface

## Structure

- [Software Structure](https://github.com/korczis/iCave/blob/master/app/README.md)

## Images

![Display Image](https://raw.githubusercontent.com/korczis/iCave/master/imgs/display.jpg)

## Hardware

- [Teensy 3.1](https://www.pjrc.com/teensy/teensy31.html) (~ $20)
  
  Teensy 3.1 is a small, breadboard-friendly development which brings a low-cost 32 bit ARM Cortex-M4 platform to hobbyists, students and engineers, using an adapted version of the Arduino IDE.

  - Processor: MK20DX256VLH7 
  - Core: Cortex-M4
  - Clock: 72 MHz / Overclock: 96 MHz
  - Flash Memory: 256 kB
  - Cache: 256 B
  - RAM: 64 kB
  - EEPROM: 2 kB
  - DAC: 12 bits
  - USB / Serial / SPI / I2C / CAN / I2S
  - 5V tolerant digital inputs

- [ST7735R](https://www.adafruit.com/product/358) (~ $20)

  Display that uses 4-wire SPI to communicate and has its own pixel-addressable frame buffer, it can be used with every kind of microcontroller.
  
  - 1.8" diagonal LCD TFT display
  - 128x160 resolution, 18-bit (262,144) color
  - ST7735R (datasheet) controller with built in pixel-addressable video RAM buffer
  - 4 or 5 wire SPI digital interface
  - Built-in microSD slot - uses 2 more digital lines
  - 5V compatible, use with 3.3V or 5V logic
  - Onboard 3.3V @ 150mA LDO regulator
  - 2 white LED backlight, transistor connected so you can PWM dim the backlight
  - 1x10 header for easy breadboarding
  - 4 x 0.9"/2mm mounting holes in corners
  - Current with full backlight draw is ~50mA

- [DHT22](https://www.adafruit.com/product/393) (~ $15)

  Basic, low-cost digital temperature and humidity sensor. It uses a capacitive humidity sensor and a thermistor to measure the surrounding air, and spits out a digital signal on the data pin.
  
  - Low cost
  - 3 to 5V power and I/O
  - 2.5mA max current use 
  - 0-100% humidity readings with 2-5% accuracy
  - -40 to 80°C temperature readings ±0.5°C accuracy
  
- [GPS](https://www.adafruit.com/products/746) (~ $40)

  High-quality GPS module that can track up to 22 satellites on 66 channels and has an excellent high-sensitivity receiver.
  
  - 165 dBm sensitivity, 10 Hz updates, 66 channels
  - 5V friendly design
  - Only 20mA current draw
  - Breadboard friendly + two mounting holes
  - RTC battery-compatible
  - Built-in datalogging
  - PPS output on fix
  - Internal patch antenna
  - u.FL connector for external active antenna
  - Fix status LED

- [TSL2561](https://www.adafruit.com/products/439) (~ $6)

  The TSL2561 luminosity sensor is an advanced digital light sensor
  
  - Approximates Human eye Response
  - Precisely Measures Illuminance in Diverse Lighting Conditions
  - Temperature range: -30 to 80 *C
  - Dynamic range (Lux): 0.1 to 40,000 Lux
  - Voltage range: 2.7-3.6V
  - Interface: I2C
  - I2C 7-bit addresses 0x39, 0x29, 0x49, selectable with jumpers
  
- [Wifi CC3000](https://www.adafruit.com/products/1469) (~ $35)

  Microcontroller-friendly WiFi module
  
  - 802.11b/g
  - Open/WEP/WPA/WPA2 security,
  - TKIP & AES
  - Built in TCP/IP stack
  - "BSD socket" interface

- [nRF24L01](http://playground.arduino.cc/InterfacingWithHardware/Nrf24L01) (~ $1-5)

  Radio/Wireless Transceiver

  - 2.4GHz RF
  - [How To](http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo)

- [RFID-RC522](http://devsketches.blogspot.cz/2014/05/rfid-sensor-funduino-rfid-rc522.html) (~ $6)

  RFID sensor
  
  
