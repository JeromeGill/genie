/*
  ==============================================================================

    SequenceGeneratorEditor.h
    Created: 24 Mar 2013 12:33:01pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SEQUENCEGENERATOREDITOR_H_86DD913__
#define __SEQUENCEGENERATOREDITOR_H_86DD913__

#include "genieHeader.h"
<<<<<<< HEAD
#include "SequenceGenerator.h"
/**==============================================================================
 SequenceGeneratorEditor provides an interface for @SequenceGenerator
=======
#include "SequenceGenerator.h"  

/**==============================================================================
 SequenceGeneratorEditor is where automatic sequence rearrangments can be generated
>>>>>>> 32630d546c700eb5a22f0b938fff1b24b0da079a
 
 Features;
 Inherits from @SequenceGenerator
 
 ToDo;
 Export sequence as midifile to host
 ============================================================================== */
class SequenceGeneratorEditor :  public Component,
                        public ButtonListener,
                        public SequenceGenerator

{
public:
    SequenceGeneratorEditor();
    ~SequenceGeneratorEditor();
    
    //==============================================================================
    /**@Internal@*/
    void paint (Graphics& g);
    /**@Internal@*/
    void resized();
    
    //==============================================================================
    /**@Internal@*/
    void buttonClicked (Button* button);
<<<<<<< HEAD

=======
>>>>>>> 32630d546c700eb5a22f0b938fff1b24b0da079a
    
private:
    
    TextButton generatePattern;
<<<<<<< HEAD
    Slider phraseValue;
    Slider sequenceLength;
=======
>>>>>>> 32630d546c700eb5a22f0b938fff1b24b0da079a
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceGeneratorEditor)
    
};



#endif  // __SEQUENCEGENERATOREDITOR_H_86DD913__
