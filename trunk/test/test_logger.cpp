/***********************************************************************************
 * This file is part of the swissknife library which contains the class examples   *
 * of CS133: Advanced C++ programming at ShanghaiTech (spring semester 2019)       *
 * There is no copyright and there is no license, feel free to do with it          *
 * whatever you want.                                                              *
 ***********************************************************************************/

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

#include "swissknife_config.h"
#include "swissknife/tools/console_logger.hpp"
#include "swissknife/tools/file_logger.hpp"


using namespace swissknife::tools;

class Month {
public:
  Month( BaseLogger * logger );
  virtual ~Month();

  void setMonth( int month );

private:
  int m_month;
  BaseLogger * m_logger;
};

Month::Month( BaseLogger * logger ) {
  m_month = 1;
  m_logger = logger;
}

Month::~Month() {}

void
Month::setMonth( int month ) {
  if( month < 1 || month > 12 ) {
    std::string ErrorMessage("Error: Wrong month setting");
    m_logger->printErrorMessage(ErrorMessage);
  }
}

int main() {
  
  std::cout << "Welcome to CS133 swissknife library version " << SWISSKNIFE_VERSION_MAJOR << "." << SWISSKNIFE_VERSION_MINOR << std::endl;

  ConsoleLogger logger;
  //std::string logFile("/Users/laurent/Documents/CS133/classExamples/log.txt");
  //FileLogger logger(logFile);

  Month month( &logger );

  month.setMonth(4);
  month.setMonth(13);
}