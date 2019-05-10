#include <stdlib.h>
#include <iostream>
#include <tmmintrin.h>
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

static const char __attribute__((aligned(16))) MASK_4bit[16] = {0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf};
static const uint8_t __attribute__((aligned(16))) POPCOUNT_4bit[16] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
static const __m128i shiftval = _mm_set_epi32 (0,0,0,4);

__inline__
uint32_t hammingDistance2(const __m128i* signature1, const __m128i* signature2, const int numberOf128BitWords ) {
  uint32_t result = 0;

  register __m128i xmm0;
  register __m128i xmm1;
  register __m128i xmm2;
  register __m128i xmm3;
  register __m128i xmm4;
  register __m128i xmm5;
  register __m128i xmm6;
  register __m128i xmm7;

  xmm7 = _mm_load_si128 ((__m128i *)POPCOUNT_4bit);
  xmm6 = _mm_load_si128 ((__m128i *)MASK_4bit);
  xmm5 = _mm_setzero_si128();

  const size_t end=(size_t)(signature1+numberOf128BitWords);

  xmm4 = xmm5;

  do {
    xmm0 = _mm_xor_si128 ( (__m128i)*signature1++, (__m128i)*signature2++);
    xmm1 = xmm0;
    xmm1 = _mm_srl_epi16 (xmm1, shiftval);
    xmm0 = _mm_and_si128 (xmm0, xmm6);
    xmm1 = _mm_and_si128 (xmm1, xmm6);
    xmm2 = xmm7;
    xmm3 = xmm7;
    xmm2 = _mm_shuffle_epi8(xmm2, xmm0);
    xmm3 = _mm_shuffle_epi8(xmm3, xmm1);
    xmm4 = _mm_add_epi8(xmm4, xmm2);
    xmm4 = _mm_add_epi8(xmm4, xmm3);
  }
  while((size_t)signature1<end);
  xmm4 = _mm_sad_epu8(xmm4, xmm5);
  xmm5 = _mm_add_epi32(xmm5, xmm4);
  
  xmm0 = _mm_cvtps_epi32(_mm_movehl_ps(_mm_cvtepi32_ps(xmm0), _mm_cvtepi32_ps(xmm5)));
  xmm0 = _mm_add_epi32(xmm0, xmm5);
  result = _mm_cvtsi128_si32 (xmm0);
  return result;
}

static unsigned char __attribute__((aligned(16))) Data1[64];
static unsigned char __attribute__((aligned(16))) Data2[64];

int main() {
  //initializes the bit-strings to some values with Hamming distance 256
  initData(Data1,Data2);

  swissknife::profiling::LapTimer timer(false,10);
  swissknife::profiling::LapHandle lap1 = timer.addLap( std::string("test") );

  int result;
  timer.start(lap1);
  for (int i = 0; i < 1000000; i++)
    result = hammingDistance2((__m128i*) Data1,(__m128i*) Data2, 4);
  timer.stop(1000000);

  timer.printSummary();
  std::cout << "The result of the Hamming distance function is " << result << "\n";
  return 0;
}