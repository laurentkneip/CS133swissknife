/***********************************************************************************
 * This file is part of the swissknife library which contains the class examples   *
 * of CS133: Advanced C++ programming at ShanghaiTech (spring semester 2019)       *
 * There is no copyright and there is no license, feel free to do with it          *
 * whatever you want.                                                              *
 ***********************************************************************************/

#include "swissknife/profiling/lap_timer.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>


swissknife::profiling::LapHandle::LapHandle() {
  m_number = -1;
}

swissknife::profiling::LapHandle::LapHandle(int number) {
  if (number < 0)
    m_number = -1;
  m_number = number;
}

swissknife::profiling::LapHandle::~LapHandle() {}

int
swissknife::profiling::LapHandle::value() {
  return m_number;
}

bool
swissknife::profiling::LapHandle::valid() {
  return !(m_number < 0);
}

swissknife::profiling::LapTimer::LapTimer( bool start, size_t precision ) {
  m_precision = precision;
  m_activeLap = addLap( std::string("defaultLap") );
  m_running = false;

  if (start) {
    m_running = true;
    m_startingTime = std::chrono::high_resolution_clock::now();
  }
}

swissknife::profiling::LapTimer::~LapTimer() {}
  
void
swissknife::profiling::LapTimer::start() {
  if (m_running) {
    std::cout << "Error: timer is already started\n";
    return;
  }

  m_running = true;
  m_startingTime = std::chrono::high_resolution_clock::now();
}

void
swissknife::profiling::LapTimer::start( LapHandle & lap ) {
  if (m_running) {
    std::cout << "Error: timer is already started\n";
    return;
  }
  
  m_activeLap = lap;
  m_running = true;
  m_startingTime = std::chrono::high_resolution_clock::now();
}

void
swissknife::profiling::LapTimer::stop( bool restart ) {
  int iterations = 1;
  stop(iterations,restart);
}

void
swissknife::profiling::LapTimer::stop( size_t iterations, bool restart ) {
  stop( (int) iterations, restart );
}

void
swissknife::profiling::LapTimer::stop( int iterations, bool restart ) {
  if (!m_running) {
    std::cout << "Error: timer is not started\n";
    return;
  }
  
  std::chrono::high_resolution_clock::time_point toc = std::chrono::high_resolution_clock::now();
  double runningTime = (double) std::chrono::duration_cast<std::chrono::microseconds>(toc-m_startingTime).count() / 1000000.0;
  
  m_cummulativeLapTimes[m_activeLap.value()] += runningTime;
  m_lapIterations[m_activeLap.value()] += iterations;
  
  if(restart)
    m_startingTime = toc;
  else
    m_running = false;
}

void
swissknife::profiling::LapTimer::stop( LapHandle & nextLap, bool restart ) {
  int iterations = 1;
  stop( nextLap, iterations, restart );
}

void
swissknife::profiling::LapTimer::stop( LapHandle & nextLap, size_t iterations, bool restart ) {
  stop( nextLap, (int) iterations, restart );
}

void
swissknife::profiling::LapTimer::stop( LapHandle & nextLap, int iterations, bool restart ) {
  if (!m_running) {
    std::cout << "Error: timer is not started\n";
    return;
  }
  
  std::chrono::high_resolution_clock::time_point toc = std::chrono::high_resolution_clock::now();
  double runningTime = (double) std::chrono::duration_cast<std::chrono::microseconds>(toc-m_startingTime).count() / 1000000.0;
  
  m_cummulativeLapTimes[m_activeLap.value()] += runningTime;
  m_lapIterations[m_activeLap.value()] += iterations;
  
  if (nextLap.valid())
    m_activeLap = nextLap;
  else
    std::cout << "Error: Invalid lap set attempt\n";

  if (restart)
    m_startingTime = toc;
  else
    m_running = false;
}

void
swissknife::profiling::LapTimer::reset() {
  m_running = false;
  for (int i = 0; i < m_cummulativeLapTimes.size(); i++) {
    m_cummulativeLapTimes[i] = 0.0;
    m_lapIterations[i] = 0;
  }
}

