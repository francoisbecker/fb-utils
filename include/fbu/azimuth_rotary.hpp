#ifndef AZIMUTH_ROTARY_HPP_INCLUDED
#define AZIMUTH_ROTARY_HPP_INCLUDED

/**
 @file azimuth_rotary.hpp
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
 @class AzimuthRotary
 A Juce rotary encoder that loops between 180° and -180° and uses the
 trigonometric convention: positive left.
 */
class AzimuthRotary
: public Slider
{
public:
    AzimuthRotary (const String& componentName)
    : Slider (componentName)
    {
        setDoubleClickReturnValue(true, 0.);
        setSliderStyle (Slider::Rotary); // TODO: support Slider::RotaryHorizontalVerticalDrag;
        setRotaryParameters({M_PIf, 3.f * M_PIf, false});
        setMouseCursor(MouseCursor::CrosshairCursor);
    }
    double proportionOfLengthToValue (double proportion) override
    {
        return 1.0 - Slider::proportionOfLengthToValue(proportion);
    }
    double valueToProportionOfLength (double value) override
    {
        return 1.0 - Slider::valueToProportionOfLength(value);
    }
    void mouseDown (const MouseEvent& e) override
    {
        // TODO: windows port
        if (e.mods.isCtrlDown() && e.mods.isCommandDown()) // PT automation menu
        {
            return;
        }
        Slider::mouseDown(e);
    }
    void mouseDoubleClick (const MouseEvent& e) override
    {
        // TODO: windows port
        if (e.mods.isCtrlDown() && e.mods.isCommandDown()) // PT automation menu
        {
            return;
        }
        Slider::mouseDoubleClick(e);
    }
};

#endif
