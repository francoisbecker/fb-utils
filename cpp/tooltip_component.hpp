#ifndef TOOLTIP_COMPONENT_HPP_INCLUDED
#define TOOLTIP_COMPONENT_HPP_INCLUDED

/**
 @file tooltip_component.hpp
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

class TooltipComponent
: public Label
, private Timer
{
public:
    explicit TooltipComponent ()
    : Label("tooltip")
    {
        if (Desktop::getInstance().getMainMouseSource().canHover())
            startTimer (123);
    }
    
    ~TooltipComponent()
    {
        stopTimer();
    }
    
    void displayTip (const String& text)
    {
        setText(text, dontSendNotification);
    }
    
private:
    void timerCallback() override
    {
        Desktop& desktop = Desktop::getInstance();
        const MouseInputSource mouseSource (desktop.getMainMouseSource());
        
        Component* const comp = mouseSource.isMouse() ? mouseSource.getComponentUnderMouse() : nullptr;
        const String tip (getTipFor (comp));
        
        displayTip (tip);
    }
    
    static String getTipFor (Component* c)
    {
        if (TooltipClient* const ttc = dynamic_cast<TooltipClient*> (c))
            if (! c->isCurrentlyBlockedByAnotherModalComponent())
                return ttc->getTooltip();
        
        return String();
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TooltipComponent)
};

#endif
