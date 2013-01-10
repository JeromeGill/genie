/*
  ==============================================================================

    MidiManager.cpp
    Created: 4 Jan 2013 7:05:04pm
    Author:  Jerome

  ==============================================================================
*/

#include "MidiManager.h"

MidiManager::MidiManager(PolyAudioFilePlayer& polyAudioFilePlayer_,
                         AudioSubsectionManager& audioSubsectionManager_,
                         MidiKeyboardState &keyboardState_)
: subsections(audioSubsectionManager_),
player(polyAudioFilePlayer_),
state(keyboardState_)
{
    state.addListener(this);
}

MidiManager::~MidiManager(){
    state.removeListener(this);
}

void MidiManager::handleNoteOn (MidiKeyboardState* source,
                                 int midiChannel, int midiNoteNumber, float velocity){
    
    std::cout<<"NoteNumber = "<<midiNoteNumber<<"\n";
    if (midiNoteNumber >= 48) playSubsection(midiNoteNumber - 48, velocity);
}

void MidiManager::handleNoteOff (MidiKeyboardState* source,
                                  int midiChannel, int midiNoteNumber){
    if (midiNoteNumber >= 48) stopSubsection(midiNoteNumber - 48);
}

void MidiManager::playSubsection(int subsectionIndex, float gain){
    std::cout<<"SM: Playing slice"<<subsectionIndex<<"\n";
    if (subsections.size() > subsectionIndex) {        
        player.playSubSection(subsections.getStart(subsectionIndex),
                              subsections.getLength(subsectionIndex),
                              gain);
        
    }
    else std::cout<<"playSlice subsectionIndex "<<subsectionIndex<<" out of scope \n";
    
}
void MidiManager::stopSubsection(int subsectionIndex){
    
    if (subsections.size() > subsectionIndex) {
        player.stopVoice(subsectionIndex);
        std::cout<<"stopSlice subsectionIndex "<<subsectionIndex<<"\n";
    }
    else std::cout<<"stopSlice subsectionIndex "<<subsectionIndex<<" out of scope \n";
    
}