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
    for (int i = 0; i<TotalFunctions; i++)
        functionOptions.add(new ComboBox);
       
    functionOptions[Edits]->setText("Edits");
    functionOptions[Edits]->addItem("Edit Option 1", 1);
    functionOptions[Edits]->addItem("Edit Option 2", 2);
    functionOptions[Edits]->addItem("Edit Option 3", 3);
    
    functionOptions[Rolls]->setText("Rolls");
    functionOptions[Rolls]->addItem("Roll Option 1", 1);
    functionOptions[Rolls]->addItem("Roll Option 2", 2);
    functionOptions[Rolls]->addItem("Roll Option 3", 3);

    for (int i = 0; i<TotalFunctions; i++)
        addAndMakeVisible(functionOptions[i]);

}

SequenceEditor::~SequenceEditor()
{
}

//==============================================================================
void SequenceEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}
//==============================================================================
void SequenceEditor::resized()
{
    int w = getWidth();
    int h = getHeight();
    
   for (int i = 0; i<TotalFunctions; i++) {
       functionOptions[i]->setBounds(0, i * h/TotalFunctions / 2, 3 * w/4 , h/TotalFunctions / 2);
   }
}