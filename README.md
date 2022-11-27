
[![Arduino CI](https://github.com/RobTillaart/TSL260R/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TSL260R/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TSL260R/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TSL260R/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TSL260R/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TSL260R/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TSL260R.svg?maxAge=3600)](https://github.com/RobTillaart/TSL260R/releases)


# TSL260R

Arduino library for the TSL260R IR to voltage convertor


## Description

The TSL260R (TSL261R, TSL262R) is a IR sensor that outputs a voltage depending on the irradiation.

This library does convert the output voltage to uW/cm2.

As the sensors differ by sensitivity the library has three distinct classes.


**Warning** this library is experimental so you should use it with care.
It is written on the datasheet, and I have no hardware yet to test it. 
Of course I am very interested in your experiences and feedback to improve
the library.


## Hardware Connection

Always check datasheet

```
//  PIN 1 - GND
//  PIN 2 - VDD      2.7 V .. 5.5 V
//  PIN 3 - SIGNAL   voltage out
```


## Interface

#### Base

- **TSL260R()** constructor
- **float irradiance(float voltage)** returns the irradiance in uW/cm2.

#### Wavelength

- **void setWavelength(uint16_t wavelength = 940)** sets the wavelength so the conversion can use a correction factor. 
At 900 - 940 nm the wavelength correction factor == 1.0.
Wavelength should be between 830 and 1100.
- **uint16_t getWavelength()** returns the set wavelength.
- **float getWaveLengthFactor()** returns the wavelength correction factor. 
Note the sensor is most sensitive around 940 nm. See datasheet.
- **calculateWaveLengthFactor(uint16_t waveLength)** calculates the factor to compensate for less sensitivity. 
E.g. if the sensor is 0.5 x as sensitive at a given wavelength the factor should be 2. 


#### Calibration

To elaborate.


## Operations

See examples.


## Future

#### must
- improve documentation
- buy hardware (where)
- test test test test
- extend interface
  - include an analogRead constructor + vars
  - getters/setters for A and B to calibrate the sensor.

#### should
- extend unit tests
- write examples



#### could
- test with different IR LEDS (e.g. remote)
