/*
  ==============================================================================

    Oscillator.cpp
    Created: 5 Nov 2012 11:58:16pm
    Author:  Jerome

  ==============================================================================
*/

#include "Oscillator.h"


Oscillator::Oscillator()
{
    twoPi = 2 * M_PI;
    phasePosition = 0;
    
}

Oscillator::~Oscillator()
{
    
}

void Oscillator::initialiseOscillator(double samplerate_, float frequency_)
{
    frequency = frequency_;
    sampleRate = samplerate_;
    phaseIncrement = (twoPi * frequency) / sampleRate;
    std::cout <<"(Frequency :" << frequency << "* twoPI) / " << sampleRate << " sample rate =" << phaseIncrement<<"\n";
}

void Oscillator::setFrequency(double frequency_)
{
    frequency = frequency_;
}

float Oscillator::getSine()
{
    float oscillation = sin(phasePosition);
    phaseInc();
    return oscillation;
}

void Oscillator::phaseInc()
{
    phasePosition += phaseIncrement;    //Incriment the phase position
	
	if (phasePosition > twoPi)          //Return phase to 0 once it goes out of bounds
        phasePosition -= twoPi;

}