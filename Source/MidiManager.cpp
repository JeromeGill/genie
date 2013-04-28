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

//====================================================================================
/** Requests a voice from a PolyAudioFilePlayer for a subsection
 */
void MidiManager::handleNoteOn (MidiKeyboardState* source,
                                 int midiChannel, int midiNoteNumber, float velocity){
    
    std::cout<<"NoteNumber = "<<midiNoteNumber<<"\n";
    if (midiNoteNumber >= 48) playSubsection(midiNoteNumber - 48, velocity);
}
/** Stops the voice PolyAudioFilePlayer voice playing a subsection if any
 */
void MidiManager::handleNoteOff (MidiKeyboardState* source,
                                  int midiChannel, int midiNoteNumber){
    if (midiNoteNumber >= 48) stopSubsection(midiNoteNumber - 48);
}
//====================================================================================
/**@Internal@*/
void MidiManager::playSubsection(int subsectionIndex, float gain){
    std::cout<<"SM: Playing slice"<<subsectionIndex<<"\n";
    if (subsections.size() > subsectionIndex) {        
        player.playSubSection(subsections[subsectionIndex].StartSample,
                              subsections[subsectionIndex].LengthInSamples,
                              gain);
        
    }
    else std::cout<<"playSlice subsectionIndex "<<subsectionIndex<<" out of scope \n";
    
}
/**@Internal@*/
void MidiManager::stopSubsection(int subsectionIndex){
    
    if (subsections.size() > subsectionIndex) {
        player.stopVoice(subsectionIndex);
        std::cout<<"stopSlice subsectionIndex "<<subsectionIndex<<"\n";
    }
    else std::cout<<"stopSlice subsectionIndex "<<subsectionIndex<<" out of scope \n";
    
}