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
    refresh();
}
        

MonomeDisplay::~MonomeDisplay()
{
}


void MonomeDisplay::resized()
{
    if (rows && columns) {
    float w = getWidth();
    float h = getHeight();
    
   
        for (int i = 0; i < rows; i++){
            for (int ii = 0 ; ii < columns; ii++) {
                btn[getElement(ii, i)]->setBounds(w/columns * ii,
                                              h/rows * i,
                                              w/columns,
                                              h/rows);
            }
            
        }
  
    }

}


void MonomeDisplay::setActive(size_t column, size_t row, bool setActive, Colour colour){
    btn[getElement(columns, row)]->onColour(colour);
    btn[getElement(columns, row)]->isOn(setActive);
}

void MonomeDisplay::addRow(){

    //std::cout<<"Monome Add Row: "<<columns<<" "<<rows;
    for (int i = 0; i < columns; i++) {
        SequenceElement *a = new SequenceElement;
        btn.add(a);
        
    }
    rows++;
 
}

void MonomeDisplay::addColumn()
{
  
    std::cout<<"Monome Add Column: "<<columns<<" "<<rows;
    for (int i = 0; i < rows; i++) {
        SequenceElement *a = new SequenceElement;
        btn.insert(i*columns + columns, a);
        std::cout<<"o";
    }
    columns++;

    std::cout<<"\n";

}

void MonomeDisplay::removeRow(){
  
    
    for (int i = 1; i <= columns; i++) {
        btn.remove((btn.size() - i));
    }
    rows--;
    refresh();
}

void MonomeDisplay::removeColumn(){
   
    for (int i = 0; i < rows; i++) {
        btn.remove((getElement(i, i)));
    }
    columns--;
    refresh();
}

void MonomeDisplay::setColumns(int numberOfColumns){
    if (numberOfColumns < MONOMEMAXSIZE && numberOfColumns > 0) {
         clear();
        
        if (columns < numberOfColumns) {
            for (int i = columns; i < numberOfColumns; i++) {
                addColumn();
            }
        }
        else{
            for (int i = columns; i > numberOfColumns; i--) {
                removeColumn();
            }
        }
           refresh();
    }
    
}

void MonomeDisplay::setRows(int numberOfRows){
    if (numberOfRows < MONOMEMAXSIZE && numberOfRows> 0) {
          clear();
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
        refresh();
    }
}

void MonomeDisplay::clear(){
    for (int i = 0; i < btn.size(); i++) {
        btn[i]->setVisible(false);
    }
}

void MonomeDisplay::refresh(){
    for (int i = 0; i < btn.size(); i++) {
        addAndMakeVisible(btn[i]);
    }
    resized();
}

void MonomeDisplay::emptyGrid(){
    btn.clear();
}
void MonomeDisplay::resetGrid(){
    for (int i = 0; i < btn.size(); i++) {
        btn[i]->isOn(false);
    }
    
}

int MonomeDisplay::getElement(size_t column, size_t row){
    return row * columns + column;
}
