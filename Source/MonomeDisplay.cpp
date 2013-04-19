/*
  ==============================================================================

    MonomeDisplay.cpp
    Created: 19 Apr 2013 10:01:43am
    Author:  Jerome

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MonomeDisplay.h"

//==============================================================================
MonomeDisplay::MonomeDisplay(int initialColumns, int initialRows):
columns(0),
rows(0)
{
    for (int i = 0; i < initialColumns; i++) {
        addColumn();
    }
    for (int i = 0; i < initialRows; i++) {
        addRow();
    }
}
        

MonomeDisplay::~MonomeDisplay()
{
}

void MonomeDisplay::paint (Graphics& g)
{


    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("MonomeDisplay", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void MonomeDisplay::resized()
{
    if (rows && columns) {
    int w = getWidth();
    int h = getHeight();
    
   
        for (int i = 0; i < rows; i++){
            for (int ii = 0 ; ii < columns; ii++) {
                btn[i*columns+ ii]->setBounds(w/columns * ii,
                                              h/rows * i,
                                              w/columns,
                                              h/    rows);
            }
            
        }
        repaint();
    }
}


void MonomeDisplay::setActive(size_t column, size_t row, bool setActive){
    btn[row * columns + column]->isOn(setActive);
    repaint();
}

void MonomeDisplay::addRow(){
    
    //std::cout<<"Monome Add Row: "<<columns<<" "<<rows;
    for (int i = 0; i < columns; i++) {
        
        btn.add(new SequenceElement);
        addAndMakeVisible(btn.getLast());
        
    }
    rows++;
    resized();
}

void MonomeDisplay::addColumn()
{
    std::cout<<"Monome Add Column: "<<columns<<" "<<rows;
    for (int i = 0; i < rows; i++) {
        SequenceElement *a = new SequenceElement;
        addAndMakeVisible(a);
        btn.insert(i*columns + columns, a);
        std::cout<<"o";
    }
    columns++;
    resized();
    std::cout<<"\n";
}

void MonomeDisplay::removeRow(){
    btn.removeRange(btn.size()-1, columns);
    rows--;
    resized();
}

void MonomeDisplay::removeColumn(){
    for (int i = 0; i < rows; i++) {
        btn.remove((i*columns + i));
    }
    columns--;
    resized();
}

void MonomeDisplay::setColumns(int numberOfColumns){
    if (numberOfColumns < 33 && numberOfColumns > 0) {
        
        
        if (columns < numberOfColumns) {
            for (int i = columns; i <= numberOfColumns; i++) {
                addColumn();
            }
        }
        else{
            for (int i = columns; i > numberOfColumns; i--) {
                removeColumn();
            }
        }
        
    }
    
}

void MonomeDisplay::setRows(int numberOfRows){
    if (numberOfRows < 33 && numberOfRows> 0) {
        if (rows < numberOfRows) {
            for (int i = 0; i <= numberOfRows - rows; i++) {
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



void MonomeDisplay::emptyGrid(){
    btn.clear();
}
void MonomeDisplay::resetGrid(){
    for (int i = 0; i < btn.size(); i++) {
        btn[i]->isOn(false);
    }
    
}
