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

//==============================================================================
/** SequenceGeneratorEditor
 \brief SequenceGeneratorEditor provides an interface for SequenceGenerator

*/
//==============================================================================
class SequenceGeneratorEditor : public Component,
                                public ButtonListener,
                                public Slider::Listener,
                                public SequenceGenerator

{
public:
    SequenceGeneratorEditor();
    ~SequenceGeneratorEditor();
    
    //==============================================================================
    /** @internal*/
    void paint (Graphics& g);
    /** @internal*/
    void resized();
    
    //==============================================================================
    /** @internal*/
    void buttonClicked (Button* button);
    /** @internal*/
    void sliderValueChanged (Slider* slider);

    void addSliderListeners (Slider::Listener *listener);
    void removeSliderListeners (Slider::Listener *listener);
    
private:

    OwnedArray<Label> labels;
    TextButton generatePattern;
    OwnedArray<Slider> slider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceGeneratorEditor)
    
};



#endif  // __SEQUENCEGENERATOREDITOR_H_86DD913__
