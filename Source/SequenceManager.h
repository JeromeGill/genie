/*
  ==============================================================================

    SequenceManager.h

    Created: 5 Apr 2013 5:23:28pm

  ==============================================================================
*/

#ifndef __SEQUENCEMANAGER_H_AAAAC460__
#define __SEQUENCEMANAGER_H_AAAAC460__
#include "AudioSubsectionManager.h"
#include "SequenceGenerator.h"
#include "genieHeader.h"


/**==============================================================================
 
 SequenceManager
 
 Sequences of AudioSubsections are written to midifiles.
 
==============================================================================*/
class SequenceManager {    
public:
    SequenceManager(AudioSubsectionManager audioSubsectionManager,
                    SequenceGenerator seqGenerator);
    ~SequenceManager();

private:
    SequenceGenerator& seqGenerator;
    AudioSubsectionManager& subsection;
    OwnedArray<MidiFile> midiFiles;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceManager)
};

#endif  // __SEQUENCEMANAGER_H_AAAAC460__
