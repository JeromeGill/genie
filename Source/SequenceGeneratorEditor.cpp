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
    generatePattern.addListener(this);
}

SequenceGeneratorEditor::~SequenceGeneratorEditor()
{
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
    
    generatePattern.setBounds(twoBw, twoBw, w - fourBw, h - fourBw);
    
}

void SequenceGeneratorEditor::buttonClicked (Button* button){
    if (button == &generatePattern) {
        PrintPattern(GeneratePattern(GetRandomPatternPreset()));
    }
}
//==============================================================================