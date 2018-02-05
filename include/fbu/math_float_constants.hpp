#ifndef MATH_FLOAT_CONSTANTS_HPP_INCLUDED
#define MATH_FLOAT_CONSTANTS_HPP_INCLUDED

/**
 @file math_float_constants.hpp
 @author François Becker

MIT License

Copyright (c) 2015-2017 François Becker

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <cmath>

#if _MSC_VER
#include <cstdint>
#endif

// standard float
#define M_Ef        (static_cast<float>(M_E))
#define M_LOG2Ef    (static_cast<float>(M_LOG2E))
#define M_LOG10Ef   (static_cast<float>(M_LOG10E))
#define M_LN2f      (static_cast<float>(M_LN2))
#define M_LN10f     (static_cast<float>(M_LN10))
#define M_PIf       (static_cast<float>(M_PI))
#define M_PI_2f     (static_cast<float>(M_PI_2))
#define M_PI_4f     (static_cast<float>(M_PI_4))
#define M_1_PIf     (static_cast<float>(M_1_PI))
#define M_2_PIf     (static_cast<float>(M_2_PI))
#define M_2_SQRTPIf (static_cast<float>(M_2_SQRTPI))
#define M_SQRT2f    (static_cast<float>(M_SQRT2))
#define M_SQRT1_2f  (static_cast<float>(M_SQRT1_2))

// custom-defined double
#define M_SQRT3            1.7320508075688772935274463415058724
#define M_SQRT1_3          0.5773502691896257645091487805019574556
#define M_SQRT6            2.4494897427831780981972840747058914
#define M_SQRT1_6          0.408248290463863016366214012450981899
#define EPSILON_POWER      0.0000000000000001
#define EPSILON_AMPLITUDE  0.00000001

// custom-defined float
#define M_SQRT3f           (static_cast<float>(M_SQRT3))
#define M_SQRT1_3f         (static_cast<float>(M_SQRT1_3))
#define M_SQRT6f           (static_cast<float>(M_SQRT6))
#define M_SQRT1_6f         (static_cast<float>(M_SQRT1_6))
#define EPSILON_POWERf     (static_cast<float>(EPSILON_POWER))
#define EPSILON_AMPLITUDEf (static_cast<float>(EPSILON_AMPLITUDE))

#endif
