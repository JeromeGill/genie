/*
  ==============================================================================

    SequenceGeneratorEditor.h
    Created: 24 Mar 2013 12:33:01pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SEQUENCEGENERATOREDITOR_H_86DD913__
#define __SEQUENCEGENERATOREDITOR_H_86DD913__

#include "genieHeader.h"
#include "SequenceGenerator.h"
/**==============================================================================
 SequenceGeneratorEditor provides an interface for @SequenceGenerator
 
 Features;
 Inherits from @SequenceGenerator
 
 ToDo;
 Export sequence as midifile to host
 ============================================================================== */
class SequenceGeneratorEditor : public Component,
                                public ButtonListener,
                                public SequenceGenerator

{
public:
    SequenceGeneratorEditor();
    ~SequenceGeneratorEditor();
    
    //==============================================================================
    /**@Internal@*/
    void paint (Graphics& g);
    /**@Internal@*/
    void resized();
    
    //==============================================================================
    /**@Internal@*/
    void buttonClicked (Button* button);

    
private:
    
    TextButton generatePattern;
    
    OwnedArray<Button> hitGrid;
    OwnedArray<Slider> slider;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceGeneratorEditor)
    
};



#endif  // __SEQUENCEGENERATOREDITOR_H_86DD913__
