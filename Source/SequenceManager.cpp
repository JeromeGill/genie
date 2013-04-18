/*
  ==============================================================================

    SequenceManager.cpp
    Created: 5 Apr 2013 5:23:28pm
    Author:  Jerome

  ==============================================================================
*/

#include "SequenceManager.h"

SequenceManager::SequenceManager(AudioSubsectionManager audioSubsectionManager,
                                  SequenceGenerator seqGenerator)
: subsection(audioSubsectionManager),
seqGenerator(seqGenerator)
{
    
}