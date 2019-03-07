/***********************************************************************************
 * This file is part of the swissknife library which contains the class examples   *
 * of CS133: Advanced C++ programming at ShanghaiTech (spring semester 2019)       *
 * There is no copyright and there is no license, feel free to do with it          *
 * whatever you want.                                                              *
 ***********************************************************************************/

#include <stdlib.h>
#include <math.h>

#include <fstream>


int main( int argc, char** argv ) {
  std::ofstream myGeneratedCode( argv[1] );
  myGeneratedCode << "double sqrt_lut[] = {\n";

  for (int i = 0; i < 10; i++ ) {
    myGeneratedCode << "  " << sqrt( (double) i);
    if (i == 9)
      myGeneratedCode << "};\n";
    else
      myGeneratedCode << ",\n";
  }

  return 0;
}