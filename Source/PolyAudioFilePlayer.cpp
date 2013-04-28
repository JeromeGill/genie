/*
  ==============================================================================

    PolyAudioFilePlayer.cpp
    Created: 11 Dec 2012 10:25:31am
    Author:  Jerome

  ==============================================================================
*/

#include "PolyAudioFilePlayer.h"

PolyAudioFilePlayer::PolyAudioFilePlayer()
:thread("voices")

{

    Voices.ensureStorageAllocated(POLYPHONY);
    
    //Initialise Voices
     for (int i = 0; i < POLYPHONY;) {
         Voices.add(new PolyPlayerVoice(thread));
         mixer.addInputSource(&Voices.getLast()->audioTransportSource, false);
         i++;
     }
   
}

PolyAudioFilePlayer::~PolyAudioFilePlayer()
{
   
    mixer.removeAllInputs();
    
}
//==============================================================================
/**Set the AudioFormatReader to crop from*/
void PolyAudioFilePlayer::setAudioFormatReader(AudioFormatReader *reader){
    masterReader = reader;
}
//==============================================================================
void PolyAudioFilePlayer::playSubSection(int64 startSample, int64 length, float gain){
    
    if (masterReader!= nullptr) {
        
    int i;
    //Normalise eroneous gain values
    if (gain > 1) {
        std::cout<<"Gain = "<<gain<<"\n";
        gain = 1;
        
    }
    if (gain < 0) {
        gain = 0;
    }
    
    //Flag true if voice is available
    bool voiceAvailableflag = false;
    
    for (i = 0; i < POLYPHONY;) { //Scan voices for an available voice
        if (!Voices[i]->audioTransportSource.isPlaying()){//If a voice is available, use it and break loop
            std::cout<<"PP: playing Voice "<<i<<"\n";
            Voices[i]->initialise(masterReader, startSample, length);
            Voices[i]->audioTransportSource.setGain(gain);
            Voices[i]->audioTransportSource.start();
            voiceAvailableflag = true;
            break;
        }
        i++;
    }
    
 

    if (!voiceAvailableflag) std::cout<<"PP: No available voice\n";
    }


}
void PolyAudioFilePlayer::stopVoice(int voiceIndex){
    AudioTransportSource* source = &Voices[voiceIndex]->audioTransportSource;
    if (source->isPlaying()){
    source->setGain (0);
    std::cout<<"Stoping Voice "<<voiceIndex<<"\n";
    }
    
}

/** Implementation of the AudioSource method. */
void PolyAudioFilePlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate){
    //    thread.startThread();
    mixer.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

/** Implementation of the AudioSource method. */
void PolyAudioFilePlayer::releaseResources(){
    mixer.releaseResources();
  //  thread.stopThread(0);
    
}

/** Implementation of the AudioSource method. */
void PolyAudioFilePlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill){
    mixer.getNextAudioBlock(bufferToFill);
}

