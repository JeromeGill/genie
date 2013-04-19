/*
  ==============================================================================

    MidiFileGenerator.h
    Created: 19 Apr 2013 11:31:02am
    Author:  Jerome

  ==============================================================================
*/

#ifndef __MIDIFILEGENERATOR_H_8A2B81CA__
#define __MIDIFILEGENERATOR_H_8A2B81CA__

#include "genieHeader.h"

class MidiFileGenerator {
    
public:
    MidiFileGenerator();
    ~MidiFileGenerator();
    
    void AddNoteAtTime(MidiFile* midiFile, int noteNumber, int velocity, int channel, double time);
};



#endif  // __MIDIFILEGENERATOR_H_8A2B81CA__
