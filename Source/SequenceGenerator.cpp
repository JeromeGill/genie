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
    
    Pattern p;
    
  
    if (P.d() || P.x()) { //If Pattern preset is valid
       for (int i = 0; i < P.d(); i++) { //cycle through the depth of the pattern
           
           Sequence s; //Initialise a blank sequence
            
            for (int ii = 0; ii < P.x(); ii++){//cycle through the number of necklaces at each level of the pattern.
                
                Sequence z =  GenerateNecklace(P.np(i, ii).n,
                                               P.np(i, ii).p,
                                               P.np(i, ii).b);
                
                AppendSequence(s, z); //generate each necklace and append to sequence s
            }
            
            AddSequence(p, s);//add sequence s to the pattern
        }
    }
    else{std::cout<<"Generate Pattern received invalid preset \n";}
    
    return p;
}

/**Generate a Random PatternPreset
 
 Each of its member variables are randomised.
 
 */
PatternPreset SequenceGenerator::GetRandomPatternPreset(){
    return GeneratePatternPreset();
}

/**Generate a PatternPreset
 
 
 Number of necklaces per sequence, sequences per pattern and total number of intervals per sequence is defined by the user.
 Values of 0 randomise that value.
 
 Ranges
 
 NecklacesPerSequence   = 0 - 10
 SequencesPerPattern    = 0 - 5
 IntervalsPerSequence   = 0 - 4 (equivilant to the number of bars generated assuming a 4/4 rythmn)
 
 Values outside of these ranges get rounded
 */
PatternPreset SequenceGenerator::GeneratePatternPreset(int necklacesPerSequence,
                                                  int sequencesPerPatten,
                                                  int intervalsPerSequence){
    PatternPreset P(necklacesPerSequence,sequencesPerPatten);
    

    
    //std::cout<<"Intervals "<<intervalsPerSequence<<"\n";
    
    for (int i = 0; i < P.d(); i++) { //Cycle through each sequence in a pattern
        
        int remainderIntervals = intervalsPerSequence * 8; //For each sequence determine how many intervals need distributing between each necklace
        
        for (int ii = 0; remainderIntervals>0; ii++) { //Move through each necklace in the sequence for as long as there are intervals to distribute
            
            if(ii == P.x()){ //Move back to the first necklace if reached the end of the cycle
             ii = 0;
            }
            
            int n = MINNECKLACESIZE + (rand() % (intervalsPerSequence - MINNECKLACESIZE)); //Generate a random number between the minimum number of necklaces and the total intervals in a sequence
            
            remainderIntervals -= n; //Subtract that number from the remainding intervals
            
            if  (remainderIntervals < 0) { //If the remainding intervals are less than zero add the difference back on to n
                n += remainderIntervals;
            }
           
            std::cout<<"n "<<n<<"\n";
            std::cout<<"Remainder Intervals "<<remainderIntervals<<"\n";
            
            P.np(ii, i).n += n; //Add n to the number of intervals in the necklace
            P.np(ii, i).p = rand() %  P.np(ii, i).n; //Generate a random number of pulses between 0 and the number of intervals in the necklace
           
            P.np(ii, i).b = true;
        
            std::cout<<"Pattern "<<ii<<" "<<i<<" n "<<P.np(ii, i).n<<" p "<<P.np(ii, i).p<<"\n";
        }
    }
    
    return P;
    
}

/**Generate a single necklace.
 */
Sequence SequenceGenerator::GenerateNecklace(int Intervals, int Pulses, bool BreakEarly)
{
    
    Pattern necklace(Intervals, Sequence(1,1));
    
    for (int i = 0; i < Intervals; i++) {
        if (i < Pulses)
            necklace[i][0] = true;
        else
            necklace[i][0] = false;
    }

    Sequence s = DistributePulses(Intervals, Pulses, necklace, BreakEarly);
    
    return s;
}

/**The recursive part of the GenerateNecklace() function
 
 Returns a sequence Intervals long with n pulses distributed evenly
 */
Sequence SequenceGenerator::DistributePulses(int Intervals, int Pulses, Pattern Necklace, bool BreakEarly){
  
    //Sequences are divided into blocks, postitive and remainders.
    //A remainder block is appended onto a positive block.
    //The remainder block is then poped
    //The process is repeated untill there are no remainders.
    //The positive block each remainder is placed on is cycled to ensure even distribution of remainders
    
    int end = (int)BreakEarly;
    
    if (Pulses <= end){
        
        for (int i = 1; i < Necklace.size(); i++) {
            AppendSequence(Necklace[0], Necklace[i]);
        }
        return Necklace[0];
        
    }
    
    else{
        int i = 0;      //The counter for the number of positive blocks
        
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
        
        return DistributePulses(Pulses, Intervals % Pulses, Necklace);
    }
}

/**Adds an additional sequence to a pattern
 */
void SequenceGenerator::AddSequence(Pattern& pattern, Sequence sequence){
  
    pattern.push_back(sequence);
}
/**Append Sequence two onto the end of Sequence one
 */
void SequenceGenerator::AppendSequence(Sequence& one, Sequence two){
    
//    std::cout<<"AppendSequence : ";
//    PrintSequence(one, false);
//    std::cout<<" : ";
//    PrintSequence(two);
    
    for (int i = 0; i < two.size(); i++) {
        one.push_back(two[i]);
    }

    //PrintSequence(one);

    
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
    std::cout<<"Printing Pattern "<<PatternToPrint.size()<<"\n";
    
    for (int i = 0; i < PatternToPrint.size(); i++) {
        std::cout<<"Sequence "<<i<<" : ";
        PrintSequence(PatternToPrint[i]);
    }
}

/**Outputs Sequence to the console
 */
void SequenceGenerator::PrintSequence(Sequence SequenceToPrint, bool newLine){
    
    for (int i = 0; i < SequenceToPrint.size(); i++) {
        
            std::cout<<SequenceToPrint[i];
        }
    
    if (newLine)
        std::cout<<"\n";
}