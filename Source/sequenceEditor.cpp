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
: genieImage(
             ImageCache::getFromMemory (genieLogo::genielogo2_png,
                                      genieLogo::genielogo2_pngSize))
{
 


}

SequenceEditor::~SequenceEditor()
{
}

//==============================================================================
/**@Internal@*/
void SequenceEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawRect(Bw, Bw, getWidth()-twoBw, getHeight()-twoBw,Bw);
    g.drawImageAt(genieImage.rescaled (getWidth() / 2 - twoBw, getHeight() - fourBw),getWidth()/ 4 - Bw,  twoBw);
    
}
/**@Internal@*/
void SequenceEditor::resized()
{
    int w = getWidth();
    int h = getHeight();

}

//==============================================================================