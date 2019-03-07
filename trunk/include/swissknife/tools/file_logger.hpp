/***********************************************************************************
 * This file is part of the swissknife library which contains the class examples   *
 * of CS133: Advanced C++ programming at ShanghaiTech (spring semester 2019)       *
 * There is no copyright and there is no license, feel free to do with it          *
 * whatever you want.                                                              *
 ***********************************************************************************/

#ifndef SWISSKNIFE_TOOLS_FILE_LOGGER_HPP_
#define SWISSKNIFE_TOOLS_FILE_LOGGER_HPP_

#include "base_logger.hpp"

#include <fstream>

namespace swissknife {
namespace tools {

class FileLogger : public BaseLogger {
public:
  FileLogger( std::string & file );
  virtual ~FileLogger();

  void printErrorMessage( std::string & str );

private:
  std::ofstream m_stream;
};

}
}

#endif