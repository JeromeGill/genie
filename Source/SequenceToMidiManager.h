/*
  ==============================================================================

    SequenceToMidiManager.h
    Created: 19 Apr 2013 5:21:45pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SEQUENCETOMIDIMANAGER_H_2BDE58C4__
#define __SEQUENCETOMIDIMANAGER_H_2BDE58C4__

#include "genieHeader.h"
#include "AudioSubsectionManager.h"
#include "SequenceGenerator.h"

class SequenceToMidiManager : public SequenceGenerator

{
public:
    SequenceToMidiManager();
    ~SequenceToMidiManager();
    
    void writePatternToMidiFile(MidiFile& file, Pattern pattern, int BPM);
    
    void addNoteToSequence(MidiMessageSequence& Sequence,
                           int noteNumber,
                           float velocity,
                           double ticks,
                           double duration);
    void exportMidiFile(MidiFile &f);
private:
    
    OwnedArray<MidiFile> midiFiles;
    MidiMessageSequence* seq;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceToMidiManager)
};



#endif  // __SEQUENCETOMIDIMANAGER_H_2BDE58C4__
