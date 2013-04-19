//
//  SequenceEditor.cpp
//  Genie
//
//  Created by Jerome on 13/10/2012.
//
//

#include "SequenceEditor.h"
#include "SequenceGenerator.h"

//==============================================================================
SequenceEditor::SequenceEditor()
:
sequenceGenerator(display),
display(8,1)

{

    addAndMakeVisible(&sequenceGenerator);
    addAndMakeVisible(&display);
}

SequenceEditor::~SequenceEditor()
{
}

//==============================================================================
/**@Internal@*/
void SequenceEditor::paint (Graphics& g)
{
    int w = getWidth();
    int h = getHeight();
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawRect(Bw, Bw, w-twoBw, h-twoBw,Bw);
    
}
/**@Internal@*/
void SequenceEditor::resized()
{
    int w = getWidth();
    int h = getHeight();
    
    sequenceGenerator.setBounds(twoBw, twoBw, w / 2 - fourBw, h /2  - fourBw);
    display.setBounds(twoBw, h/4 * 3 - twoBw, w - fourBw, h/4 - twoBw);

}

//==============================================================================