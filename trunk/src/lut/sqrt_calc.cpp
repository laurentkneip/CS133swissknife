/***********************************************************************************
 * This file is part of the swissknife library which contains the class examples   *
 * of CS133: Advanced C++ programming at ShanghaiTech (spring semester 2019)       *
 * There is no copyright and there is no license, feel free to do with it          *
 * whatever you want.                                                              *
 ***********************************************************************************/

#include "swissknife/lut/sqrt_calc.hpp"

#include <math.h>

#include "sqrt_lut.inc"

swissknife::lut::SqrtCalc::SqrtCalc() {};
swissknife::lut::SqrtCalc::~SqrtCalc() {};

double
swissknife::lut::SqrtCalc::calc( double val ) {
  int index = floor( (val - 0.0) / 1.0 + 0.5 );
  return sqrt_lut[index];
}