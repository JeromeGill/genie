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
#include "genieHeader.h"

#define MAXNECKLACESIZE 36 //The maximum available intervals in a necklace
#define MAXNECKLACES    5  //The maxmimum available necklaces in a sequence
#define MAXDEPTH        6  //The maximum sequences in a pattern

#define MINNECKLACESIZE 3 //The minimum intervals in a necklace



typedef std::vector<bool> Sequence;
typedef std::vector<Sequence> Pattern;

/**
 \brief PatternPreset is used to store all constituent NecklacePresets that generate a complete pattern
 
 Values cannot be modified after initialisation.
 
 x - the number of necklaces in a sequence
 d - the number of sequences that form the pattern
 
 n - an individual necklace in a std::vector
 n consists of;
 m - the number of available intervals
 p - the number of pulses to be distributed over the available intervals
 breakEarly - which rotation the necklace is
 
 see RandomPattern() for a detailed example of how to initialise one of these.
 */
struct PatternPreset {
    /**
     \brief NecklacePreset contains the number of pulses and intervals involved in a single euclidean necklace
     */
    struct NecklacePreset{
        NecklacePreset(int intervals = 0, int pulses = 0, bool BreakEarly = false)
        :n(intervals), p(pulses), b(BreakEarly)
        {
            if (pulses > MAXNECKLACESIZE || pulses>intervals || intervals > MAXNECKLACESIZE){ //protect against invalid values.
                pulses = intervals = 0;
                std::cout<<"Necklace received invalid initialisation.\n";
            }
        }
        
        int n; //Available intervals
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
            NP.push_back(NecklacePreset());
        }
    }
    
    const int x(){return necklaces;}
    const int d(){return depth;}
    
    NecklacePreset & np(size_t x, size_t d) { return NP[x + d * this->x()]; }
    
private:
    
    std::vector<NecklacePreset> NP; //Size = necklaces * depth (x * d).
    
    int necklaces;      //The number of necklaces to form one sequence
    int depth;          //The number of sequences to form one pattern
};


//==============================================================================
/**SequenceGenerator
 \brief SequenceGenerator is where the rythmic generation aspect of genie occurs
 
 SequenceGenerator generates a vector of vectors of Bools that represents a rhythmic sequence.
 Each sequence consists of two or more "necklaces". Each necklace is a cyclical sequence of pulses.
 A number of sequences are stacked on top of each other to form a pattern.
 
 A pattern is generated from a PatternPreset structure.
 
 Features\n;
 Generate a vector of bools using euclid method\n
 Concate a number of these vectors to form a sequence\n
 Generate a pattern by layering sequences\n
 Return the number of true values at each position of a sequence vector\n
 PatternPreset Struct\n
 Randomly generate a pattern preset\n
 Export a pattern as a midifile\n
 Print a pattern preset\n
 
 ToDo;
 
 Store structs used to generate sequence vector on hard disk\n
 Protection against stupid numbers in PatternPreset struct\n
 *///==============================================================================
class SequenceGenerator {
    
public:
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
    
    /**Generate a PatternPreset
     
     Number of necklaces per sequence, sequences per pattern and total number of intervals per sequence is defined by the user.
     Values of 0 randomise that value.
     
     Ranges
     
     NecklacesPerSequence   = 0 - 5
     SequencesPerPattern    = 0 - 5
     IntervalsPerSequence   = 0 - 4 (equivilant to the number of bars generated assuming a 4/4 rythmn)
     
     Values outside of these ranges get rounded
     */
    PatternPreset GeneratePatternPreset(int necklacesPerSequence = 3, int sequencesPerPatten = 3, int intervalsPerSequence = 2);
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

    //==============================================================================
    /** Listener
     */
    class Listener
    {
    public:
        virtual ~Listener(){};
        /** Called when a pattern is generated
         */
        virtual void patternGenerated(Pattern& p){};
    };
    /** add a listener
     */
    void addListener(Listener* listener);
    /** Remove a listener
     */
    void removeListener(Listener* listener);
    //==============================================================================
    /** Write a generated pattern to midifile at a specified BPM
     */
    void writePatternToMidiFile(Pattern pattern, int BPM, bool isCumulativePattern);
    /** Write a most recently generated pattern to midifile at a specified BPM
     */
    void writeLastPatternToMidiFile(int BPM, bool isCumulativePattern);
  
    
    /** Add a MidiNote to a midi sequence at ticks.
     
     A noteoff is automatically placed at ticks+duration
     
     use isCumulativePattern to determine slice slection or standard rhythm generation
     */
    void addNoteToSequence(MidiMessageSequence& Sequence,
                           double ticks,
                           double duration,
                           int noteNumber,
                           int channel = 10,
                           float velocity = 1);
    
    Pattern *pattern; /*!< The most recently generated pattern */

private:
    /**The recursive part of the GenerateNecklace() function
     */
    Sequence DistributePulses(int Intervals, int Pulses, Pattern Necklace, bool BreakEarly = false);
    
    
    int noteNumberFromPatternPosition(Pattern p, int i);
    ListenerList<Listener> listenerList;
    
};



#endif  // __SEQUENCEGENERATOR_H_DDA483C6__
