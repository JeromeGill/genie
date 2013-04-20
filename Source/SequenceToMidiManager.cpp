/*
  ==============================================================================

    SequenceToMidiManager.cpp
    Created: 19 Apr 2013 5:21:45pm
    Author:  Jerome

  ==============================================================================
*/

#include "SequenceToMidiManager.h"

SequenceToMidiManager::SequenceToMidiManager(SequenceGenerator &sequenceGenerator,
                                AudioSubsectionManager &subsectionManager)
: subsection(subsectionManager),
seqGenerator(sequenceGenerator)
{

}

SequenceToMidiManager::~SequenceToMidiManager(){

}

MidiFile SequenceToMidiManager::writePatternToMidiFile(Pattern pattern){
    MidiFile newFile;
}