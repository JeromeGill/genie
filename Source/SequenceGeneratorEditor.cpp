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
<<<<<<< HEAD


    phraseValue.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    sequenceLength.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(&phraseValue);
    addAndMakeVisible(&sequenceLength);
=======
    generatePattern.addListener(this);
>>>>>>> 32630d546c700eb5a22f0b938fff1b24b0da079a
}

SequenceGeneratorEditor::~SequenceGeneratorEditor()
{
<<<<<<< HEAD
    generatePattern.removeListener(this);
=======
>>>>>>> 32630d546c700eb5a22f0b938fff1b24b0da079a
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
    
<<<<<<< HEAD
    generatePattern.setBounds(twoBw, h/4-twoBw, w - fourBw, h/4- twoBw);
    phraseValue.setBounds(twoBw, twoBw, w / 4 - fourBw, h/4 - twoBw);
    sequenceLength.setBounds(w/4 + twoBw, twoBw, w /4 - fourBw, h/4 - twoBw);
}
//==============================================================================
/**@Internal@*/
=======
    generatePattern.setBounds(twoBw, twoBw, w - fourBw, h - fourBw);
    
}

>>>>>>> 32630d546c700eb5a22f0b938fff1b24b0da079a
void SequenceGeneratorEditor::buttonClicked (Button* button){
    if (button == &generatePattern) {
        PrintPattern(GeneratePattern(GetRandomPatternPreset()));
    }
}
<<<<<<< HEAD
/**@Internal@*/
=======
//==============================================================================
>>>>>>> 32630d546c700eb5a22f0b938fff1b24b0da079a
