/*
  ==============================================================================

    MonomeDisplay.h
    Created: 19 Apr 2013 10:01:43am
    Author:  Jerome

  ==============================================================================
*/

#ifndef __MONOMEDISPLAY_H_83AF7FB__
#define __MONOMEDISPLAY_H_83AF7FB__

#include "../JuceLibraryCode/JuceHeader.h"
#include "genieHeader.h"
//==============================================================================
/*
*/

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
        
        g.fillAll (Colours::black);
        if (active){
            g.setColour(Colours::green);
            g.fillRect(twoBw, twoBw, w-fourBw, h-fourBw);
         }
      
        
        g.setColour(Colours::white);
        g.drawRect(Bw, Bw, w-twoBw, h-twoBw,Bw);
    }
    
    void resized(){
        repaint();
    }
};

class MonomeDisplay    : public Component
{
public:
    MonomeDisplay(int columns, int rows);
    ~MonomeDisplay();

    void setActive(size_t column, size_t row, bool isActive);
    void addRow();
    void addColumn();
    
    void removeRow();
    void removeColumn();
    
    void setColumns(int numberOfColumns);
    void setRows(int numberOfRows);
    
    void emptyGrid();
    void resetGrid();
    
    void paint (Graphics&);
    void resized();
    
private:
    OwnedArray<SequenceElement> btn;
    int columns,rows;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonomeDisplay)
};


#endif  // __MONOMEDISPLAY_H_83AF7FB__
