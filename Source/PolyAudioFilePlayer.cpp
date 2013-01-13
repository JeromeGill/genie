/*
  ==============================================================================

    PolyAudioFilePlayer.cpp
    Created: 11 Dec 2012 10:25:31am
    Author:  Jerome

  ==============================================================================
*/

#include "PolyAudioFilePlayer.h"

PolyAudioFilePlayer::PolyAudioFilePlayer(AudioFilePlayer &audioFilePlayer_)
: audioFilePlayer(&audioFilePlayer_),
thread("voices")

{

   
    
    Voices.ensureStorageAllocated(POLYPHONY);
    //Initialise Voices
     for (int i = 0; i < POLYPHONY;) {
         Voices.add(new PolyPlayerVoice(thread));
         mixer.addInputSource(Voices.getLast()->getAudioSource(), true);
         i++;
     }
    
     audioFilePlayer->addListener(this);
}

PolyAudioFilePlayer::~PolyAudioFilePlayer()
{
    audioFilePlayer->removeListener(this);
    
}


void PolyAudioFilePlayer::playSubSection(int64 startSample, int64 length, float gain){
    
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
    
    for (i = 0; i < POLYPHONY;) {
        if (!Voices[i]->getAudioSource()->isPlaying()) {
            std::cout<<"PP: playing Voice "<<i<<"\n";
            Voices[i]->initialise(masterReader, startSample, length);
            Voices[i]->getAudioSource()->setGain(gain);
            Voices[i]->getAudioSource()->start();
            voiceAvailableflag = true;
            break;
        }
        i++;
    }
    
 

    if (!voiceAvailableflag) std::cout<<"PP: No available voice\n";


}
void PolyAudioFilePlayer::stopVoice(int voiceIndex){
    AudioTransportSource* source = Voices[voiceIndex]->getAudioSource();
    if (source->isPlaying()){
    source->setGain (0);
    std::cout<<"Stoping Voice "<<voiceIndex<<"\n";
    }
    
}
//==============================================================================
//Callbacks
void PolyAudioFilePlayer::fileChanged(AudioFilePlayer *player){
    masterReader = audioFilePlayer->getAudioFormatManager()->createReaderFor(audioFilePlayer->getFile());
    
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

