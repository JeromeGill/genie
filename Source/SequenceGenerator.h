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

#define MAXNECKLACESIZE 30 //The maximum available intervals in a necklace
#define MAXNECKLACES    5  //The maxmimum available necklaces in a sequence
#define MAXDEPTH        5  //The maximum sequences in a pattern


 /**==============================================================================
  SequenceGenerator generates a vector of vectors of Bools that represents a rhythmic sequence.
  Each sequence consists of two or more "necklaces". Each necklace is a cyclical sequence of pulses.
  A number of sequences are stacked on top of each other to form a pattern. 
  
  A pattern is generated from a PatternPreset structure. 
  
  Features;
    Generate a vector of bools using euclid method
    Concate a number of these vectors to form a sequence
    Generate a pattern by layering sequences
    Return the number of true values at each position of a sequence vector
    PatternPreset Struct 
  
  ToDo;
    Randomly generate a pattern preset
    Store structs used to generate sequence vector on hard disk
    Print a pattern preset
    Protection against stupid numbers in PatternPreset struct
  
 ============================================================================== */
typedef std::vector<bool> Sequence;
typedef std::vector<Sequence> Pattern;

/**PatternPreset is used to store all the constituent values that generate a complete pattern
 
 Values cannot be modified after initialisation.
 
 x - the number of necklaces in a sequence
 d - the number of sequences that form the pattern
 
 n - an individual necklace in a std::vector
 n consists of;
 m - the number of available intervals
 p - the number of pulses to be distributed over the available intervals
 breakEarly - which rotation the necklace is
 
 see @RandomPattern() for a detailed example of how to initialise one of these.
 */
struct PatternPreset {
    
    struct NecklacePreset{
        NecklacePreset(int intervals = 0, int pulses = 0, bool BreakEarly = false)
        :m(intervals), p(pulses), b(BreakEarly)
        {
            if (pulses > MAXNECKLACESIZE || pulses>intervals || intervals > MAXNECKLACESIZE || pulses < 0 || intervals < 0){ //protect against invalid values.
                pulses = intervals = 0;
                std::cout<<"Necklace received invalid initialisation.\n";
            }
        }
        
        int m; //Available intervals
        int p;  //Pulses
        bool b; //BreakEarly toggle
    };
    
    PatternPreset(int necklaces, int depth)
    :necklaces(necklaces), depth(depth)
    {
        if (necklaces < 0 || necklaces > MAXNECKLACES || depth < 0 || depth > MAXDEPTH) { //protect against invalid values.
            necklaces = depth = 0;
            std::cout<<"Pattern received invalid initialisation.\n";
        }
        
        for (int i = 0; i < necklaces * depth; i++) {
            N.push_back(NecklacePreset());
        }
    }
    
    const int x(){return necklaces;}
    const int d(){return depth;}
    
    NecklacePreset & n(size_t x, size_t d) { return N[x + d * this->x()]; }
    
private:
    
    std::vector<NecklacePreset> N; //Size = necklaces * depth (x * d).
    
    int necklaces;      //The number of necklaces to form one sequence
    int depth;          //The number of sequences to form one pattern
};


class SequenceGenerator {
    
protected:
    SequenceGenerator();
    ~SequenceGenerator();
    
    //==============================================================================
    /**Generate a Pattern from a pattern preset.
     */
    Pattern GeneratePattern(PatternPreset setting);
    
    /**Generate a PatternPreset
     
     Each of its member variables are randomised
     */
    PatternPreset GetRandomPatternPreset();
    
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
    void AddSequence(Pattern& pattern, Sequence sequence);
    /**Append Sequence two onto the end of Sequence one
     */
    void AppendSequence(Sequence &one, Sequence two);

    //==============================================================================
    /**Outputs Pattern to the console
     */
    void PrintPattern(Pattern PatternToPrint);
    /**Outputs Sequence to the console
     */
    void PrintSequence(Sequence SequenceToPrint, bool newLine = true);
    
    /**Returns the number of true values at a given position of a pattern
     Returns 0 if Position is invalid. (If 
     */
    int GetPulses(Pattern pattern, int position);

private:
    /**The recursive part of the GenerateNecklace() function
     */
    Sequence DistributePulses(int Intervals, int Pulses, Pattern Necklace, bool BreakEarly = false);
};



#endif  // __SEQUENCEGENERATOR_H_DDA483C6__