void
swissknife::profiling::LapTimer::clear() {
  m_cummulativeLapTimes.clear();
  m_lapIterations.clear();
  m_lapNames.clear();

  m_activeLap = addLap( std::string("defaultLap") );
  m_running = false;

}

swissknife::profiling::LapHandle
swissknife::profiling::LapTimer::addLap( const std::string & lapName ) {
  //check whether we only have the defaultLap and remove
  if( m_lapNames.size() == 1 && findLap(std::string("defaultLap")).valid() ) {
    m_cummulativeLapTimes.clear();
    m_lapIterations.clear();
    m_lapNames.clear();
  }

  LapHandle handle = findLap( lapName );
  if( handle.valid() )
    return handle;

  m_lapNames.push_back(lapName);
  m_cummulativeLapTimes.push_back(0.0);
  m_lapIterations.push_back(0);

  return LapHandle(m_lapNames.size()-1);
}

swissknife::profiling::LapHandle
swissknife::profiling::LapTimer::findLap( const std::string & lapName ) const {
  int index = -1;
  for (size_t i = 0; i < m_lapNames.size(); i++) {
    if( m_lapNames[i] == lapName ) {
      index = i;
      break;
    }
  }

  return LapHandle(index);
}

void
swissknife::profiling::LapTimer::printSummary() const {
  for (size_t i = 0; i < 100; i++)
    std::cout << "\n";

  //get max length of tags
  size_t maxLength = 0;
  for (size_t i = 0; i < m_lapNames.size(); i++)
    if (m_lapNames[i].length() > maxLength )
      maxLength = m_lapNames[i].length();
  
  if( maxLength < 10 )
    maxLength = 10;
    
  size_t itemWidth = 6;
  std::cout << "Module";

  for (size_t i = 0; i < (maxLength-itemWidth); i++)
    std::cout << " ";

  std::cout << "| It.    ";
  std::cout << "| Total  [s]";
  std::cout << "| / It. [s]    ";
  std::cout << "| %      ";
  std::cout << "\n";
  
  for (size_t i = 0; i < maxLength; i++)
    std::cout << "_";
  std::cout << "_________";
  std::cout << "____________";
  std::cout << "_______________";
  std::cout << "_________";
  std::cout << "\n";
  
  double totalDuration = 0.0;
  for (size_t i = 0; i < m_lapNames.size(); i++)
    totalDuration += m_cummulativeLapTimes[i];
  
  for (size_t i = 0; i < m_lapNames.size(); i++)
  {
    size_t itemWidth = m_lapNames[i].length();
    std::cout << m_lapNames[i];
    for( size_t j = 0; j < (maxLength-itemWidth); j++ )
      std::cout << " ";
    
    std::cout << "| ";
    std::stringstream temp;
    temp << std::fixed << m_lapIterations[i];
    std::string item = temp.str();
    itemWidth = item.length();
    
    std::cout << item;
    for( size_t j = 0; j < 7-itemWidth; j++ )
      std::cout << " ";
    
    std::cout << "| ";
    temp.str("");
    temp << std::fixed << std::setprecision(5) << m_cummulativeLapTimes[i];
    item = temp.str();
    itemWidth = item.length();
    
    std::cout << item;
    for( size_t j = 0; j < 10-itemWidth; j++ )
      std::cout << " ";
    
    std::cout << "| ";
    temp.str("");
    temp << std::fixed << std::setprecision(m_precision) << (m_cummulativeLapTimes[i]/m_lapIterations[i]);
    item = temp.str();
    itemWidth = item.length();
    
    std::cout << item;
    for( size_t j = 0; j < 13-itemWidth; j++ )
      std::cout << " ";
    
    std::cout << "| ";
    temp.str("");
    temp << std::fixed << std::setprecision(2) << 100.0 * (m_cummulativeLapTimes[i]/totalDuration) << "%";
    item = temp.str();
    itemWidth = item.length();

    std::cout << item;
    for( size_t j = 0; j < 7-itemWidth; j++ )
      std::cout << " ";
    
    std::cout << "\n";
  }
  
  std::cout << "\nTotal time consumption: " << totalDuration << "\n";
  
  for( size_t i = 0; i < 2; i++ )
    std::cout << "\n";
}