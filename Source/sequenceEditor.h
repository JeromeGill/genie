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
#include "genieLogo.h"



//==============================================================================
/**SequenceEditor
 \brief SequenceEditor displays a SequenceGeneratorEditor interface and results 

 It displays two MonomeDisplay objects
 One for a generative sequence and the second for the cumulative value of each position of that sequence.
 
 Genie Logo design - [RyanHegarty]
 
 [RyanHegarty]: http://ryanhegarty.co.uk/ (RyanHegarty)
*/
//==============================================================================
class SequenceEditor :  public Component,
                        public Slider::Listener,
                        public ButtonListener,
                        public SequenceGenerator::Listener

{
public:
    SequenceEditor();
    ~SequenceEditor();
    
    //==============================================================================
    /** @internal */
    void paint (Graphics& g);
    /** @internal */
    void resized();
    
    //==============================================================================
    /** @internal */
    void displayPattern(Pattern pattern, MonomeDisplay& display);
    void displayPatternTotals(Pattern pattern, MonomeDisplay& display);
    
    /** @internal */
    void sliderValueChanged(Slider* slider);
    /** @internal*/
    void buttonClicked (Button* button);
    /** @internal*/
    void patternGenerated(Pattern& p);
private:

    
    SequenceGeneratorEditor sequenceGenerator;
    MonomeDisplay sequenceDisplay;
    MonomeDisplay totalDisplay;
    
    
    TextButton savePattern1;
    TextButton savePattern2;
    
    const Image genieImage;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceEditor)
    
};

#endif /* defined(__Genie__SequenceEditor__) */
