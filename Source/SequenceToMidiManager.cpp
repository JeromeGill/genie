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

void SequenceToMidiManager::writePatternToMidiFile(MidiFile& newFile, Pattern pattern, int BPM){
    

    MidiMessageSequence *seq = new MidiMessageSequence;
    
    newFile.addTrack(*seq);
    
    
    newFile.setSmpteTimeFormat (4,
                                 25);
    //newFile->setTicksPerQuarterNote (tpq);
    

    //A bit cack handed at present
    
    for (int i = 0; i < pattern[0].size(); i++) {
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
        
        double ticks = 60.0/(double)BPM * 0.5 * i *1000;
        double noteLength = (60.0/(double)BPM * 0.5 *1000);
        
        float velocity = 1.0;
      
        
        std::cout<<noteNumber<<" "<<velocity<<" / "<<ticks<<" : "<<ticks+noteLength<<"\n";
        
        addNoteToSequence(*seq, noteNumber, velocity, ticks, ticks+noteLength);
    }

    
    //return newFile;
}

void SequenceToMidiManager::addNoteToSequence(MidiMessageSequence& Sequence,
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

void SequenceToMidiManager::exportMidiFile(MidiFile &f){
    File midiSequencefile;
    
}