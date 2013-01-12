//
//  SequenceEditor.cpp
//  Genie
//
//  Created by Jerome on 13/10/2012.
//
//

#include "SequenceEditor.h"

//==============================================================================
SequenceEditor::SequenceEditor()
{
 
    hitTypes.add("Grooves");
    hitTypes.add("Fills");
    
    
    addAndMakeVisible(&functionOptions);

    for (int i = 0; i<hitTypes.size(); i++)
        functionOptions.addItem(hitTypes[i], i+1);

}

SequenceEditor::~SequenceEditor()
{
}

//==============================================================================
void SequenceEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    g.setColour(Colours::black);
    g.drawRect(0, 0, getWidth(), getHeight(), twoBw);
    
}
//==============================================================================
void SequenceEditor::resized()
{
    int w = getWidth();
    int h = getHeight();
    
       functionOptions.setBounds(twoBw,  twoBw,  w - fourBw , h/10 - Bw);

}