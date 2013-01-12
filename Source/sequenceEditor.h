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


/**==============================================================================
 SequenceEditor is where all the Automatic editing functions can be generated
 
 Features;
 
 ToDo;
============================================================================== */
class SequenceEditor : public Component

{
public:
    SequenceEditor();
    ~SequenceEditor();
    
    //==============================================================================
    /**Internal@*/
    void paint (Graphics& g);
    /**Internal@*/
    void resized();
    
private:
    
    //Types of automatic editing algortythms
    enum
    {
        Edits = 0,
        Rolls,
        TotalFunctions
    };
    
    StringArray hitTypes;

    ComboBox functionOptions;
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceEditor)
    
};

#endif /* defined(__Genie__SequenceEditor__) */
