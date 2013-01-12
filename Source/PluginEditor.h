/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINEDITOR_H_8ED19174__
#define __PLUGINEDITOR_H_8ED19174__

#include "genieHeader.h"
#include "PluginProcessor.h"
#include "audioEditor.h"
#include "sequenceEditor.h"
#include "SubsectionEditor.h"


/**==============================================================================
 
 GenieAudioProcessorEditor is the visual parent component of Genie.
 
 
 It comprises of;
    AudioEditor
    SequenceEditor
    SliceEditor

 
==============================================================================*/
class GenieAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    GenieAudioProcessorEditor (GenieAudioProcessor* ownerFilter,
                               AudioFilePlayer& audioFilePlayer_,
                               AudioSubsectionManager &audioSubsectionManager_);
    ~GenieAudioProcessorEditor();

    //==============================================================================
    // Component
    void paint (Graphics& g);
    void resized();
    
private:

    SubsectionEditor subsectionEditor;
    AudioEditor audioEditor;
    SequenceEditor sequenceEditor;
    
    
    //==============================================================================
    // Member Objects
    
    //Display
    
    Label genieTitle;
 
    AudioThumbnailImage*  audioThumbnailImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenieAudioProcessorEditor)
};


#endif  // __PLUGINEDITOR_H_8ED19174__
