/*
  ==============================================================================

    SliceComponent.cpp
    Created: 24 Mar 2013 12:34:37pm
    Author:  Jerome

  ==============================================================================
*/

#include "SliceComponent.h"

SliceComponent::SliceComponent()
{
    addAndMakeVisible(&Name);
    Name.addListener(this);
}

SliceComponent::~SliceComponent(){
    Name.removeListener(this);
}

void SliceComponent::paint(Graphics &g){
    g.fillAll(Colours::black);
    
    int w = getWidth();
    int h = getHeight();
    if (subsectionWaveform.isValid()) {
        g.drawImageAt(subsectionWaveform.rescaled(getWidth() - fourBw,
                                                  getHeight() - fourBw),
                      twoBw,
                      twoBw);
    }
    Name.setBounds(0, 0, w, h);
    
}

void SliceComponent::resized(){
    repaint();
}


void SliceComponent::labelTextChanged (Label* labelThatHasChanged){
    repaint();
}