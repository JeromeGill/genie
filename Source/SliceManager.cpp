/*
 ==============================================================================
 
 SliceManager.cpp
 Created: 2 Dec 2012 6:35:45pm
 Author:  Jerome
 
 ==============================================================================
 */

#include "SliceManager.h"

SliceManager::SliceManager(AudioFilePlayer &audioFilePlayer_,
                           MidiKeyboardState &keyboardState_,
                           PolyAudioFilePlayer &polyPlayer_)
: audioFilePlayer(&audioFilePlayer_),
keyboardState(&keyboardState_),
polyAudioFilePlayer(&polyPlayer_)


{
    audioThumbnailImage = nullptr;
    setInterceptsMouseClicks(false, false);
    audioFilePlayer->addListener(this);
    keyboardState->addListener(this);
    
}

SliceManager::~SliceManager()
{
    audioFilePlayer->removeListener(this);
    keyboardState->removeListener(this);
}

void SliceManager::setAudioThumbnailImage(AudioThumbnailImage *image){
    audioThumbnailImage = image;
}

//==============================================================================
//Component
void SliceManager::resized(){
    w = getWidth();
    h = getHeight();
    
}
void SliceManager::paint(Graphics &g){
    
}

//==============================================================================
//Slice managment
void SliceManager::initialiseSlices(){
    
    sliceArray.clear(true);
    sliceArray.add(new SliceData(0,
                                 audioFilePlayer->getTotalLength() - 1,
                                 0));
    std::cout<<"Initalising Slices \n";
    Listeners.call(&Listener::sliceInitialised);
}

SliceData* SliceManager::getSlice(int sliceIndex){
    return sliceArray[sliceIndex];
}



/** Create a New Slice */
void SliceManager::createSlice(double mouseX){
    
    //Need to convert pixel to sample
    int64 sampleClickedOn = PixelToSample(mouseX);
    
    bool sliceExistsFlag = true;
    
    //Check to see if the startlocation clicked on already exists
    for (int i = 0; i < sliceArray.size(); i++)
        if(sliceArray[i]->getStartPosition() == sampleClickedOn)
            sliceExistsFlag = false;
    
    //Create a Slice with its start position where the user clicked
    if(sliceArray.size() && sliceExistsFlag){
        
        sliceArray.add(new SliceData(sampleClickedOn,
                                     audioFileLength,
                                     sliceArray.size()));
       
        
        SortSliceArray();
        
        Listeners.call(&Listener::sliceCreated);
    }
     else std::cout<<"No SliceArray Created \n";
}

/** Delete a Slice */
void SliceManager::deleteSlice(double mouseX){
    
    int64 startSample, endSample;
    //Need to convert Pixel clicked on to Sample in audio file
    int64 sampleClickedOn = PixelToSample(mouseX);
   
    //Search for the slice clicked on
    if(sliceArray.size() > 1){
        for(int i = 0; i < sliceArray.size();){
            
            startSample = sliceArray[i]->getStartPosition();
            endSample   = sliceArray[i]->getEndPosition();
            
            //If the sample clicked on is between the start and end samples of a particular slice, delete it
            if (sampleClickedOn > startSample && sampleClickedOn < endSample){
                sliceArray.remove(i);
                std::cout<<"Deleting Slice that contains sample "<<sampleClickedOn<<" at position "<<i<<"\n";;
            }
            
            i++;
        }
        SortSliceArray();
        
        Listeners.call (&Listener::sliceDeleted);
    }
    
    
    
}

void SliceManager::setSliceEndSample(int sliceIndex, double position){
    //.startSample = position;
}
void SliceManager::setSliceStartSample(int sliceIndex, double position){
    //.endSample = position;
}

void SliceManager::setBPM(int BPM)
{
    bpm = BPM;
}

int64 SliceManager::getSliceStartSample   (int markerIndex){
    return sliceArray[markerIndex]->getStartPosition();
}
int64 SliceManager::getSliceEndSample     (int markerIndex){
    return sliceArray[markerIndex]->getEndPosition();
}

