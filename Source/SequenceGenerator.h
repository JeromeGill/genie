/*
  ==============================================================================

    SequenceGenerator.h
    Created: 17 Feb 2013 3:07:19pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SEQUENCEGENERATOR_H_DDA483C6__
#define __SEQUENCEGENERATOR_H_DDA483C6__

#include <iostream>
#include <vector>


 /**==============================================================================
  SequenceGenerator generates a vector of vectors of Bools that represents a rhythmic sequence.
  Each sequence consists of two or more "necklaces". Each necklace is a cyclical sequence of pulses.
  A number of sequences are stacked on top of each other to form a pattern. 
  
  Features;

  ToDo;
    Generate a pattern by layering sequences
  
    Generate a vector of bools using euclid method
    Concate a number of these vectors to form a sequence
    Store sequences in a vector
    Return the number of true values at each position of the sequence vector
  
    Store numbers used to generate sequence vector in a 'preset' file. 
  
 ============================================================================== */

typedef std::vector<bool> Sequence;
typedef std::vector<Sequence> Pattern;

class SequenceGenerator {
    
protected:
    SequenceGenerator();
    ~SequenceGenerator();
    
    //==============================================================================
    
    /**Generate a single necklace.
     
     Distributes a number of pulses as evenly as possible over a number of intervals.
     Utilises a Euclidean model of recursion. 
     Returns the result as a vector of bools.
     
     E.G
     
     GenerateNecklace(8, 3) = 1 0 0 1 0 1 0 0
     
     Different revolutions of the necklace are possible by enabling the BreakEarly option.
     
     E.G
     
     GenerateNecklace(8, 3, true) = 1 0 0 1 0 0 1 0
     
     */
    Sequence GenerateNecklace(int Intervals, int Pulses, bool BreakEarly = false);
    /**Adds an additional sequence to a pattern
     */
    void AddSequence(Pattern pattern, Sequence sequence);
    /**Append Sequence two onto the end of Sequence one
     */
    void AppendSequence(Sequence one, Sequence two);

    //==============================================================================
    /**Outputs Pattern to the console
     */
    void PrintPattern(Pattern PatternToPrint);
    
    /**Returns the number of true values at a given position of a pattern
     */
    int GetPulses(Pattern pattern, int position);//Would be nice to do this with overloading [] if it can be done only when accessed out side of this class?

private:
    /**The recursive part of the GenerateNecklace() function
     */
    int DistributePulses(int Intervals, int Pulses, Pattern Necklace, bool BreakEarly = false);
};



#endif  // __SEQUENCEGENERATOR_H_DDA483C6__
