///*
//  ==============================================================================
//
//    subsectionEditor.h
//    Created: 31 Dec 2012 4:55:46pm
//    Author:  Jerome
//
//  ==============================================================================
//*/
//
//#ifndef __subsectionEDITOR_H_F6E0FF7F__
//#define __subsectionEDITOR_H_F6E0FF7F__
//
//#include "genieHeader.h"
//#include "AudioSubsectionManager.h"
//
///**==============================================================================
// subsectionViewer is an object to provide a GUI for an AudioSubsectionManager
// 
//    Functions
// Set subsection hit type
// 
//    Todo
// Display subsectionWaveform
// Allow for Trimming subsection endpoints
// ==============================================================================*/
//class subsectionViewer : public Component,
//                    public Button::Listener
//{
//public:
//    subsectionViewer(AudioSubsectionManager &subsectionManager_)
//    : AudioSubsectionManager(&subsectionManager_),
//    subsectionWaveform("subsectionImage")
//    
//    {
//        
//        
//        
//        HitClassButtons.add(new ToggleButton("Kick"));
//        HitClassButtons.add(new ToggleButton("Snare"));
//        HitClassButtons.add(new ToggleButton("Hat"));
//        HitClassButtons.add(new ToggleButton("Ride"));
//        HitClassButtons.add(new ToggleButton("Crash"));
//        
//        //addAndMakeVisible(&subsectionWaveform);
//        for(int i = 0; i < subsectionData::HitType::TotalHitTypes; )
//        {  addAndMakeVisible(HitClassButtons[i]);
//            HitClassButtons[i]->addListener(this);
//            i++;
//        }
//        
//      
//    }
//    ~subsectionViewer(){
//        for(int i = 0; i < subsectionData::HitType::TotalHitTypes; )
//        {  
//            HitClassButtons[i]->removeListener(this);
//            i++;
//        }
//    }
//
//    /** @Internal@ */
//    void paint(Graphics &g){
//      
//    }
//    
//    /** @Internal@ */
//    void resized(){
//
//        int w = getWidth();
//        int h = getHeight();
//        int b = w / HitClassButtons.size();
//        
//        subsectionWaveform.setBounds(0, h / 5, w / 5 * 4 , h/5 * 2);
////        for (int i; i<HitClassButtons.size();) {
////            HitClassButtons[i]->setBounds(b * i, 0, b, h/5);
////            i++;
////            }
//        }
//        
//
//    /** Set the subsection to be represented*/
//    void setsubsection(subsectionData* subsection_)
//    {
//        RectanglePlacement placement(RectanglePlacement::centred);
//        
//        subsectionWaveform.setImage(subsection_->getsubsectionImage(), placement);
//        //subsectionWaveform.repaint();
//    }
//    
//    /** @Internal@ */
//    void buttonClicked (Button* button)
//    {
//        int typeIndex;
//        
//        if (button->getName() == "kick") {
//            typeIndex = 0;
//            button->setToggleState (true, false);
//        }
//        if (button->getName() == "snare") {
//            typeIndex = 1;
//            button->setToggleState (true, false);
//        }
//        if (button->getName() == "hat") {
//            typeIndex = 2;
//            button->setToggleState (true, false);
//        }
//        if (button->getName() == "ride") {
//            typeIndex = 3;
//            button->setToggleState (true, false);
//        }
//        if (button->getName() == "crash") {
//            typeIndex = 4;
//            button->setToggleState (true, false);
//        }
//        
//        for (int i; i<HitClassButtons.size();) {
//            if (i != subsection->getHitType()) {
//                HitClassButtons[i]->setToggleState(false, false);
//                i++;
//            }
//        }
//    }
//private:
//    
//    OwnedArray<ToggleButton> HitClassButtons;
//    AudioSubsectionManager *subsections;
//    Label label;
//    Image subsectionWaveform;
//    StringArray &hitTypes;
//};
//
///**
// subsectionEditor manages a subsectionviewer
// 
// these really need to only be one class
// */
//class subsectionEditor : public Component,
//                    public subsectionManager::Listener,
//                    public ComboBox::Listener
//{
//    
//public:
//    subsectionEditor(subsectionManager &subsectionManager_);
//    ~subsectionEditor();
//    
//    /** @Internal@ */
//    void resized();
//    /** @Internal@ */
//    void paint(Graphics &g);
//    
//    /** @Internal@ */
//    void subsectionCreated();
//    /** @Internal@ */
//    void subsectionDeleted();
//    /** @Internal@ */
//    void subsectionInitialised();
//    /** @Internal@ */
//    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
//private:
//    
//    int totalsubsections;
//    ComboBox subsectionSelector;
//    subsectionManager* subsectionManager;
//    subsectionViewer viewer;
//};
//
//
//
//#endif  // __subsectionEDITOR_H_F6E0FF7F__
