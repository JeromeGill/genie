/*
  ==============================================================================

    SequenceGeneratorEditor.cpp
    Created: 24 Mar 2013 12:33:01pm
    Author:  Jerome

  ==============================================================================
*/

#include "SequenceGeneratorEditor.h"


//==============================================================================
SequenceGeneratorEditor::SequenceGeneratorEditor()

{
    
    generatePattern.addListener(this);
    generatePattern.setButtonText("Generate Pattern");
    addAndMakeVisible(&generatePattern);


    phraseValue.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sequenceLength.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(&phraseValue);
    addAndMakeVisible(&sequenceLength);
}

SequenceGeneratorEditor::~SequenceGeneratorEditor()
{
    generatePattern.removeListener(this);
}

//==============================================================================
/**@Internal@*/
void SequenceGeneratorEditor::paint (Graphics& g)
{
    int w = getWidth();
    int h = getHeight();
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawRect(Bw, Bw, w-twoBw, h-twoBw,Bw);
      
}
/**@Internal@*/
void SequenceGeneratorEditor::resized()
{
    int w = getWidth();
    int h = getHeight();
    
    generatePattern.setBounds(twoBw, h/4-twoBw, w - fourBw, h/4- twoBw);
    phraseValue.setBounds(twoBw, twoBw, w / 4 - fourBw, h/4 - twoBw);
    sequenceLength.setBounds(w/4 + twoBw, twoBw, w /4 - fourBw, h/4 - twoBw);
}
//==============================================================================
/**@Internal@*/
void SequenceGeneratorEditor::buttonClicked (Button* button){
    if (button == &generatePattern) {
        PrintPattern(GeneratePattern(GetRandomPatternPreset()));
    }
}
/**@Internal@*/
