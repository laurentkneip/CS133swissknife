/***********************************************************************************
 * This file is part of the swissknife library which contains the class examples   *
 * of CS133: Advanced C++ programming at ShanghaiTech (spring semester 2019)       *
 * There is no copyright and there is no license, feel free to do with it          *
 * whatever you want.                                                              *
 ***********************************************************************************/

#ifndef SWISSKNIFE_LUT_SQRTCALC_HPP_
#define SWISSKNIFE_LUT_SQRTCALC_HPP_

#include <stdlib.h>


namespace swissknife {
namespace lut {

/*! \brief A look-up table based class for computing square root values
 *
 *  SqrtCalc computes square roots based on a look-up table of precomputed square root
 *  values. The precomputed values are just for a few numbers and the table with the values
 *  is generated at build time by a compiled code-generator function (make_sqrt_lut). The
 *  class currently is just a toy example illustrating this functionlity, consider to
 *  extend it to be more flexible.
 */

class SqrtCalc {
public:
  SqrtCalc();
  virtual ~SqrtCalc();

  /*! \brief function for calculating the square root
   *  \param[in] val The value of which we want to compute the square root.
   *  \return The square root of the value (up to discretization errors given by look-up table).
   */
  double calc( double val );
};

}
}

#endif