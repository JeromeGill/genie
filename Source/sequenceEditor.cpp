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
: genieImage(ImageCache::getFromMemory (genieLogo::genielogo2_png,
                                        genieLogo::genielogo2_pngSize))
{

    addAndMakeVisible(&sequenceGenerator);

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
    g.drawImageAt(genieImage.rescaled (w / 2 - twoBw, h - fourBw), w/ 4 - Bw,  twoBw);
    
}
/**@Internal@*/
void SequenceEditor::resized()
{
    int w = getWidth();
    int h = getHeight();
    
    sequenceGenerator.setBounds(twoBw, h/5 * 4, w - fourBw, h/5 - twoBw);

}

//==============================================================================