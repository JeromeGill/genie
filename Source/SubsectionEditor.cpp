/*
 ==============================================================================
 
 SubsectionEditor.cpp
 Created: 10 Jan 2013 8:44:34pm
 Author:  Jerome
 
 ==============================================================================
 */

#include "SubsectionEditor.h"

SubsectionEditor::SubsectionEditor(AudioSubsectionManager &audioSubsectionManager)
                                  // ,AudioThumbnailImage& sourceToBeUsed)
:
//imageSource(&sourceToBeUsed),
subsection(audioSubsectionManager)
{

    hitTypeSelector.addItemList(subsection.HitTypeStringArray, 1);
    
    subsection.addListener(this);
    subsectionSelector.addListener(this);
    hitTypeSelector.addListener(this);
    Preview.addListener(this);
    Preview.setButtonText("Preview Slice");
    
    addChildComponent(&Preview);
    
    subsectionSelector.setRange (0,0,1);
    addChildComponent(&subsectionSelector);
    addChildComponent(&hitTypeSelector);
    activeSubsection = 0;
}

SubsectionEditor::~SubsectionEditor(){
    
    hitTypeSelector.removeListener(this);
    subsection.removeListener(this);
}

void SubsectionEditor::setImageSource(AudioThumbnailImage &image){
    imageSource = &image;
}
//==============================================================================
/**@Internal@*/
void SubsectionEditor::subsectionCreated(int SubsectionIndex){
    
    subsectionSelector.setVisible(true);
    hitTypeSelector.setVisible(true);
    Preview.setVisible(true);
    subsectionSelector.setRange(1, subsection.size(), 1);
    
   
    
}
/**@Internal@*/
void SubsectionEditor::subsectionDeleted(int SubsectionIndex){
    
    if (subsection.size()) {
        subsectionSelector.setValue(1);
        subsectionSelector.setRange(1, subsection.size(), 1);
    }
    else
    {
        subsectionSelector.setVisible(false);
        hitTypeSelector.setVisible(false);
        Preview.setVisible(false);
    }
}
//**@Internal@*/
void SubsectionEditor::subsectionChanged(int SubsectionIndex){

   //  std::cout<<"Changed"<<SubsectionIndex<<"\n";
    repaint();

}
//**@Internal@*/
void SubsectionEditor::subsectionsCleared(){
    activeSubsection = 0;
    repaint();
    
}

//**@Internal@*/
void SubsectionEditor::comboBoxChanged (ComboBox* comboBox)
{
  
    if (comboBox == &hitTypeSelector) {
        subsection.setSubsectionType(activeSubsection, hitTypeSelector.getSelectedItemIndex());
    }
}
/** @Internal@ */
void SubsectionEditor::sliderValueChanged (Slider* slider){
    if (slider == &subsectionSelector) {
        activeSubsection = (int)slider->getValue() - 1;
        hitTypeSelector.setSelectedItemIndex(subsection.getSubsectionType(activeSubsection));
        std::cout<<"Selected "<<subsection[activeSubsection].name<<" : "<<subsection.getTypeAsString(activeSubsection)<<"\n";
        repaint();
        
    }
}
/** @Internal@ */
void SubsectionEditor::buttonClicked(Button *button){
    if (button == &Preview) {
        
    }
}

//==============================================================================
/**@Internal@*/
void SubsectionEditor::paint(Graphics &g){
    
    
    g.fillAll(Colours::black);
    
    if (activeSubsection >= 0){
        
        double start    = subsection.SampleToTime(subsection.getStart(activeSubsection));
        double duration = subsection.SampleToTime(subsection.getLength(activeSubsection));
        
        if (imageSource->getImage().isValid() && duration)
            subsectionWaveform = imageSource->getImageAtTime (start, duration);
        
        g.setColour(Colours::white);
        g.drawRect(Bw, Bw, getWidth()-twoBw, getHeight()-twoBw,Bw);
        if (subsectionWaveform.isValid()) {
            g.drawImageAt(subsectionWaveform.rescaled(getWidth() - fourBw,
                                                      getHeight() - fourBw),
                          twoBw,
                          twoBw);
        }
    }
}
/**@Internal@*/
void SubsectionEditor::resized(){
    int w = getWidth();
    int h = getHeight();

   
    Preview.setBounds(w/2, h/8, w/2 - twoBw, h/8 - twoBw);
    subsectionSelector.setBounds(twoBw, twoBw, w - fourBw, h/8 - twoBw);
    hitTypeSelector.setBounds(twoBw,h/8 ,w / 2 - fourBw , h/8 - twoBw);
}