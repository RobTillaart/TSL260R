//  see email 2022-01-25

#pragma once
//
//    FILE: TSL260R.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2022-11-25
// PURPOSE: library for the TSL260R IR to voltage convertor


#define TSL260R_LIB_VERSION             (F("0.1.0"))

#include "Arduino.h"


class TSL260R
{
public:

  TSL260R();

  float    irradiance(float voltage);

  //  range: 800 - 1150 ==> 940 = default.
  void     setWavelength(uint16_t wavelength = 940);
  uint16_t getWavelength();
  float    getWaveLengthFactor();

  //  useful for debugging too
  float    calculateWaveLengthFactor(uint16_t waveLength);


protected:
  uint16_t _waveLength;
  float    _waveLengthFactor;
  //       _A and _B are defined in constructor;
  //       need getter / setter to adjust values runtime
  float    _A;
  float    _B;
  float    multiMap(float value, float * _in, float * _out, uint8_t size);
};


///////////////////////////////////////////////////////
//
//  DERIVED CLASSES
//
class TSL261R : public TSL260R
{
public:
  TSL261R();
};


class TSL262R : public TSL260R
{
public:
  TSL262R();
};


// -- END OF FILE --


