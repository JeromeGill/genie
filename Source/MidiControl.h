/*
  ==============================================================================

    MidiControl.h
    Created: 5 Jan 2013 7:55:46pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __MIDICONTROL_H_977D099C__
#define __MIDICONTROL_H_977D099C__

#include "genieHeader.h"

/**
 MidiControl provides an interface for exporting slice time values as a MidiFile
 
 Features;
 
 ToDo;
    convert the number of beats between two times into a BPM
    
 */
class MidiControl : public Component,
public Slider::Listener
{
public:
    MidiControl();
    ~MidiControl();
    
    void paint(Graphics &g);
    void resized();
    
    void sliderValueChanged (Slider* slider);
private:
    int LengthInBeats_;
    int BPM_;
    
    
    Slider LengthInBeats;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiControl)
};



#endif  // __MIDICONTROL_H_977D099C__
