#ifndef ELEVATION_ROTARY_HPP_INCLUDED
#define ELEVATION_ROTARY_HPP_INCLUDED

/**
 @file elevation_rotary.hpp
 @author François Becker

MIT License

Copyright (c) 2017 François Becker

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

#include "JuceHeader.h"

#include "fbu/math_float_constants.hpp"

/**
 @class ElevationRotary
 A Juce rotary encoder dedicated to elevation.
 */
class ElevationRotary
: public Slider
{
public:
    ElevationRotary (const String& componentName)
    : Slider (componentName)
    {
        setDoubleClickReturnValue(true, 0.);
        setSliderStyle (Slider::RotaryVerticalDrag);
        setRotaryParameters({M_PIf, 2.f * M_PIf, false});
    }
};

#endif
