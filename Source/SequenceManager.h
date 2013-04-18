/*
  ==============================================================================

    SequenceManager.h
    Created: 5 Apr 2013 5:23:28pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SEQUENCEMANAGER_H_AAAAC460__
#define __SEQUENCEMANAGER_H_AAAAC460__
#include <iostream>
#include <vector>
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
};

#endif  // __SEQUENCEMANAGER_H_AAAAC460__
