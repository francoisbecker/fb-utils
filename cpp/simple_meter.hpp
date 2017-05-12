#ifndef SIMPLE_METER_HPP_INCLUDED
#define SIMPLE_METER_HPP_INCLUDED

/**
 @file simple_meter.hpp
 @author François Becker
 
MIT License

Copyright (c) 2016-2017 François Becker

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

class SimpleMeter
{
public:
    SimpleMeter(String pName = "");
    virtual ~SimpleMeter();
    
    void process(const float* pBuffer, int pNumSamples);
    
    float getPeakAmplitudeAndReset();
    float getPeakDBAndReset();
    
    void setName(String pName)
    {
        mName = pName;
    }
    
private:
    Atomic<float> mPeak;
    String        mName;
};

class SimpleMeterComponent
: public Component
, public SettableTooltipClient
, private Timer
{
public:
    /**
     Constructor
     */
    SimpleMeterComponent(SimpleMeter* pSimpleMeter, int pHz = 20);
    
    /**
     Virtual destructor
     */
    virtual ~SimpleMeterComponent();
    
    void setForegroundColour(Colour pColour);
    void setBackgroundColour(Colour pColour);
    
    void timerCallback() override;
    
private:
    void paint (Graphics& g) override;
    
    SimpleMeter* mSimpleMeter;
    
    float mPeakDB;
    
    Colour mForegroundColour;
    Colour mBackgroundColour;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleMeterComponent);
};

#endif
