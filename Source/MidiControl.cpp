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
    addAndMakeVisible(&BPM);
    addAndMakeVisible(&LengthInBeats);
    
    LengthInBeats.setRange(0, 128,1);
    LengthInBeats.setTextBoxIsEditable(true);
    LengthInBeats.setVelocityBasedMode(true);
    LengthInBeats.addListener(this);
    
}
MidiControl::~MidiControl(){
    BPM.removeListener(this);
    LengthInBeats.removeListener(this);
}

void MidiControl::paint(Graphics &g){
    g.setColour(Colours::wheat);
    g.fillAll();
    
}
void MidiControl::resized(){
    int w = getWidth();
    int h = getHeight();
    BPM.setBounds(0, 0, w /2, h);
    LengthInBeats.setBounds(w/2, 0, w/2, h);
}

void MidiControl::sliderValueChanged (Slider* slider){
    BPM_ = BPM.getValue();
    LengthInBeats_ = LengthInBeats.getValue();
}