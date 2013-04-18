/*
 ==============================================================================
 
 SubsectionEditor.cpp
 Created: 10 Jan 2013 8:44:34pm
 Author:  Jerome
 
 ==============================================================================
 */

#include "SubsectionEditor.h"

SubsectionEditor::SubsectionEditor(AudioSubsectionManager &audioSubsectionManager,
                                   PolyAudioFilePlayer& polyAudioFilePlayer_)
                                  // ,AudioThumbnailImage& sourceToBeUsed)
:
//imageSource(&sourceToBeUsed),
subsection(audioSubsectionManager),
polyAudioFilePlayer(polyAudioFilePlayer_),
genieImage(ImageCache::getFromMemory (genieLogo::genielogo2_png,
                                        genieLogo::genielogo2_pngSize))
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
    
    repaint();
}
//**@Internal@*/
void SubsectionEditor::subsectionChanged(int SubsectionIndex){

    activeSubsection = SubsectionIndex;
    subsectionSelector.setValue(SubsectionIndex + 1);
    repaint();

}
//**@Internal@*/
void SubsectionEditor::subsectionsCleared(){

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
        polyAudioFilePlayer.playSubSection(subsection[activeSubsection].StartSample, subsection[activeSubsection].LengthInSamples, 1);
    }
}

//==============================================================================
/**@Internal@*/
void SubsectionEditor::paint(Graphics &g){
    
    int w = getWidth();
    int h = getHeight();
    g.fillAll(Colours::black);
    
    g.setColour(Colours::white);
    g.drawRect(Bw, Bw, w-twoBw, h-twoBw,Bw);
    g.drawImageAt(genieImage.rescaled (w / 3 - twoBw, h - fourBw), twoBw,  twoBw);

    
    //If there is an active subsection, draw it, else draw the genie logo
    if (activeSubsection >= 0){
        
        double start    = subsection.SampleToTime(subsection.getStart(activeSubsection));
        double duration = subsection.SampleToTime(subsection.getLength(activeSubsection));

        
        if (imageSource->getImage().isValid() && duration)
            subsectionWaveform = imageSource->getImageAtTime (start, duration);
        
        
        if (subsectionWaveform.isValid()) {
            g.setOpacity(0.9);
            g.drawImageAt(subsectionWaveform.rescaled(w - fourBw,
                                                      h - fourBw),
                          twoBw,
                          twoBw);
      
        }
    }

}
/**@Internal@*/
void SubsectionEditor::resized(){
    int w = getWidth();
    int h = getHeight();

   
    Preview.setBounds(w/4* 3, h/8, w/4 - twoBw, h/8 - twoBw);
    subsectionSelector.setBounds(w/5 * 2, twoBw, w/5 * 3 - twoBw, h/8 - twoBw);
    hitTypeSelector.setBounds(w/2 ,h/8 ,w / 4 - fourBw , h/8 - twoBw);
}