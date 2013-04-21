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
#include "SequenceGeneratorEditor.h"


/**==============================================================================
 SequenceEditor is where automatic sequence rearrangments can be generated
 
 Features;
 
 ToDo;
 Export sequence as midifile to host
============================================================================== */
class SequenceEditor :  public Component,
                        public Slider::Listener,
                        public SequenceGenerator::Listener

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
    void displayPattern(Pattern pattern, MonomeDisplay& display);
    void displayPatternTotals(Pattern pattern, MonomeDisplay& display);
    
    /**@Internal@*/
    void sliderValueChanged(Slider* slider);
    
    void patternGenerated(Pattern& p);
private:

    SequenceGeneratorEditor sequenceGenerator;
    MonomeDisplay sequenceDisplay;
    MonomeDisplay totalDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceEditor)
    
};

#endif /* defined(__Genie__SequenceEditor__) */
