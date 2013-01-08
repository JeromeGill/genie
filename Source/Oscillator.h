/*
  ==============================================================================

    Oscillator.h
    Created: 5 Nov 2012 11:58:16pm
    Author:  Jerome

  ==============================================================================
*/

/**
 Oscillator is a class that generates simple waveforms
 Sine, Triangle, Square
 */

#ifndef __OSCILLATOR_H_DF18FA34__
#define __OSCILLATOR_H_DF18FA34__

#include <math.h>
#include <iostream>

class Oscillator
{
public:
    Oscillator();

    ~Oscillator();
    
    void initialiseOscillator(double samplerate, float frequency);
    
    void setFrequency(double frequency);
    
    float getSine();
    
    void phaseInc();
    
    //double getSquare();
    
    //double getTriangle();
    
private:

    
    float sampleRate;
    float frequency, phaseIncrement, phasePosition, twoPi;
};


#endif  // __OSCILLATOR_H_DF18FA34__
