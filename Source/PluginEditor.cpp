/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "genieLogo.h"


//==============================================================================

GenieAudioProcessorEditor::GenieAudioProcessorEditor (GenieAudioProcessor* ownerFilter,
                                                      drow::AudioFilePlayer& audioFilePlayer_,
                                                      AudioSubsectionManager &audioSubsectionManager_,
                                                      PolyAudioFilePlayer &polyAudioFilePlayer_)
:   AudioProcessorEditor (ownerFilter), 
    subsectionEditor(audioSubsectionManager_,
                     polyAudioFilePlayer_),
    audioEditor(audioSubsectionManager_, audioFilePlayer_, subsectionEditor)


{
    addAndMakeVisible(&sequenceEditor);
    addAndMakeVisible(&audioEditor);
    addAndMakeVisible(&subsectionEditor);
    
    genieTitle.setText("Genie \n - An Automatic Breakbeat Rearranging Sampler -", false);
    genieTitle.getFont();
    genieTitle.setJustificationType(Justification::centred);
    genieTitle.setColour(0x1000281, Colours::white);
    addAndMakeVisible(&genieTitle);

    
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
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawRect(Bw, getHeight()/4 * 3 + twoBw, getWidth()/2-twoBw, getHeight()/4-twoBw - Bw ,Bw);

   
}
//==============================================================================
void GenieAudioProcessorEditor::resized()
{

    int w = getWidth();
    int h = getHeight();
    
    audioEditor.setBounds   (0,  0   ,w   ,h/4);
    sequenceEditor.setBounds(w/2, h/4 ,w/2 ,h/4 * 3);
    subsectionEditor.setBounds(0,  h/4 ,w/2 ,h/4 * 2);
    genieTitle.setBounds(0, h/4 * 3, w/2, h/4);
}