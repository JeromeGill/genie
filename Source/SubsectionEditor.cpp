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
    
    std::cout<<"\n";
    addAndMakeVisible(&subsectionSelector);
    addAndMakeVisible(&hitTypeSelector);
    activeSubsection = 0;
}

SubsectionEditor::~SubsectionEditor(){
    
    
    subsection.removeListener(this);
}

void SubsectionEditor::setImageSource(AudioThumbnailImage &image){
    imageSource = &image;
}
//==============================================================================
/**@Internal@*/
void SubsectionEditor::subsectionCreated(int SubsectionIndex){
    
    String name = "slice";
    subsectionSelector.addItem(name, subsection.size());
    
   
    
}
/**@Internal@*/
void SubsectionEditor::subsectionDeleted(int SubsectionIndex){
    
    subsectionSelector.clear();
    
    for (int i = 0; i < subsection.size(); i++) {
        String name = subsection.getName(i);
        std::cout<<"ComboBox adding"<<i<<"\n";
        subsectionSelector.addItem(name, i+1);
    }
}
//**@Internal@*/
void SubsectionEditor::subsectionChanged(int SubsectionIndex){
<<<<<<< HEAD
   //  std::cout<<"Changed"<<SubsectionIndex<<"\n";
    repaint();
=======
    
    double start    = subsection.SampleToTime(subsection.getStart(SubsectionIndex));
    double duration = subsection.SampleToTime(subsection.getLength(SubsectionIndex));
    
    if (imageSource->getImage().isValid() && duration){
        subsection[SubsectionIndex]->subsectionWaveform = imageSource->getImageAtTime (start, duration);
        subsection[SubsectionIndex]->repaint();
        
    }
>>>>>>> 32630d546c700eb5a22f0b938fff1b24b0da079a
}
//**@Internal@*/
void SubsectionEditor::subsectionsCleared(){
    activeSubsection = 0;
    repaint();
    
}

//**@Internal@*/
void SubsectionEditor::comboBoxChanged (ComboBox* comboBox)
{
    if (comboBox == &subsectionSelector) {
        activeSubsection = comboBox->getSelectedId() - 1;
<<<<<<< HEAD
        hitTypeSelector.setSelectedItemIndex(subsection.getSubsectionType(activeSubsection));
        std::cout<<"Selected "<<subsection[activeSubsection].name<<" : "<<subsection.getTypeAsString(activeSubsection)<<"\n";
        repaint();
=======
        hitTypeSelector.setSelectedId(subsection.getSubsectionType(activeSubsection) - 1);
        
        std::cout<<"Selected "<<subsection.getName(activeSubsection)
        <<" : "<<subsection.getTypeAsString(activeSubsection)<<"\n";
        
        SubsectionViewer = subsection[activeSubsection];
        addAndMakeVisible(SubsectionViewer);
        
        SubsectionViewer->setBounds(twoBw,
                                    twoBw + (getWidth()/8 *2),
                                    getWidth() - fourBw,
                                    getHeight()/8 * 6 - twoBw);
    }
    
    
    if (comboBox == &hitTypeSelector) {
        subsection.setSubsectionType(activeSubsection, hitTypeSelector.getSelectedItemIndex());
>>>>>>> 32630d546c700eb5a22f0b938fff1b24b0da079a
    }
    if (comboBox == &hitTypeSelector) {
        subsection.setSubsectionType(activeSubsection, hitTypeSelector.getSelectedItemIndex());
    }
    
}


//==============================================================================
/**@Internal@*/
void SubsectionEditor::paint(Graphics &g){
    
    
    g.fillAll(Colours::black);
<<<<<<< HEAD
    
    if (activeSubsection >= 0){
        
        double start    = subsection.SampleToTime(subsection.getStart(activeSubsection));
        double duration = subsection.SampleToTime(subsection.getLength(activeSubsection));

       if (imageSource->getImage().isValid() && duration)
            subsectionWaveform = imageSource->getImageAtTime (start, duration);

=======
    g.setColour(Colours::white);
    g.drawRect(Bw, Bw, getWidth()-twoBw, getHeight()-twoBw,Bw);
    if (subsectionWaveform.isValid()) {
>>>>>>> 32630d546c700eb5a22f0b938fff1b24b0da079a
        g.drawImageAt(subsectionWaveform.rescaled(getWidth() - fourBw,
                                                  getHeight() - fourBw),
                      twoBw,
                      twoBw);
    }
    resized();
    
}
/**@Internal@*/
void SubsectionEditor::resized(){
    int w = getWidth();
    int h = getHeight();

   
    subsectionSelector.setBounds(twoBw, twoBw, w - fourBw, h/8 - twoBw);
    hitTypeSelector.setBounds(twoBw,h/8 ,w / 2 - fourBw , h/8 - twoBw);
}