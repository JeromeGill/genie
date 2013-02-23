/*
  ==============================================================================

    SequenceGenerator.cpp
    Created: 17 Feb 2013 3:07:19pm
    Author:  Jerome

  ==============================================================================
*/

#include "SequenceGenerator.h"
SequenceGenerator::SequenceGenerator(){
    
}

SequenceGenerator::~SequenceGenerator(){
    
}

//==============================================================================
/**Generate a Pattern.
  Takes a PatternPreset struct and generates a Pattern from it.
 */
Pattern SequenceGenerator::GeneratePattern(PatternPreset P){
    
    Pattern NewPattern;
    if (P.d() || P.x()) { //If Pattern preset exists else return an empty pattern
        
    }

    return NewPattern;
}

/**Generate a Random PatternPreset
 
 Each of its member variables are randomised.
 
 */
//PatternPreset RandomPatternPreset(){
//    PatternPreset P(1,1);
//    
//    for (int i = 0; i < P.d(); i++) {
//        for (int ii = 0; ii < P.x(); ii++) {
//            
//            P.n(ii, i).m = 8; //Not random at the moment for testing.
//            P.n(ii, i).p = 3;
//            
//        }
//    }
//    return P;
//}

/**Generate a single necklace.
 */
Sequence SequenceGenerator::GenerateNecklace(int Intervals, int Pulses, bool BreakEarly)
{
    
    Pattern necklace(Intervals, Sequence(1,0));
    
    for (int i = 0; i < Intervals ; i++) {
        if (Intervals < Pulses)
            necklace[i][0] = true;
        else
            necklace[i][0] = false;
        
        std::cout<<necklace[i][0];
    }
    std::cout<<"\n";
    
    DistributePulses(Intervals, Pulses, necklace, BreakEarly);
    Sequence seq = necklace[0];
    return seq;
}

/**The recursive part of the GenerateNecklace() function
 */
int SequenceGenerator::DistributePulses(int Intervals, int Pulses, Pattern Necklace, bool BreakEarly){
  
    //Sequences are divided into blocks, postitive and remainders.
    //A remainder block is appended onto a positive block.
    //The remainder block is then poped
    //The process is repeated untill there are no remainders.
    //The positive block each remainder is placed on is cycled to ensure even distribution of remainders
    
    int end = (int)BreakEarly;
    
    if (Pulses == end)
        return Intervals;
    
    else{
        int i = 0;      //The counter for the number of positive blocks
        int r = Intervals - Pulses;  //The number of remainder blocks
        
        std::cout<<r<<"\n";
        
        for (int r = 0; r < Intervals - Pulses; r++)     //while r < the total remainder blocks
        {
            int size = (int)Necklace[Intervals - r - 1].size();  //The size of remainder cells
            
            //Push each remainder cell onto Positive block, then pop remainder cell
            for (int i2 = 0; i2 < size; i2++){
                Necklace[i].push_back(Necklace[Intervals- r -1][i2]);
                Necklace[Intervals - 1 - r].pop_back();
            }
            
            //Move to the next positive block
            i++;
            if(i == Pulses) i = 0;
        }
        
        
        for (int i = 0; i < Intervals; i++) {
            for (int p = 0; p < Necklace[i].size(); p++)
                std::cout<<Necklace[i][p];
        }
        std::cout<<"\n";
        
        return DistributePulses(Pulses, Intervals % Pulses, Necklace);
    }
}

/**Adds an additional sequence to a pattern
 */
void AddSequence(Pattern pattern, Sequence sequence){
  
    pattern.push_back(sequence);
}
/**Append Sequence two onto the end of Sequence one
 */
void SequenceGenerator::AppendSequence(Sequence one, Sequence two){
    for (int i = 0; i < two.size(); i++) {
        one.push_back(two[i]);
    }

}
//==============================================================================
    
/**Returns the number of true values at a given position of a pattern
 Returns 0 if Position is invalid
 */
int SequenceGenerator::GetPulses(Pattern pattern, int position){
    
    int pulses = 0;
        
    for (int i = 0; i < pattern.size(); i++) {
        if (pattern[i].size()>position && position >= 0){
            if(pattern[i][position]) pulses++;
        }
        
        else{
            std::cout<<"GetPulses recieved invalid position. Returning 0/n";
            pulses = 0;
            break;
        }
    }

    return pulses;
        
}
//==============================================================================
/**Outputs Pattern to the console
 */
void SequenceGenerator::PrintPattern(Pattern PatternToPrint){
    for (int i = 0; i < PatternToPrint.size(); i++) {
        for (int ii = 0; ii < PatternToPrint[i].size(); ii++) {
            std::cout<<PatternToPrint[i][ii];
        }
        std::cout<<"\n";
    }
}