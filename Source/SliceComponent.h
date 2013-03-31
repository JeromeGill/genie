/*
  ==============================================================================

    SliceComponent.h
    Created: 24 Mar 2013 12:34:37pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SLICECOMPONENT_H_9012DECB__
#define __SLICECOMPONENT_H_9012DECB__

#include "genieHeader.h"
#include "SubSection.h"

/** SliceComponent renders an image of Subsection and provides a standard Juce Component of that image
 */

class SliceComponent : public Component,
                       public SubSection,
public Label::Listener
{
    friend class AudioSubsectionManager;
    friend class SubsectionComparator;
public:
    SliceComponent();
    ~SliceComponent();
    
    void resized();
    void paint(Graphics &g);
    
    Image subsectionWaveform;
    
    void labelTextChanged (Label* labelThatHasChanged);
    
private:
    Label Name;
};



#endif  // __SLICECOMPONENT_H_9012DECB__
