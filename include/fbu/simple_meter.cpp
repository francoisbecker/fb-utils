/**
 @file simple_meter.cpp
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

#include "fbu/simple_meter.hpp"

//==============================================================================
SimpleMeter::SimpleMeter(String pName)
: mPeak(0.f)
, mName(pName)
{
}

//==============================================================================
SimpleMeter::~SimpleMeter()
{
}

//==============================================================================
void SimpleMeter::process(const float* pBuffer, int pNumSamples)
{
    Range<float> lMinMax = FloatVectorOperations::findMinAndMax(pBuffer, pNumSamples);
    float lCurrentPeak = std::max(-lMinMax.getStart(), lMinMax.getEnd());
    
    if (lCurrentPeak >= 1.f)
    {
        // TODO: PEAK FLASH
    }
    
    bool lWasZero = mPeak.compareAndSetBool(lCurrentPeak, 0.f);
    if (!lWasZero)
    {
        float lPreviousPeak = mPeak.get();
        if (lPreviousPeak < lCurrentPeak)
        {
            mPeak.set(lCurrentPeak);
        }
    }
    
    //std::cerr << mName.toRawUTF8() << ":" << mPeak.get() << std::endl;
}

//==============================================================================
float SimpleMeter::getPeakAmplitudeAndReset()
{
    float lPeak = mPeak.exchange(0.f);
    return lPeak;
}

//==============================================================================
float SimpleMeter::getPeakDBAndReset()
{
    float lPeak = getPeakAmplitudeAndReset();
    float lPeakDB = 20.f * std::log10(lPeak);
    if (lPeakDB < -144.f || !std::isnormal(lPeakDB))
    {
        lPeakDB = -144.f;
    }
    return lPeakDB;
}

//==============================================================================
//==============================================================================
//==============================================================================
SimpleMeterComponent::SimpleMeterComponent(SimpleMeter* pSimpleMeter, int pHz)
: mSimpleMeter(pSimpleMeter)
, mPeakDB(-144.f)
, mForegroundColour(Colours::lightgreen)
, mBackgroundColour(Colours::black)
{
    jassert(pSimpleMeter);
    startTimerHz(pHz);
    
    setBounds(0, 0, 5, 144);
}

//==============================================================================
SimpleMeterComponent::~SimpleMeterComponent()
{
    stopTimer();
}

//==============================================================================
void SimpleMeterComponent::setForegroundColour(Colour pColour)
{
    mForegroundColour = pColour;
}

//==============================================================================
void SimpleMeterComponent::setBackgroundColour(Colour pColour)
{
    mBackgroundColour = pColour;
}

//==============================================================================
void SimpleMeterComponent::paint (Graphics& g)
{
#if 0
    g.fillAll(mBackgroundColour);
#else
    g.setFillType(mBackgroundColour);
    g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), getWidth()/2);
#endif
    
    g.setImageResamplingQuality(Graphics::ResamplingQuality::lowResamplingQuality);
    
    float lOldPeakDB = mPeakDB;
    mPeakDB = mSimpleMeter->getPeakDBAndReset();
    
    if (mPeakDB == -144.f)
    {
        mPeakDB = std::max(lOldPeakDB - 10.f, -144.f);
    }
    
    float lNormalizedPeakDB = (mPeakDB + 144.f)/144.f;
    float lSkewed = std::pow(lNormalizedPeakDB, 4.f);
    float lHeight = lSkewed * getHeight();
    
#if 0
    g.setColour(mForegroundColour);
    g.fillRect(Rectangle<int>(0, getHeight() - lHeight, getWidth(), lHeight+1));
#else
    g.setFillType(mForegroundColour);
    g.fillRoundedRectangle(0, getHeight() - lHeight, getWidth(), lHeight, getWidth()/2);
#endif
}

//==============================================================================
void SimpleMeterComponent::timerCallback()
{
    jassert(mSimpleMeter);

    repaint();
    
    // TODO: if too many repaint calls without actual repaint, actually call a reset on the peak value (?)
}
