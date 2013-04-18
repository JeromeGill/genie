/*
  ==============================================================================

    SequenceManager.h
<<<<<<< HEAD
    Created: 5 Apr 2013 5:23:28pm
=======
    Created: 24 Mar 2013 12:26:28pm
>>>>>>> 32630d546c700eb5a22f0b938fff1b24b0da079a
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SEQUENCEMANAGER_H_AAAAC460__
#define __SEQUENCEMANAGER_H_AAAAC460__
<<<<<<< HEAD
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

=======

class SequenceManager
{
public:
    SequenceManager();
    ~SequenceManager();
};



>>>>>>> 32630d546c700eb5a22f0b938fff1b24b0da079a
#endif  // __SEQUENCEMANAGER_H_AAAAC460__
