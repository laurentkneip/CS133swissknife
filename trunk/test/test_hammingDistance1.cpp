#include <stdlib.h>
#include <iostream>
#include "swissknife/profiling/lap_timer.hpp"

void initData( unsigned char * data1, unsigned char * data2 ) {
  for( int i = 0; i < 64; i+=2 ) {
    data1[i] = 0x55; //01010101
    data2[i] = 0x55; //01010101
  }
  for( int i = 1; i < 64; i+=2 ) {
    data1[i] = 0x55; //01010101
    data2[i] = 0xAA; //10101010
  }

  //the Hamming distance between these bit strings should 32*8 = 256!
}

int hammingDistance1( const unsigned char * data1, const unsigned char * data2, size_t bytes ) {
  int XOcount = 0;
  unsigned char temp;
  for( size_t i = 0; i < bytes; i++ )
  {
    temp = data1[i] ^ data2[i];
    if( temp >= 0x80 ) { XOcount++; temp -= 0x80; }
    if( temp >= 0x40 ) { XOcount++; temp -= 0x40; }
    if( temp >= 0x20 ) { XOcount++; temp -= 0x20; }
    if( temp >= 0x10 ) { XOcount++; temp -= 0x10; }
    if( temp >= 0x08 ) { XOcount++; temp -= 0x08; }
    if( temp >= 0x04 ) { XOcount++; temp -= 0x04; }
    if( temp >= 0x02 ) { XOcount++; temp -= 0x02; }
    if( temp >= 0x01 ) { XOcount++; }
  }
  return XOcount;
}

static unsigned char __attribute__((aligned(16))) Data1[64]; //512 bit-string
static unsigned char __attribute__((aligned(16))) Data2[64]; //512 bit-string

int main() {
  //initializes the bit-strings to some values with Hamming distance 256
  initData(Data1,Data2);

  swissknife::profiling::LapTimer timer(false,10);
  swissknife::profiling::LapHandle lap1 = timer.addLap( std::string("test") );

  int result;
  timer.start(lap1);
  for (int i = 0; i < 1000000; i++ )
    result = hammingDistance1(Data1,Data2,64);
  timer.stop(1000000);

  timer.printSummary();
  std::cout << "The result of the Hamming distance function is " << result << "\n";
  return 0;
}