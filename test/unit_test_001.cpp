//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2022-11-25
// PURPOSE: unit tests for the temperature library
//          https://github.com/RobTillaart/TSL260R
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)


#include <ArduinoUnitTests.h>


#include "Arduino.h"
#include "TSL260R.h"


unittest_setup()
{
  fprintf(stderr, "TSL260R_LIB_VERSION: %s\n", (char *) TSL260R_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  TSL260R TSL;
  assertEqual(940, TSL.getWavelength() );
  assertEqualFloat(1.0, TSL.getWaveLengthFactor(), 0.001);
}


unittest(test_irradiance)
{
  TSL260R TSL0;
  TSL261R TSL1;
  TSL262R TSL2;

  //  see output example 1
  assertEqualFloat(6.985,  TSL0.irradiance(0.700), 0.001);
  assertEqualFloat(16.305, TSL1.irradiance(0.700), 0.001);
  assertEqualFloat(77.000, TSL2.irradiance(0.700), 0.001);
}


unittest(test_calculateWaveLengthFactor)
{
  TSL260R TSL;

  //  check the internal table 
  assertEqualFloat(100,   TSL.calculateWaveLengthFactor(800), 0.1);
  assertEqualFloat(10,    TSL.calculateWaveLengthFactor(830), 0.01);
  assertEqualFloat(1.25,  TSL.calculateWaveLengthFactor(880), 0.001);
  assertEqualFloat(1.0,   TSL.calculateWaveLengthFactor(900), 0.001);
  assertEqualFloat(1.0,   TSL.calculateWaveLengthFactor(940), 0.001);
  assertEqualFloat(2.0,   TSL.calculateWaveLengthFactor(990), 0.001);
  assertEqualFloat(3.333, TSL.calculateWaveLengthFactor(1050), 0.001);
  assertEqualFloat(10,    TSL.calculateWaveLengthFactor(1100), 0.01);
  assertEqualFloat(100,   TSL.calculateWaveLengthFactor(1150), 0.1);
}



unittest_main()


// --------
