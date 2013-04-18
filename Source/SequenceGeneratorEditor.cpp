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


    slider.add(new Slider("SequenceLength"));
    slider.add(new Slider("SequenceDepth"));

    slider[0]->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    slider[0]->setRange(1, 5, 1);
    slider[1]->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    slider[1]->setRange(1, 4, 1);
    
    for (int i = 0; i < slider.size(); i++) {
        addAndMakeVisible(slider[i]);
    }


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
    

    generatePattern.setBounds(twoBw, h/8 * 7 - twoBw, w - fourBw, h/8);
    for (int i = 0; i < slider.size(); i++) {
       slider[i]->setBounds(w/slider.size() * i - twoBw, h/8 - twoBw,  w/slider.size() - fourBw, h/8);;
    }
}
//==============================================================================
/**@Internal@*/


void SequenceGeneratorEditor::buttonClicked (Button* button){
    if (button == &generatePattern) {
        PrintPattern(GeneratePattern(GeneratePatternPreset((int)slider[0]->getValue(),
                                                           2,
                                                           (int)slider[1]->getValue())));
    }
}

