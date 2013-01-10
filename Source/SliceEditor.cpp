/*
  ==============================================================================

    SliceEditor.cpp
    Created: 31 Dec 2012 4:55:46pm
    Author:  Jerome

  ==============================================================================
*/

#include "SliceEditor.h"

//SliceEditor::SliceEditor(SliceManager &sliceManager_)
//: sliceManager(&sliceManager_),
//    viewer(sliceManager_)
//{
//    sliceManager->addListener(this);
//    SliceSelector.addListener(this);
//
//    
//    addAndMakeVisible(&SliceSelector);
//    
//    addAndMakeVisible(&viewer);
//}
//
//SliceEditor::~SliceEditor(){
//    sliceManager->removeListener(this);
//    SliceSelector.removeListener(this);
//}

//void SliceEditor::paint(Graphics &g){
//    g.setColour(Colours::wheat);
//    g.fillAll();
//}

//void SliceEditor::resized(){
//    int w = getWidth();
//    int h = getHeight();
//    SliceSelector.setBounds(0, h/10 * 9 , w , h/10);
//    viewer.setBounds(0, 0, w, h/10 * 9);
//    
//}
//
//void SliceEditor::sliceCreated(){
//    
//    String name = "Slice";
//    totalSlices++;
//    name += totalSlices;
//    SliceSelector.addItem(name, totalSlices);
//   
//    std::cout<<"populating menu \n";
//    
//    }
//
//void SliceEditor::sliceDeleted(){
//    totalSlices--;
//    for (int i = 0; i < totalSlices; i++) {
//        SliceSelector.addItem("slice", i );
//    }
//}
//
//void SliceEditor::sliceInitialised(){
//    totalSlices = 1;
//    
//    SliceSelector.clear();
//    String name = "Slice";
//    name += totalSlices;
//    
//    SliceSelector.addItem(name, totalSlices);
//}
//void SliceEditor::comboBoxChanged (ComboBox* comboBox)
//{
//    viewer.setSlice(sliceManager->getSlice(comboBox->getSelectedId() - 1));
//}