void SliceManager::playSlice(int sliceIndex, float gain){
     std::cout<<"SM: Playing slice"<<sliceIndex<<"\n";
    if (sliceArray.size() > sliceIndex) {
        SliceData *slice = sliceArray[sliceIndex];
        polyAudioFilePlayer->playSubSection(slice->getStartPosition(),
                                                                  slice->getTotalLength(),
                                                                  gain);
       
    }
    else std::cout<<"playSlice SliceIndex "<<sliceIndex<<" out of scope \n";
    
}
void SliceManager::stopSlice(int sliceIndex){
    
    if (sliceArray.size() > sliceIndex) {
        polyAudioFilePlayer->stopVoice(sliceIndex);
        std::cout<<"stopSlice SliceIndex "<<sliceIndex<<"\n";
    }
    else std::cout<<"stopSlice SliceIndex "<<sliceIndex<<" out of scope \n";
    
}


AudioFilePlayer* SliceManager::getAudioFilePlayer(){
    return audioFilePlayer;
}

void SliceManager::SortSliceArray(){
        int64 startSample, endSample;
        
        //Sort Slice Array
        if(sliceArray.size() > 2)
            sliceArray.sort(sliceComparator);
        else std::cout<<"No need to sort only 2 slices \n";
        
        
        //ReAdjust End Positions
        for(int i = sliceArray.size(); i > 0 ;){
            i--;
            
            //Get start and end samples for the current slice
            startSample = sliceArray[i]->getStartPosition();
            endSample = sliceArray[i]->getEndPosition();
            
            //If slice > 0 Adjust the end position of the previous slice then adjust the end position of the moved slice
            if(i) sliceArray[i - 1]->setEndPosition(startSample);
            
            
            //sliceArray[i]->setSliceIndex(i);
            addAndMakeVisible(sliceArray[i]);
            
            //calculate position on the wavefile
            sliceArray[i]->setBounds(SampleToPixel(startSample),
                                     0,
                                     SampleToPixel(endSample - startSample),
                                     h);
            
            //Print start and end locations of each slice
            std::cout<<"Slice "<<i<<" Start : "<<startSample<<" :: End "<<endSample<<"\n";
            
            if (audioThumbnailImage!= nullptr) {
                double startTime = SampleToTime(sliceArray[i]->getStartPosition());
                double endTime   = SampleToTime(sliceArray[i]->getTotalLength());
                Image image = audioThumbnailImage->getImageAtTime(startTime,
                                                                  endTime);
                std::cout<<"Making Image. StartTime: "<<startTime<<" EndTime: "<<endTime<<"\n";
                
                sliceArray[i]->setImage(&image);
            }
            
         }
}

//==============================================================================
//Callbacks
void SliceManager::fileChanged(AudioFilePlayer *player){
    
    audioFileLength = player->getTotalLength();
    currentXScale   = (audioFileLength / w);
    initialiseSlices();
    
}

//==============================================================================
//Midi
void SliceManager::handleNoteOn (MidiKeyboardState* source,
                                 int midiChannel, int midiNoteNumber, float velocity){
    
    std::cout<<"NoteNumber = "<<midiNoteNumber<<"\n";
    if (midiNoteNumber >= 48) playSlice(midiNoteNumber - 48, velocity);
}

void SliceManager::handleNoteOff (MidiKeyboardState* source,
                                  int midiChannel, int midiNoteNumber){
    if (midiNoteNumber >= 48) stopSlice(midiNoteNumber - 48);
}

//==============================================================================
//Listeners
void SliceManager::addListener (SliceManager::Listener* const listener)
{
    Listeners.add (listener);
}

void SliceManager::removeListener (SliceManager::Listener* const listener)
{
    Listeners.remove (listener);
}

//==============================================================================
//Test



//AudioFilePlayer* SliceManager::getAudioFilePlayer(){return audioFilePlayer;}