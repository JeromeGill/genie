//
//  SequenceEditor.h
//  Genie
//
//  Created by Jerome on 13/10/2012.
//
//

#ifndef __Genie__SequenceEditor__
#define __Genie__SequenceEditor__

#include "genieHeader.h"
#include "genieLogo.h"
#include "SequenceGeneratorEditor.h"

/**==============================================================================
 SequenceEditor is where automatic sequence rearrangments can be generated
 
 Features;
 
 ToDo;
 Export sequence as midifile to host
============================================================================== */
class SequenceEditor :  public Component

{
public:
    SequenceEditor();
    ~SequenceEditor();
    
    //==============================================================================
    /**@Internal@*/
    void paint (Graphics& g);
    /**@Internal@*/
    void resized();
    
    //==============================================================================
    /**@Internal@*/

    
private:

    
    SequenceGeneratorEditor sequenceGenerator;
    const Image genieImage;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceEditor)
    
};

#endif /* defined(__Genie__SequenceEditor__) */
