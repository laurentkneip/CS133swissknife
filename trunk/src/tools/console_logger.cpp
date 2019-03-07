/***********************************************************************************
 * This file is part of the swissknife library which contains the class examples   *
 * of CS133: Advanced C++ programming at ShanghaiTech (spring semester 2019)       *
 * There is no copyright and there is no license, feel free to do with it          *
 * whatever you want.                                                              *
 ***********************************************************************************/

#include "swissknife/tools/console_logger.hpp"

#include <iostream>

swissknife::tools::ConsoleLogger::ConsoleLogger() {}
swissknife::tools::ConsoleLogger::~ConsoleLogger() {}

void
swissknife::tools::ConsoleLogger::printErrorMessage( std::string & str ) {
  std::cout << str << std::endl;
}