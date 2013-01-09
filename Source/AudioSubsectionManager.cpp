/*
  ==============================================================================

    AudioSubsectionManager.cpp
    Created: 7 Jan 2013 7:01:22pm
    Author:  Jerome

  ==============================================================================
*/

#include "AudioSubsectionManager.h"

AudioSubsectionManager::AudioSubsectionManager(AudioFilePlayer &filePlayer_)
: filePlayer(&filePlayer_)
{
    
}
AudioSubsectionManager::~AudioSubsectionManager(){

}



//====================================================================================
/**Creates a Subsection on a specific sample of the waveDisplay
 */
void AudioSubsectionManager::addSubsection (int64 startSample){
    std::cout<<"Adding Subsection \n";
    subsection.add(new SubSection);
    subsection.getLast()->StartSample = startSample;
    sortSubsections();
    listenerList.call(&Listener::subsectionCreated);

}
/** Deletes the nearest Subsection to the sample passed on
 */
void AudioSubsectionManager::removeSubsection (int SubsectionIndex){
    subsection.remove(SubsectionIndex);
    listenerList.call(&Listener::subsectionDeleted);
}
/** Returns a subsection's start sample
 */
int64 AudioSubsectionManager::getStart(int SubsectionIndex){
    return subsection[SubsectionIndex]->StartSample;
}
/** Returns a subsection's duration
 */
int64 AudioSubsectionManager::getLength(int SubsectionIndex){
    return subsection[SubsectionIndex]->LengthInSamples;
}
/** Sets Start point of a particular Subsection
 */
void AudioSubsectionManager::SetSubsectionStart (int64 startSample, int SubsectionIndex){
    subsection[SubsectionIndex]->StartSample = startSample;
    listenerList.call(&Listener::subsectionChanged, SubsectionIndex);
}
/** Sets a Subsections duration
 */
void AudioSubsectionManager::SetSubsectionDuration (int64 lengthInSamples, int SubsectionIndex){
    subsection[SubsectionIndex]->LengthInSamples = lengthInSamples;
    listenerList.call(&Listener::subsectionChanged, SubsectionIndex);
}
/** Returns the index of nearest Subsection to a provided sample
 */
int AudioSubsectionManager::getNearestSubsection (int64 Sample){
    int i;
    if (subsection.size() > 1){
        for(i = 1; i < subsection.size() && subsection[i]->StartSample < Sample; i++){
            std::cout<<"Comparing \n";
        }
        if(fabs((double) subsection[i]->StartSample - Sample) < fabs((double) subsection[i-1]->StartSample - Sample))
            return i;
        else
            return i - 1;
        
    }
    else
        return 0;
}
//====================================================================================
/** Returns size of subsection array
 */
int  AudioSubsectionManager::size(){
    return subsection.size();
}
int AudioSubsectionManager::getPreviousSubsection (int64 Sample){
    int i = 1;
    if(subsection.size())
    for(; i < subsection.size() && subsection[i]->StartSample > Sample; i++);
    return i - 1;
}
/** Clears all Subsections
 */
void AudioSubsectionManager::clear(){
    subsection.clear();
}
/** Sorts subsections by StartSample
 */
void AudioSubsectionManager::sortSubsections(){
    if(subsection.size() > 2)
       subsection.sort(subsectionComparator);
    for(int i = 0; i < subsection.size() -1; i ++){
        if (subsection[i]->StartSample == subsection[i+1]->StartSample)
            subsection.remove(i);
            std::cout<<"subsection Start"<<subsection[i]->StartSample<<"\n";
    }
}

//====================================================================================
double AudioSubsectionManager::SampleToTime(int64 sample){
    return (double) sample * (filePlayer->getTotalLength() / filePlayer->getLengthInSeconds());
}
//====================================================================================
/** add a listener
 */
void AudioSubsectionManager::addListener(Listener* listener){
    listenerList.add(listener);
}
/** Remove a listener
 */
void AudioSubsectionManager::removeListener(Listener* listener){
    listenerList.remove(listener);
}


