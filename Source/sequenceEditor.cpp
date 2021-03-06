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
: sequenceDisplay(4,1),
totalDisplay(4,1),
genieImage(ImageCache::getFromMemory (genieLogo::genielogo2_png,
                                      genieLogo::genielogo2_pngSize))
{

    sequenceGenerator.addListener(this);
    addAndMakeVisible(&sequenceGenerator);
    addAndMakeVisible(&sequenceDisplay);
    addAndMakeVisible(&totalDisplay);
    
    savePattern1.addListener(this);
    savePattern1.setButtonText("Save Polyphonic Sequence");
    addAndMakeVisible(&savePattern1);
    
    savePattern2.addListener(this);
    savePattern2.setButtonText("Save Slice Selection Sequence");
    addAndMakeVisible(&savePattern2);
    
     sequenceDisplay.setAlpha(0.7);
     totalDisplay.setAlpha(0.7);
    
    sequenceGenerator.addListener(this);
    sequenceGenerator.addSliderListeners(this);
}

SequenceEditor::~SequenceEditor()
{
    sequenceGenerator.removeSliderListeners(this);
}

//==============================================================================
/** @internal */
void SequenceEditor::paint (Graphics& g)
{
    int w = getWidth();
    int h = getHeight();
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawRect(Bw, Bw, w-twoBw, h-twoBw,Bw);
    g.drawRect(twoBw + Bw, h/2, w - fourBw-twoBw, h/4,Bw);//SequenceDisplay outline
    g.drawRect(twoBw + Bw, h/8 * 7, w - fourBw-twoBw, h/8 - twoBw, Bw); //totalDisplay outline
    
    g.drawImageAt(genieImage.rescaled (w / 2 - twoBw, h - fourBw), w/2,  twoBw);
    
}
/** @internal */
void SequenceEditor::resized()
{
    int w = getWidth();
    int h = getHeight();
    
    sequenceGenerator.setBounds(twoBw, twoBw, w / 2 - fourBw, h /2  - fourBw);
    sequenceDisplay.setBounds(fourBw, h/2 + Bw, w - fourBw-fourBw, h/4 - twoBw);
    
    savePattern1.setBounds(twoBw, h/4*3, w/2 - twoBw, h/8);
    savePattern2.setBounds(w/2, h/4*3, w/2 - twoBw, h/8);
    totalDisplay.setBounds(fourBw, h/8 * 7+Bw, w - fourBw-fourBw, h/8 - fourBw);

}

//==============================================================================
void SequenceEditor::displayPattern(Pattern pattern, MonomeDisplay& display){
   
    for (int i = 0; i < pattern.size(); i++) {
        for (int ii = 0; ii < pattern[i].size(); ii++){
            display.setActive(ii, i, pattern[i][ii]);
        }
    }
    
}

void SequenceEditor::displayPatternTotals(Pattern pattern, MonomeDisplay& display){
    for (int i = 0; i < pattern[0].size(); i++) {
        
        Colour colour;
        int pulses = sequenceGenerator.GetPulses(pattern, i);
        
        if (pulses == 0) {
            colour = Colours::black;
        }

        else if (pulses == pattern.size()) {
            colour = Colours::red;
        }
        else if (pulses == pattern.size()-1) {
            colour = Colours::yellow;
        }
        else if (pulses == pattern.size()-2) {
            colour = Colours::green;
        }
        else if (pulses == pattern.size()-3) {
            colour = Colours::blue;
        }
        else if (pulses == pattern.size()-4) {
            colour = Colours::brown;
        }
        
        display.setActive(i, 0, true, colour);
    }
}

void SequenceEditor::sliderValueChanged(Slider* slider){
    if(slider->getName() == "SequenceLength"){
        sequenceDisplay.setColumns((int) slider->getValue() * 4);
        totalDisplay.setColumns((int) slider->getValue() * 4 );
    }
    if(slider->getName() == "SequenceDepth"){
        sequenceDisplay.setRows((int) slider->getValue());
    }

}

void SequenceEditor::buttonClicked (Button* button){
    if (button == &savePattern1){
        sequenceGenerator.writeLastPatternToMidiFile(120, false);
    }
    else if (button == &savePattern2) {

        sequenceGenerator.writeLastPatternToMidiFile(120, true);

    }
}


void SequenceEditor::patternGenerated(Pattern& p){
    displayPattern(p, sequenceDisplay);
    displayPatternTotals(p, totalDisplay);
}