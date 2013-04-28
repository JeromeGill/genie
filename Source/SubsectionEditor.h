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
#include "PolyAudioFilePlayer.h"

//==============================================================================
/**SubsectionEditor
 \brief SubsectionEditor displays the most recently modified SubSection in a SubSectionManager.
 
 It requires a [drow::AudioThumbnailImage] with the waveform loaded to be passed into it.
 This means it needs do no rendering of it's own. 
 This will be changed in future versions to allow a high def image of a subesction to be rendered.
 
 Each subsection may be previewed with PolyAudioFilePlayer
 
 [drow::AudioThumbnailImage: http://drowaudio.co.uk/docs/class_audio_thumbnail_image.html (drow:AudioThumbnailImage)
 
 Todo; Allow classification of subsections to place them on the GM drum map
*///==============================================================================

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
    
    void setImageSource(drow::AudioThumbnailImage& image);
  
    //==============================================================================
    /** @internal */
    void subsectionCreated(int SubsectionIndex);
    /** @internal */
    void subsectionDeleted(int SubsectionIndex);
    //** @internal */
    void subsectionChanged(int SubsectionIndex);
    //** @internal */
    void subsectionsCleared();
    
    //==============================================================================
    /** @internal */
    void paint(Graphics &g);
    /** @internal */
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
    
    ComboBox hitTypeSelector;
    Slider subsectionSelector;
    
    TextButton Preview;
    Label      SliceSelLabel;
    
    drow::AudioThumbnailImage* imageSource;
    AudioSubsectionManager &subsection;
    
    
    PolyAudioFilePlayer& polyAudioFilePlayer;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SubsectionEditor)
};

#endif  // __SUBSECTIONEDITOR_H_9D58F006__
