/***********************************************************************************
 * This file is part of the swissknife library which contains the class examples   *
 * of CS133: Advanced C++ programming at ShanghaiTech (spring semester 2019)       *
 * There is no copyright and there is no license, feel free to do with it          *
 * whatever you want.                                                              *
 ***********************************************************************************/

#include "swissknife/tools/file_logger.hpp"

swissknife::tools::FileLogger::FileLogger( std::string & file ) {
  m_stream.open(file);
}

swissknife::tools::FileLogger::~FileLogger() {
  m_stream.close();
}

void
swissknife::tools::FileLogger::printErrorMessage( std::string & str ) {
  m_stream << str << std::endl;
}