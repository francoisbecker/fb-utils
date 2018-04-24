#ifndef MULTICHANNEL_METERS_HPP_INCLUDED
#define MULTICHANNEL_METERS_HPP_INCLUDED

/**
 @file multichannel_meters.hpp
 @author François Becker
 
MIT License

Copyright (c) 2016-2018 François Becker

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

#include "fbu/simple_meter.hpp"

class MultichannelMeters
: public Component
, private Timer
{
public:
    MultichannelMeters(int pHz = 0)
    : Component()
    , Timer()
    {
        startTimerHz(pHz);
    }
    
    ~MultichannelMeters()
    {
        stopTimer();
    }
    
    /**
     Always call this referring to the same pMeters array, or if the pMeters
     array changes, call first updateNumMeters(nullptr, 0) to remove references
     to the previous array.
     */
    void updateNumMeters(SimpleMeter* pMeters, int pNumChannels)
    {
        if (pNumChannels != mMeterComponents.size())
        {
            // Growth
            while (mMeterComponents.size() < pNumChannels)
            {
                SimpleMeterComponent* lSMC = new SimpleMeterComponent(&pMeters[mMeterComponents.size()], 0);
                addAndMakeVisible(lSMC);
                lSMC->setForegroundColour(Colours::grey);
                mMeterComponents.add(lSMC);
                
                Label* lLabel = new Label();
                addAndMakeVisible(lLabel);
                lLabel->setJustificationType(Justification::centred);
                lLabel->setEditable(false, false, false);
                lLabel->setColour(Label::textColourId, Colour(0xffa0a0a0));
                mMeterLabels.add(lLabel);
            }
            
            // Shrink
            while (mMeterComponents.size() > pNumChannels)
            {
                mMeterComponents.remove(mMeterComponents.size() - 1, true);
                mMeterLabels.remove(mMeterLabels.size() - 1, true);
            }
            
            // reposition everything
            int i = 0;
            for (SimpleMeterComponent* lSMC : mMeterComponents)
            {
                lSMC->setBounds(getWidth()/2 - pNumChannels * 5 + 2 + i * 10, 0, 5, 144/5);
                ++i;
            }
            i = 0;
            for (Label* lLabel : mMeterLabels)
            {
                lLabel->setBorderSize(BorderSize<int>(0, 0, 0, 0));
                lLabel->setBounds(getWidth()/2 - pNumChannels * 5 - 1 + i * 10, 144/5 + 4, 11, 18);
                ++i;
            }
        }
    }
    
    /**
     Call this with an array of strings that is greater or equal to the number
     of meters that has been configured.
     */
    void updateLabels(const char* const * pLabels)
    {
        int i = 0;
        for (Label* lLabel : mMeterLabels)
        {
            lLabel->setText(pLabels[i], dontSendNotification);
            lLabel->setMinimumHorizontalScale(0.01f);
            lLabel->setTooltip(pLabels[i]);
            ++i;
        }
        i = 0;
        for (SimpleMeterComponent* lSMC : mMeterComponents)
        {
            lSMC->setTooltip(pLabels[i]);
            ++i;
        }
    }
    
    /**
     This can be called directly if this component has been intantiated with a
     refresh rate of 0
     */
    void timerCallback() override
    {
        for (SimpleMeterComponent* lSMC : mMeterComponents)
        {
            lSMC->timerCallback();
        }
    }
    
private:
    OwnedArray<SimpleMeterComponent> mMeterComponents;
    OwnedArray<Label>                mMeterLabels;
};

#endif

