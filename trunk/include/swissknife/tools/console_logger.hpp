/***********************************************************************************
 * This file is part of the swissknife library which contains the class examples   *
 * of CS133: Advanced C++ programming at ShanghaiTech (spring semester 2019)       *
 * There is no copyright and there is no license, feel free to do with it          *
 * whatever you want.                                                              *
 ***********************************************************************************/

#ifndef SWISSKNIFE_TOOLS_CONSOLE_LOGGER_HPP_
#define SWISSKNIFE_TOOLS_CONSOLE_LOGGER_HPP_

#include "base_logger.hpp"

namespace swissknife {
namespace tools {

class ConsoleLogger : public BaseLogger {
public:
  ConsoleLogger();
  virtual ~ConsoleLogger();

  void printErrorMessage( std::string & str );
};

}
}

#endif