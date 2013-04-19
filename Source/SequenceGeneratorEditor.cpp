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
: display(8,1)

{
    
    generatePattern.addListener(this);
    generatePattern.setButtonText("Generate Pattern");
    addAndMakeVisible(&generatePattern);


    labels.add(new Label);//("SeqGenLabel", "Sequence Controls"));
    labels.add(new Label);//("SeqComLabel", "Complexity"));
    labels.add(new Label);//("SeqLenLabel", "Length"));
    labels.add(new Label);//("SeqDepLabel", "Depth"));
    
    labels[0]->setText("Sequence Controls", false);
    labels[1]->setText("Complexity", false);
    labels[2]->setText("Length", false);
    labels[3]->setText("Depth", false);
    
    labels[0]->setColour(0x1000280, Colours::white);
    labels[0]->setJustificationType(Justification::centred);
    
    for (int i = 0; i < labels.size(); i++) {
        //labels[i]->setColour(0x1000281, Colours::white);
        addAndMakeVisible(labels[i]);
    }
    

    
    slider.add(new Slider("SequenceComplexity"));
    slider.add(new Slider("SequenceLength"));
    slider.add(new Slider("SequenceDepth"));

    slider[0]->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    slider[0]->addListener(this);
    slider[0]->setRange(1, 5, 1);

    slider[1]->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    slider[1]->addListener(this);
    slider[1]->setRange(1, 4, 1);

    slider[2]->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    slider[2]->addListener(this);
    slider[2]->setRange(1, 4, 1);

    
    for (int i = 0; i < slider.size(); i++)
        addAndMakeVisible(slider[i]);
    
    addAndMakeVisible(&display);

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
    g.fillRect(fourBw, h/8 - twoBw, w/2 - fourBw - twoBw, h/8 * slider.size() - twoBw);
      
}
/**@Internal@*/
void SequenceGeneratorEditor::resized()
{
    int w = getWidth();
    int h = getHeight();
    

    generatePattern.setBounds(twoBw, h/8 * 7 - twoBw, w - fourBw, h/8);
    
    for (int i = 0; i < slider.size(); i++) {
       slider[i]->setBounds(twoBw, h/8 * (i + 1),  w/4 - fourBw, h/8);;
    }
    labels[0]->setBounds(fourBw, fourBw, w/2 - fourBw, h/8 - (2*fourBw));
    
    for (int i = 1; i < labels.size(); i++) {
        labels[i]->setBounds (w/4, h/8 * i,  w/4 - fourBw, h/8);
    }
    
    display.setBounds(twoBw, h/8 * (slider.size() + 1), w - fourBw, h/4);
}
//==============================================================================
/**@Internal@*/


void SequenceGeneratorEditor::buttonClicked (Button* button){
    if (button == &generatePattern) {
        Pattern p = GeneratePattern(GeneratePatternPreset((int)slider[0]->getValue(),
                                                          (int)slider[2]->getValue(),
                                                          (int)slider[1]->getValue()));
        PrintPattern(p);
        displayPattern(p);
        
    }
}

/**@Internal@*/
void SequenceGeneratorEditor::sliderValueChanged (Slider* slider){
    if(slider->getName() == "SequenceLength"){
        display.setColumns((int) slider->getValue() * 8);
    }
    if(slider->getName() == "SequenceDepth"){
         display.setRows((int) slider->getValue());
    }
}


void SequenceGeneratorEditor::displayPattern(Pattern pattern){
    for (int i = 0; i < pattern.size(); i++) {
        for (int ii = 0; ii < pattern[i].size(); ii++){
            display.setActive(ii, i, pattern[i][ii]);
        }
    }
}
