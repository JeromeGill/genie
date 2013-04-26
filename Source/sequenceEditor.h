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


//==============================================================================
/**
 \brief SequenceEditor displays a SequenceGeneratorEditor interface and results 

 It displays two MonomeDisplay objects
 One for a generative sequence and the second for the cumulative value of each position of that sequence.
*/
//==============================================================================
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
