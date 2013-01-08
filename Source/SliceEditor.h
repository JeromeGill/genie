/*
  ==============================================================================

    SliceEditor.h
    Created: 31 Dec 2012 4:55:46pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SLICEEDITOR_H_F6E0FF7F__
#define __SLICEEDITOR_H_F6E0FF7F__

#include "genieHeader.h"
#include "SliceManager.h"

/**==============================================================================
 SliceViewer is an object to provide a GUI for a SliceData
 
    Functions
 Set slice hit type
 
    Todo
 Display sliceWaveform
 Allow for Trimming slice endpoints
 ==============================================================================*/
class SliceViewer : public Component,
                    public Button::Listener
{
public:
    SliceViewer(SliceManager &sliceManager_)
    : sliceManager(&sliceManager_),
    sliceWaveform("sliceImage")
    
    {
        HitClassButtons.add(new ToggleButton("Kick"));
        HitClassButtons.add(new ToggleButton("Snare"));
        HitClassButtons.add(new ToggleButton("Hat"));
        HitClassButtons.add(new ToggleButton("Ride"));
        HitClassButtons.add(new ToggleButton("Crash"));
        
        //addAndMakeVisible(&sliceWaveform);
        for(int i = 0; i < SliceData::HitType::TotalHitTypes; )
        {  addAndMakeVisible(HitClassButtons[i]);
            HitClassButtons[i]->addListener(this);
            i++;
        }
        
      
    }
    ~SliceViewer(){
        for(int i = 0; i < SliceData::HitType::TotalHitTypes; )
        {  
            HitClassButtons[i]->removeListener(this);
            i++;
        }
    }

    /** @Internal@ */
    void paint(Graphics &g){
      
    }
    
    /** @Internal@ */
    void resized(){

        int w = getWidth();
        int h = getHeight();
        int b = w / HitClassButtons.size();
        
        sliceWaveform.setBounds(0, h / 5, w / 5 * 4 , h/5 * 2);
//        for (int i; i<HitClassButtons.size();) {
//            HitClassButtons[i]->setBounds(b * i, 0, b, h/5);
//            i++;
//            }
        }
        

    /** Set the slice to be represented*/
    void setSlice(SliceData* slice_)
    {
        RectanglePlacement placement(RectanglePlacement::centred);
        
        sliceWaveform.setImage(slice_->getSliceImage(), placement);
        //sliceWaveform.repaint();
    }
    
    /** @Internal@ */
    void buttonClicked (Button* button)
    {
        int typeIndex;
        
        if (button->getName() == "kick") {
            typeIndex = 0;
            button->setToggleState (true, false);
        }
        if (button->getName() == "snare") {
            typeIndex = 1;
            button->setToggleState (true, false);
        }
        if (button->getName() == "hat") {
            typeIndex = 2;
            button->setToggleState (true, false);
        }
        if (button->getName() == "ride") {
            typeIndex = 3;
            button->setToggleState (true, false);
        }
        if (button->getName() == "crash") {
            typeIndex = 4;
            button->setToggleState (true, false);
        }
        
        for (int i; i<HitClassButtons.size();) {
            if (i != slice->getHitType()) {
                HitClassButtons[i]->setToggleState(false, false);
                i++;
            }
        }
    }
private:
    SliceData* slice;
    OwnedArray<ToggleButton> HitClassButtons;
    SliceManager *sliceManager;
    Label label;
    ImageComponent sliceWaveform;
};

/**
 SliceEditor manages a sliceviewer
 
 these really need to only be one class
 */
class SliceEditor : public Component,
                    public SliceManager::Listener,
                    public ComboBox::Listener
{
    
public:
    SliceEditor(SliceManager &sliceManager_);
    ~SliceEditor();
    
    /** @Internal@ */
    void resized();
    /** @Internal@ */
    void paint(Graphics &g);
    
    /** @Internal@ */
    void sliceCreated();
    /** @Internal@ */
    void sliceDeleted();
    /** @Internal@ */
    void sliceInitialised();
    /** @Internal@ */
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
private:
    
    int totalSlices;
    ComboBox SliceSelector;
    SliceManager* sliceManager;
    SliceViewer viewer;
};



#endif  // __SLICEEDITOR_H_F6E0FF7F__
