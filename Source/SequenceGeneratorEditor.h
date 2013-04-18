/*
  ==============================================================================

    SequenceGeneratorEditor.h
    Created: 24 Mar 2013 12:33:01pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SEQUENCEGENERATOREDITOR_H_86DD913__
#define __SEQUENCEGENERATOREDITOR_H_86DD913__

#include "genieHeader.h"
#include "SequenceGenerator.h"

class SequenceElement : public Component {
    bool active;
    
public:
    SequenceElement()
    :   active(false)
    {
        
    }
    
    ~SequenceElement(){
        
    }
    
    void isOn(bool isOn){
        active = isOn;
        repaint();
    }
    
    
    void paint(Graphics &g){
        int w = getWidth();
        int h = getHeight();
        
        if (active) g.fillAll (Colours::green);
        else  g.fillAll (Colours::black);
        
        g.setColour(Colours::white);
        g.drawRect(Bw, Bw, w-twoBw, h-twoBw,Bw);
    }
    
    void resized(){
        repaint();
        }
};

class MonomeDisplay : public Component{
    OwnedArray<SequenceElement> btn;
    int columns,rows;
    
    void addRow(){
        for (int i = 0; i < columns; i++) {
            btn.add(new SequenceElement);
            addAndMakeVisible(btn.getLast());
        }
        rows++;
        resized();
    }
    void addColumn(){
        for (int i = 0; i < rows; i++) {
            btn.insert(btn.size() - (i*columns + i ), new SequenceElement);
            addAndMakeVisible(btn[i*columns + i]);
        }
        columns++;
        resized();
    }
    void removeRow(){
        btn.removeRange(btn.size()-1, columns);
        rows--;
        resized();
    }
    void removeColumn(){
        for (int i = 0; i < rows; i++) {
            btn.remove(btn.size() - (i*columns + i));
        }
        columns--;
        resized();
    }
    
public:
    
    MonomeDisplay()
    : columns(0),
    rows(0)
    {
        
    }
    
    void setColumns(int numberOfColumns){
        if (numberOfColumns < 33 && numberOfColumns > 0) {
            

            if (columns < numberOfColumns) {
                for (int i = 0; i < numberOfColumns - columns; i++) {
                    addColumn();
                }
            }
            else{
                for (int i = 0; i < columns - numberOfColumns; i++) {
                    removeColumn();
                }
            }
            
        }
       
    }
    
    void setRows(int numberOfRows){
        if (numberOfRows < 33 && numberOfRows> 0) {
            if (rows < numberOfRows) {
                for (int i = 0; i < numberOfRows - rows; i++) {
                    addRow();
                }
            }
            else{
                for (int i = 0; i < rows - numberOfRows; i++) {
                    removeRow();
                }
            }
        }
    }
    

    
    void emptyGrid(){
        btn.clear();
    }
    void resetGrid(){
        for (int i = 0; i < btn.size(); i++) {
                btn[i]->isOn(false);
            }
            
    }
    

    void resized(){
        int w = getWidth();
        int h = getHeight();
        
        for (int i = 0; i < rows; i++){
            for (int ii = 0 ; ii < columns; ii++) {
                btn[i*ii]->setBounds(w/columns * ii,
                                     h/rows * i,
                                     w/columns,
                                     h/rows);
            }
          
        }
    
    }
    
    void paint(Graphics &g){
        g.fillAll(Colours::white);
    }
};



/**==============================================================================
 SequenceGeneratorEditor provides an interface for @SequenceGenerator
 
 Features;
 Inherits from @SequenceGenerator
 
 ToDo;
 Export sequence as midifile to host
 ============================================================================== */
class SequenceGeneratorEditor : public Component,
                                public ButtonListener,
                                public Slider::Listener,
                                public SequenceGenerator

{
public:
    SequenceGeneratorEditor();
    ~SequenceGeneratorEditor();
    
    //==============================================================================
    /**@Internal@*/
    void paint (Graphics& g);
    /**@Internal@*/
    void resized();
    
    //==============================================================================
    /**@Internal@*/
    void buttonClicked (Button* button);
    /**@Internal@*/
    void sliderValueChanged (Slider* slider);
    
private:
    
    TextButton generatePattern;
    
    OwnedArray<Slider> slider;

    MonomeDisplay display;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceGeneratorEditor)
    
};



#endif  // __SEQUENCEGENERATOREDITOR_H_86DD913__
