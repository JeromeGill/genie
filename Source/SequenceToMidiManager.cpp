/*
  ==============================================================================

    SequenceToMidiManager.cpp
    Created: 19 Apr 2013 5:21:45pm
    Author:  Jerome

  ==============================================================================
*/

#include "SequenceToMidiManager.h"

SequenceToMidiManager::SequenceToMidiManager()
//:
//seqGenerator(sequenceGenerator)
{

}

SequenceToMidiManager::~SequenceToMidiManager(){

}

MidiFile& SequenceToMidiManager::writePatternToMidiFile(Pattern pattern, int BPM){
    
    MidiFile *newFile = new MidiFile;
    MidiMessageSequence seq;
    newFile->addTrack(seq);
    
    //A bit cack handed at present
    
    for (int i = 0; i < pattern.size(); i++) {
        int hit = GetPulses(pattern, i);
       
        int noteNumber;
        
        if (hit == 0) {
            noteNumber = 42; //Closed Highhat
        }
        else if (hit == pattern.size()){
            noteNumber = 36; //Kick
        }
        else if (hit == pattern.size() - 1 && hit > 0){
            noteNumber = 38; //Snare
        }
        else if (hit == pattern.size() - 2 && hit > 0){
            noteNumber = 44; //Open Highhat
        }
        else if (hit == pattern.size() - 3 && hit > 0){
            noteNumber = 52; //Cymbol
        }
        else if (hit == pattern.size() - 4 && hit > 0){
            noteNumber = 44; //Open Highhat
        }
        
        double ticks = ((BPM/60)/2) * 1000 * pattern.size() * i;
        double noteLength = (BPM/60) / 2;
        
        float velocity = 1.0;
      
        
        std::cout<<noteNumber<<" "<<velocity<<" / "<<ticks<<" : "<<ticks+noteLength;
    }

    
    return *newFile;
}

void SequenceToMidiManager::addNoteToSequence(MidiMessageSequence Sequence,
                                              int noteNumber,
                                              float velocity,
                                              double ticks,
                                              double duration)
{
    MidiMessage note(juce::MidiMessage::noteOn(1, noteNumber, velocity));
    Sequence.addEvent(note, ticks);
    MidiMessage noteOff(juce::MidiMessage::noteOff(1, noteNumber));
    Sequence.addEvent(noteOff, ticks+duration);
    Sequence.updateMatchedPairs();
    
    
}