/*
 ==============================================================================
 
 SubsectionEditor.cpp
 Created: 10 Jan 2013 8:44:34pm
 Author:  Jerome
 
 ==============================================================================
 */

#include "SubsectionEditor.h"

SubsectionEditor::SubsectionEditor(AudioSubsectionManager &audioSubsectionManager,
                                   AudioThumbnailImage& sourceToBeUsed)
:
imageSource(sourceToBeUsed),
subsection(audioSubsectionManager)
{
    hitTypes.add("Kick");
    hitTypes.add("Snare");
    hitTypes.add("Hat");
    hitTypes.add("Ride");
    hitTypes.add("Crash");
    
    subsection.addListener(this);
    subsectionSelector.addListener(this);
    std::cout<<"Adding Button ";
    for(int i =0; i < hitTypes.size(); i++){
        HitClassButtons.add(new ToggleButton(hitTypes[i]));
        addAndMakeVisible(HitClassButtons[i]);
        HitClassButtons[i]->addListener(this);
        std::cout<<i<<" ";
    }
    std::cout<<"\n";
    addAndMakeVisible(&subsectionSelector);
}

SubsectionEditor::~SubsectionEditor(){
    
    for(int i; i < hitTypes.size(); i++)
        HitClassButtons[i]->removeListener(this);
    
    subsection.removeListener(this);
}

//==============================================================================
/**@Internal@*/
void SubsectionEditor::subsectionCreated(int SubsectionIndex){
    
    String name = "Slice";
    name += subsection.size();
    subsectionSelector.addItem(name, subsection.size());
}
/**@Internal@*/
void SubsectionEditor::subsectionDeleted(int SubsectionIndex){
    subsectionSelector.clear();
    for (int i = 1; i < subsection.size(); i++) {
        String name = "Slice";
        
        name += i;
        if (subsection.getName(i) != "Null") {
            name.append(subsection.getName(i), 6);
        }
        std::cout<<"ComboBox adding"<<i<<"\n";
        subsectionSelector.addItem(name, i);
    }
}
//**@Internal@*/
void SubsectionEditor::subsectionChanged(int SubsectionIndex){
}
//**@Internal@*/
void SubsectionEditor::buttonClicked (Button* button)
{
    subsection.nameSubsection(activeSubsection, button->getName());
    
}
//**@Internal@*/
void SubsectionEditor::comboBoxChanged (ComboBox* comboBox)
{
    activeSubsection = comboBox->getSelectedId();
    repaint();
}


//==============================================================================
/**@Internal@*/
void SubsectionEditor::paint(Graphics &g){
    g.fillAll(Colours::white);
}
/**@Internal@*/
void SubsectionEditor::resized(){
    int w = getWidth();
    int h = getHeight();
    
    for(int i = 0; i < hitTypes.size(); i++){
        HitClassButtons[i]->setBounds((w / hitTypes.size()) * i,
                                      h / 8,
                                      w / hitTypes.size(),
                                      h/8);
    }
    subsectionSelector.setBounds(0, 0, w, h/8);
}