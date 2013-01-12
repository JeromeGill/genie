/*
  ==============================================================================

    MidiControl.cpp
    Created: 5 Jan 2013 7:55:46pm
    Author:  Jerome

  ==============================================================================
*/

#include "MidiControl.h"

MidiControl::MidiControl()

{
    addAndMakeVisible(&LengthInBeats);
    
    LengthInBeats.setRange(0, 128,1);
    LengthInBeats.setTextBoxIsEditable(true);
    LengthInBeats.setVelocityBasedMode(true);
    LengthInBeats.addListener(this);
    
}
MidiControl::~MidiControl(){
    LengthInBeats.removeListener(this);
}

void MidiControl::paint(Graphics &g){
    g.setColour(Colours::white);
    g.fillAll();
    
}
void MidiControl::resized(){
    int w = getWidth();
    int h = getHeight();
    LengthInBeats.setBounds(0, 0, w, h);
}

void MidiControl::sliderValueChanged (Slider* slider){
    LengthInBeats_ = LengthInBeats.getValue();
}