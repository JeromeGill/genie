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

class SubsectionEditor :    public Component,
                            public AudioSubsectionManager::Listener,
                            //public Button::Listener,
                            public ComboBox::Listener
{
public:
    SubsectionEditor(AudioSubsectionManager &audioSubsectionManager);
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

    
private:
    int activeSubsection;
    
    Image subsectionWaveform;
    
    SliceComponent* SubsectionViewer;
    
    OwnedArray<ToggleButton> HitClassButtons;
    ComboBox subsectionSelector, hitTypeSelector;
    
    AudioThumbnailImage* imageSource;
    AudioSubsectionManager &subsection;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SubsectionEditor)
};

#endif  // __SUBSECTIONEDITOR_H_9D58F006__
