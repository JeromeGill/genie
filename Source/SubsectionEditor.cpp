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
    hitTypes.add("Unnamed");
    hitTypes.add("Kick");
    hitTypes.add("Snare");
    hitTypes.add("Hat");
    hitTypes.add("Ride");
    hitTypes.add("Crash");
    
    subsection.addListener(this);
    subsectionSelector.addListener(this);
   
    hitType.addListener(this);
    for(int i =0; i < hitTypes.size(); i++){
        hitType.addItem(hitTypes[i], i+1);
    }
    
    
    
    std::cout<<"\n";
    addAndMakeVisible(&subsectionSelector);
    addAndMakeVisible(&hitType);
    activeSubsection = 0;
}

SubsectionEditor::~SubsectionEditor(){
    
    for(int i; i < hitTypes.size(); i++)
        HitClassButtons[i]->removeListener(this);
    
    subsection.removeListener(this);
}

void SubsectionEditor::setImageSource(AudioThumbnailImage &image){
    imageSource = &image;
}
//==============================================================================
/**@Internal@*/
void SubsectionEditor::subsectionCreated(int SubsectionIndex){
    
    String name = "Slice";
    name += subsection.size();
    //std::cout<<name<<" Start::Duration "<<subsection.getStart(SubsectionIndex)<<" : "<<subsection.getLength(SubsectionIndex)<<"\n";
    subsectionSelector.addItem(name, subsection.size());
}
/**@Internal@*/
void SubsectionEditor::subsectionDeleted(int SubsectionIndex){
    
    subsectionSelector.clear();
    
    for (int i = 0; i < subsection.size(); i++) {
        String name = "Slice";
        
        name += i;
        if (subsection.getName(i) != "Null") {
            name.append(subsection.getName(i), 6);
        }
        std::cout<<"ComboBox adding"<<i<<"\n";
        subsectionSelector.addItem(name, i+1);
    }
}
//**@Internal@*/
void SubsectionEditor::subsectionChanged(int SubsectionIndex){
     std::cout<<"Changed"<<SubsectionIndex<<"\n";
    repaint();
}
//**@Internal@*/
void SubsectionEditor::subsectionsCleared(){
    activeSubsection = 0;
    repaint();
    
}
//**@Internal@*/
void SubsectionEditor::buttonClicked (Button* button)
{
    subsection.nameSubsection(activeSubsection, button->getName());
    
}
//**@Internal@*/
void SubsectionEditor::comboBoxChanged (ComboBox* comboBox)
{
    if (comboBox == &subsectionSelector) {
        activeSubsection = comboBox->getSelectedId();
        repaint();
    }
    
}


//==============================================================================
/**@Internal@*/
void SubsectionEditor::paint(Graphics &g){
    
    int index = activeSubsection -1;
    
    //g.setOpacity(0.4);
    g.fillAll(Colours::black);
    
    if (activeSubsection){
        
        double start    = subsection.SampleToTime(subsection.getStart(index));
        double duration = subsection.SampleToTime(subsection.getLength(index));

       if (imageSource->getImage().isValid() && duration)
            subsectionWaveform = imageSource->getImageAtTime (start, duration);

        g.drawImageAt(subsectionWaveform.rescaled(getWidth() - fourBw,
                                                  getHeight() / 8 * 6 - fourBw),
                      twoBw,
                      getHeight() / 8 * 2 - fourBw);

    }
    
    g.setColour(Colours::white);
    g.drawRect(Bw, Bw, getWidth()-twoBw, getHeight()-twoBw,Bw);
    
}
/**@Internal@*/
void SubsectionEditor::resized(){
    int w = getWidth();
    int h = getHeight();
    
//    for(int i = 0; i < hitTypes.size(); i++){
//        HitClassButtons[i]->setBounds(((w/ hitTypes.size()) * i) + fourBw,
//                                      h / 8 - twoBw,
//                                      w / hitTypes.size() - fourBw,
//                                      h/ 8 - fourBw);
//    }
    
    subsectionSelector.setBounds(twoBw, twoBw, w - fourBw, h/8 - twoBw);
    hitType.setBounds(twoBw,h/8 ,w / 2 - fourBw , h/8 - twoBw);
}