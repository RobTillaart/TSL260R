//
//    FILE: TSL260R.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2022-11-25
// PURPOSE: library for the TSL260R IR to voltage convertor


#include "TSL260R.h"


TSL260R::TSL260R(uint8_t pin, uint16_t maxADC, float voltage)
{
  _pin = pin;
  _voltagePerStep = voltage / maxADC;
  //  datasheet page 9 figure 12
  //  voltage parameters
  _aa = 10.0067;
  _bb = -0.02013423; 
  //  wavelength parameters
  _waveLength       = 940; 
  _waveLengthFactor = 1.0;
}


TSL260R::TSL260R()
{
  TSL260R(0, 1, 0); //  prevent divide by zero
  //  datasheet page 9
  //  voltage parameters
  _aa = 10.0067;
  _bb = -0.02013423; 
  //  wavelength parameters
  _waveLength       = 940; 
  _waveLengthFactor = 1.0;
}


float TSL260R::irradiance(float voltage)
{
  float value = _aa * voltage + _bb;
  if (_waveLengthFactor != 1.0) value *= _waveLengthFactor;
  return value;
}


float TSL260R::irradiance()
{
  float voltage = analogRead(_pin) * _voltagePerStep;
  return irradiance(voltage);
}


void TSL260R::setWavelength(uint16_t wavelength)
{
  _waveLength = wavelength;
  _waveLengthFactor = calculateWaveLengthFactor(_waveLength);
}


uint16_t TSL260R::getWavelength()
{
  return _waveLength; 
}


float TSL260R::getWaveLengthFactor() 
{
  return _waveLengthFactor; 
}


float TSL260R::calculateWaveLengthFactor(uint16_t waveLength)
{
  //  figure 12 datasheet
  //  940 nm is reference 1.000
  //  remaining is linear interpolated between points in the graph
  float in[]  = { 800,  830, 880, 900, 940, 990, 1050, 1100, 1150};
  float out[] = { 0.01, 0.1, 0.8, 1.0, 1.0, 0.5, 0.3,  0.1,  0.01};
  //  the correction factor is reciprocate as sensor is less sensitive.
  return 1.0 / multiMap(waveLength, in, out, 9);
}


float TSL260R::multiMap(float value, float * _in, float * _out, uint8_t size)
{
  //  take care the value is within range
  //  value = constrain(value, _in[0], _in[size-1]);
  if (value <= _in[0]) return _out[0];
  if (value >= _in[size-1]) return _out[size-1];

  //  search right interval
  uint8_t pos = 1;  // _in[0] already tested
  while(value > _in[pos]) pos++;

  //  this will handle all exact "points" in the _in array
  if (value == _in[pos]) return _out[pos];

  //  interpolate in the right segment for the rest
  uint8_t pos1 = pos - 1;
  return (value - _in[pos1]) * (_out[pos] - _out[pos1]) / (_in[pos] - _in[pos1]) + _out[pos1];
}



///////////////////////////////////////////////////////
//
//  TSL261R
//
TSL261R::TSL261R() : TSL260R()
{
  //  datasheet page 9
  //  voltage parameters
  _aa = 23.34564;
  _bb = -0.03692;
  //  wavelength parameters
  _waveLength       = 940; 
  _waveLengthFactor = 1.0;
}


TSL261R::TSL261R(uint8_t pin, uint16_t maxADC, float voltage) : TSL260R(pin, maxADC, voltage)
{
}


///////////////////////////////////////////////////////
//
//  TSL262R
//
TSL262R::TSL262R() : TSL260R()
{
  //  datasheet page 9
  //  voltage parameters
  _aa = 110;
  _bb = 0;
  //  wavelength parameters
  _waveLength       = 940; 
  _waveLengthFactor = 1.0;
}



TSL262R::TSL262R(uint8_t pin, uint16_t maxADC, float voltage) : TSL260R(pin, maxADC, voltage)
{
}



//  -- END OF FILE --

