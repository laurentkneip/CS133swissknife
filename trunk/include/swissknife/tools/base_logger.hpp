/***********************************************************************************
 * This file is part of the swissknife library which contains the class examples   *
 * of CS133: Advanced C++ programming at ShanghaiTech (spring semester 2019)       *
 * There is no copyright and there is no license, feel free to do with it          *
 * whatever you want.                                                              *
 ***********************************************************************************/

#ifndef SWISSKNIFE_TOOLS_BASE_LOGGER_HPP_
#define SWISSKNIFE_TOOLS_BASE_LOGGER_HPP_

#include <stdlib.h>
#include <string>

namespace swissknife {
namespace tools {

class BaseLogger {
public:
  BaseLogger();
  virtual ~BaseLogger();

  virtual void printErrorMessage( std::string & str ) = 0;
};

}
}

#endif