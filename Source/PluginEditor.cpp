/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================

GenieAudioProcessorEditor::GenieAudioProcessorEditor (GenieAudioProcessor* ownerFilter,
                                                      AudioFilePlayer& audioFilePlayer_,
                                                      SliceManager& sliceManager_)
:   AudioProcessorEditor (ownerFilter), 
    audioEditor(sliceManager_, audioFilePlayer_),
    sliceEditor(sliceManager_)
{
   
  
    
    
    
    addAndMakeVisible(&sequenceEditor);
    addAndMakeVisible(&audioEditor);
    addAndMakeVisible(&sliceEditor);
    
    // This is where our plugin's editor size is set.
    // Happens after creating the audio and sequence editors to prevent them being accessed by resized() before they are created
    setSize (Width, Height);
}

GenieAudioProcessorEditor::~GenieAudioProcessorEditor()
{
    //delete audioEditor;
}

//==============================================================================
void GenieAudioProcessorEditor::paint (Graphics& g)
{   
    g.fillAll (Colours::red);
}
//==============================================================================
void GenieAudioProcessorEditor::resized()
{

    int w = getWidth();
    int h = getHeight();
    
    audioEditor.setBounds   (0,  0   ,w   ,h/4);
    sequenceEditor.setBounds(w/2,h/2 ,w/2 ,h/2);
    sliceEditor.setBounds   (0,  h/2 ,w/2 ,h/2);
}