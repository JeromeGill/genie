//
//  ==============================================================================
//
//    MonomeDisplay.h
//    Created: 19 Apr 2013 10:01:43am
//    Author:  Jerome
//
//  ==============================================================================
//

#ifndef __MONOMEDISPLAY_H_83AF7FB__
#define __MONOMEDISPLAY_H_83AF7FB__

#define MONOMEMAXSIZE 129
#define BORDERPERCENTAGE 1
#include "../JuceLibraryCode/JuceHeader.h"


class SequenceElement : public Component {
    bool active;
    Colour activeColour;
public:
    SequenceElement()
    :   active(false),
    activeColour(Colours::green)
    
    {
        
    }
    
    ~SequenceElement(){
        
    }
    
    void isOn(bool isOn){
        active = isOn;
        repaint();
    }
    
    void onColour(Colour colour){
        activeColour = colour;
        repaint();
    }
    
    void paint(Graphics &g){
        float w = (float)getWidth();
        float h = (float)getHeight();
        
        float bw = 100 / BORDERPERCENTAGE;
        //  g.fillAll (Colours::black);
        
//        g.setColour(Colours::blueviolet);
//        g.drawRect(w, h, w, h, sqrt(w*h) *bw);
        
      
        
        if (active){
            g.setColour(activeColour);
        }
        else{
            g.setColour(Colours::black);
            g.setOpacity(0);
        }
            g.fillRect(w/bw, h/bw, w-w/bw *2, h-h/bw *2);
        
      
    }
    
    
    void resized(){
        repaint();
    }
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequenceElement)
};

//==============================================================================
/**MonomeDisplay
 \brief MonomeDisplay is a grid of SequenceElement arranged like a [Monome]
 
 Monome display is a class for displaying a grid of coloured rectangles or squares allowing dynamic modification of rows or columns at run time.
 [Monome]: http://monome.org/ (Monome)
 */
//==============================================================================
class MonomeDisplay    : public Component
{
public:
    MonomeDisplay(int columns, int rows);
    ~MonomeDisplay();

    /**Set a an element active and define it's colour.
     True = on
     False = off
     */
    void setActive(size_t column, size_t row, bool isActive, Colour colour = Colours::green);
    
    /** Set number of columns
     */
    void setColumns(int numberOfColumns);
    /** Set number of rows
     */
    void setRows(int numberOfRows);
    
    /**Delete all elements
     */
    void emptyGrid();
    /**Set all elements inactive
     */
    void resetGrid();

    
private:
    int getElement(size_t column, size_t row);
    void addRow();
    void addColumn();
    void removeRow();
    void removeColumn();
    
    void clear();
    void refresh();
    
    void resized();

    OwnedArray<SequenceElement> btn;
    int columns,rows;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MonomeDisplay)
};


#endif  // __MONOMEDISPLAY_H_83AF7FB__
