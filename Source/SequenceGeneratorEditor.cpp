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

    labels.add(new Label);//("SeqGenLabel", "Sequence Controls"));
    labels.add(new Label);//("SeqComLabel", "Complexity"));
    labels.add(new Label);//("SeqLenLabel", "Length"));
    labels.add(new Label);//("SeqDepLabel", "Depth"));
    
    labels[0]->setText("Sequence Controls", false);
    labels[1]->setText("Complexity", false);
    labels[2]->setText("Length", false);
    labels[3]->setText("Depth", false);
    
    
    
    for (int i = 0; i < labels.size(); i++) {
        labels[i]->setColour(0x1000280, Colours::black);
        labels[i]->setColour(0x1000281, Colours::white);
        addAndMakeVisible(labels[i]);
    }
    
    labels[0]->setColour(0x1000280, Colours::white);
    labels[0]->setColour(0x1000281, Colours::black);
    labels[0]->setJustificationType(Justification::centred);

    
    slider.add(new Slider("SequenceComplexity"));
    slider.add(new Slider("SequenceLength"));
    slider.add(new Slider("SequenceDepth"));

 

    for (int i = 0; i < slider.size(); i++) {
        slider[i]->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
        slider[i]->addListener(this);
        slider[i]->setColour(0x1001311, Colours::white);              
        addAndMakeVisible(slider[i]);
    }
    slider[0]->setRange(1, 5, 1);
    slider[1]->setRange(1, 16, 1);
    slider[2]->setRange(1, 6, 1);
    

        
    
}

SequenceGeneratorEditor::~SequenceGeneratorEditor()
{
    generatePattern.removeListener(this);

}

//==============================================================================
/** @internal */
void SequenceGeneratorEditor::paint (Graphics& g)
{
    int w = getWidth();
    int h = getHeight();
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawRect(Bw, Bw, w-twoBw, h-twoBw,Bw);
//    g.setColour(Colours::green);
//    g.setOpacity(0.7);
//    g.fillRect(fourBw, h/8 - twoBw, w - (2*fourBw), h/8 *7 - twoBw);
    
}
/** @internal */
void SequenceGeneratorEditor::resized()
{
    int w = getWidth();
    int h = getHeight();
    

    generatePattern.setBounds(fourBw, h/5 * 4 - twoBw, w - (2*fourBw), h/5 - twoBw);
    
    for (int i = 0; i < slider.size(); i++) {
       slider[i]->setBounds(twoBw, h/5 * (i + 1),  w/2 - fourBw, h/5);
    }
    labels[0]->setBounds(w / 8 - twoBw, fourBw , w/ 8 * 6 + fourBw , h/5 - (2*fourBw));
    
    for (int i = 1; i < labels.size(); i++) {
        labels[i]->setBounds (w/2, h/5 * (i) + twoBw,  w/2 - fourBw, h/5 - fourBw);
    }
    
}
//==============================================================================
/** @internal */


void SequenceGeneratorEditor::buttonClicked (Button* button){
    if (button == &generatePattern) {
     
        PrintPattern(GeneratePattern(GeneratePatternPreset((int)slider[0]->getValue(),
                                                              (int)slider[2]->getValue(),
                                                              (int)slider[1]->getValue())));

    }

}

/** @internal */
void SequenceGeneratorEditor::sliderValueChanged (Slider* slider){
//    if(slider->getName() == "SequenceLength"){
//        display.setColumns((int) slider->getValue() * 8);
//    }
//    if(slider->getName() == "SequenceDepth"){
//         display.setRows((int) slider->getValue());
//    }
}

void SequenceGeneratorEditor::addSliderListeners (Slider::Listener *listener){
    for (int i = 0; i < slider.size(); i++) {
        slider[i]->addListener(listener);
    }
}
void SequenceGeneratorEditor::removeSliderListeners (Slider::Listener *listener){
    for (int i = 0; i < slider.size(); i++) {
        slider[i]->removeListener(listener);
    }
}

