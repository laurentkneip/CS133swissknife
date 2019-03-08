/***********************************************************************************
 * This file is part of the swissknife library which contains the class examples   *
 * of CS133: Advanced C++ programming at ShanghaiTech (spring semester 2019)       *
 * There is no copyright and there is no license, feel free to do with it          *
 * whatever you want.                                                              *
 ***********************************************************************************/

#include <stdlib.h>

#include <chrono>
#include <thread>
#include <list>

#include "swissknife/profiling/lap_timer.hpp"


int main() {
  swissknife::profiling::LapTimer timer(false,10);

  swissknife::profiling::LapHandle lap1 = timer.addLap( std::string("sleep 10 ms") );
  swissknife::profiling::LapHandle lap2 = timer.addLap( std::string("sleep 5 ms") );
  swissknife::profiling::LapHandle lap3 = timer.addLap( std::string("sleep 1 ms") );

  for (int i = 0; i < 100; i++ ) {
    timer.start(lap1);
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    timer.stop(lap2,true);
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    timer.stop(lap3,true);
    for (int j = 0; j < 10; j++ )
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    timer.stop(10);
  }

  std::list<double> myList;
  swissknife::profiling::LapHandle lap4 = timer.addLap( std::string("push_back into list") );

  timer.start(lap4);
  for (int i = 0; i < 1000; i++)
    myList.push_back(0);
  timer.stop(1000);

  swissknife::profiling::LapHandle lap5 = timer.addLap( std::string("empty for loop") );

  timer.start(lap5);
  for (int i = 0; i < 1000; i++) {}
  timer.stop(1000);

  timer.printSummary();

  return 0;
}
