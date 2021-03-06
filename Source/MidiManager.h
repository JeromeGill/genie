/*
  ==============================================================================

    MidiManager.h
    Created: 4 Jan 2013 7:05:04pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __MIDIMANAGER_H_92CD5FEC__
#define __MIDIMANAGER_H_92CD5FEC__

#include "genieHeader.h"
#include "PolyAudioFilePlayer.h"
#include "SubSection.h"
#include "AudioSubsectionManager.h"

//====================================================================================
/**MidiManager

 \brief MidiManager provides a MIDI interaction between PolyAudioFilePlayer and AudioSubsectionManager
 
   It utilises the Juce [MidiKeyboardState] method of MidiIO
 
 [MidiKeyboardState]: http://rawmaterialsoftware.com/juce/api/classMidiKeyboardState.html (juce::MidiKeyboardState)
*/
//====================================================================================

class MidiManager : public  MidiKeyboardStateListener
{
    
    MidiKeyboardState& state;
    PolyAudioFilePlayer& player;
    AudioSubsectionManager& subsections;

public:
    MidiManager(PolyAudioFilePlayer& polyAudioFilePlayer_,
                AudioSubsectionManager& audioSubsectionManager_,
                MidiKeyboardState &keyboardState_);
    ~MidiManager();
    
    //====================================================================================
    /** Requests a voice from a PolyAudioFilePlayer for a subsection
     */
    void playSubsection(int subsectionIndex, float gain);
    /** Stops the voice PolyAudioFilePlayer voice playing a subsection if any
     */
    void stopSubsection(int subsectionIndex);
    //====================================================================================
    /** @internal */
    void handleNoteOn (MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity);
    /** @internal */
    void handleNoteOff (MidiKeyboardState* source, int midiChannel, int midiNoteNumber);
    
    
private:
  
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiManager)
};



#endif  // __MIDIMANAGER_H_92CD5FEC__
