/*
  ==============================================================================

    SubsectionEditor.h
    Created: 10 Jan 2013 8:44:34pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SUBSECTIONEDITOR_H_9D58F006__
#define __SUBSECTIONEDITOR_H_9D58F006__
#include "genieHeader.h"
#include "AudioSubsectionManager.h"
#include "SliceComponent.h"
#include "PolyAudioFilePlayer.h"
#include "genieLogo.h"

class SubsectionEditor :    public Component,
                            public AudioSubsectionManager::Listener,
                            public Slider::Listener,
                            public Button::Listener,
                            public ComboBox::Listener
{
public:
    SubsectionEditor(AudioSubsectionManager &audioSubsectionManager,
                     PolyAudioFilePlayer& polyAudioFilePlayer_);
    //,AudioThumbnailImage& sourceToBeUsed);
    ~SubsectionEditor();
    
    void setImageSource(AudioThumbnailImage& image);
  
    //==============================================================================
    /**@Internal@*/
    void subsectionCreated(int SubsectionIndex);
    /**@Internal@*/
    void subsectionDeleted(int SubsectionIndex);
    //**@Internal@*/
    void subsectionChanged(int SubsectionIndex);
    //**@Internal@*/
    void subsectionsCleared();
    
    //==============================================================================
    /**@Internal@*/
    void paint(Graphics &g);
    /**@Internal@*/
    void resized();
    /** @Internal@ */
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    /** @Internal@ */
    void sliderValueChanged (Slider* slider);
    /** @Internal@ */
    void buttonClicked (Button* button);

    
private:
    int activeSubsection;
    
    Image subsectionWaveform;
    
    SliceComponent* SubsectionViewer;
    
    OwnedArray<ToggleButton> HitClassButtons;
    ComboBox hitTypeSelector;
    Slider subsectionSelector;
    
    TextButton Preview;
    Label      SliceSelLabel;
    
    AudioThumbnailImage* imageSource;
    AudioSubsectionManager &subsection;
    
    
    PolyAudioFilePlayer& polyAudioFilePlayer;
    
    const Image genieImage;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SubsectionEditor)
};

#endif  // __SUBSECTIONEDITOR_H_9D58F006__
