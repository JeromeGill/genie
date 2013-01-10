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
class SubsectionEditor :    public Component,
public AudioSubsectionManager::Listener,
public Button::Listener,
public ComboBox::Listener
{
public:
    SubsectionEditor(AudioSubsectionManager &audioSubsectionManager,
                     AudioThumbnailImage& sourceToBeUsed);
    ~SubsectionEditor();
    
  
    //==============================================================================
    /**@Internal@*/
    void subsectionCreated(int SubsectionIndex);
    /**@Internal@*/
    void subsectionDeleted(int SubsectionIndex);
    //**@Internal@*/
    void subsectionChanged(int SubsectionIndex);
    
    //==============================================================================
    /**@Internal@*/
    void paint(Graphics &g);
    /**@Internal@*/
    void resized();
    /**@Internal@*/
    void buttonClicked (Button* button);
    /** @Internal@ */
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);

private:
    int activeSubsection;
    
    
    
    OwnedArray<ToggleButton> HitClassButtons;
    Image subsectionWaveform;
    
    ComboBox subsectionSelector;
    
    AudioThumbnailImage& imageSource;
    AudioSubsectionManager &subsection;
    StringArray hitTypes;
};

#endif  // __SUBSECTIONEDITOR_H_9D58F006__
