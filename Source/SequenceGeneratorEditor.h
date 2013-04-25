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
#include "MonomeDisplay.h"



/**==============================================================================
 SequenceGeneratorEditor provides an interface for @SequenceGenerator
 
 Features;
 Inherits from @SequenceGenerator
 
 ToDo;
 Export sequence as midifile to host
 ============================================================================== */
class SequenceGeneratorEditor : public Component,
                                public ButtonListener,
                                public Slider::Listener,
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
    /**@Internal@*/
    void sliderValueChanged (Slider* slider);

    void addSliderListeners (Slider::Listener *listener);
    void removeSliderListeners (Slider::Listener *listener);
    
private:
    Pattern *p;
    OwnedArray<Pattern> pattern;
    OwnedArray<Label> labels;
    TextButton generatePattern;
    TextButton savePattern;
    OwnedArray<Slider> slider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceGeneratorEditor)
    
};



#endif  // __SEQUENCEGENERATOREDITOR_H_86DD913__
