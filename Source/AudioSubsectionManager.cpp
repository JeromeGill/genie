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
    Overlap = false;
}
AudioSubsectionManager::~AudioSubsectionManager(){
    
}
//====================================================================================
/**Set False to prevent subsection overlap
 */
void AudioSubsectionManager::allowOverlap(bool allowSubsectionsToOverlap = true){
    Overlap = allowSubsectionsToOverlap;
}
//====================================================================================
/**Creates a Subsection on a specific sample of the waveDisplay
 
 */
void AudioSubsectionManager::addSubsection (int64 startSample){
    int index;
    
    std::cout<<"Adding Subsection \n";
    subsection.add(new SubSection);
    subsection.getLast()->StartSample = startSample;
    sortSubsections();
    
    index = getSubsection(startSample);
    listenerList.call(&Listener::subsectionCreated, index);
    
}
/** Deletes subsection at index
 */
void AudioSubsectionManager::removeSubsection (int SubsectionIndex){
    if(SubsectionIndex >= 0 && SubsectionIndex < subsection.size()){
        subsection.remove(SubsectionIndex);
        listenerList.call(&Listener::subsectionDeleted, SubsectionIndex);
    }
    else if(DEBUGSSM){
        std::cout<<"SubsectionManager : removeSubsection received invalid index.\n";
    }
}
/** Returns a subsection's start sample
 */
int64 AudioSubsectionManager::getStart(int SubsectionIndex){
    if(SubsectionIndex >= 0 && SubsectionIndex < subsection.size()){
        return subsection[SubsectionIndex]->StartSample;
    }
    else if(DEBUGSSM){
        std::cout<<"SubsectionManager : getStart received invalid index. Returning 0 \n";
        return 0;
    }
    else return 0;
}
/** Returns a subsection's duration
 */
int64 AudioSubsectionManager::getLength(int SubsectionIndex){
    
    if(SubsectionIndex >= 0 && SubsectionIndex < subsection.size()){
        return subsection[SubsectionIndex]->LengthInSamples;
    }
    else if(DEBUGSSM){
        std::cout<<"SubsectionManager : getStart received invalid index. Returning 0 \n";
        return 0;
    }
    else return 0;
}
/** Sets Start point of a particular Subsection
 */
void AudioSubsectionManager::SetSubsectionStart (int64 startSample, int SubsectionIndex){
    
    if(SubsectionIndex >= 0 && SubsectionIndex < subsection.size()){
        subsection[SubsectionIndex]->StartSample = startSample;
        listenerList.call(&Listener::subsectionChanged, SubsectionIndex);
    }
    else if(DEBUGSSM){
        std::cout<<"SubsectionManager : SetSubsectionStart received invalid index.\n";
    }
}
/** Sets a Subsections duration
 */
void AudioSubsectionManager::SetSubsectionDuration (int64 lengthInSamples, int SubsectionIndex){
    
    if(SubsectionIndex >= 0 && SubsectionIndex < subsection.size()){
        
        if (!Overlap){
            
            if (SubsectionIndex + 1 < subsection.size()) {
                int64 startSample = subsection[SubsectionIndex]->StartSample;
                
                if (startSample + lengthInSamples > subsection[SubsectionIndex + 1]->StartSample) {
                    lengthInSamples = subsection[SubsectionIndex + 1]->StartSample - startSample;
                }
            }
        }
        
        
        
        subsection[SubsectionIndex]->LengthInSamples = lengthInSamples;
        listenerList.call(&Listener::subsectionChanged, SubsectionIndex);
    }
    else if(DEBUGSSM){
        std::cout<<"SubsectionManager : SetSubsectionDuration received invalid index.\n";
    }
}
/** Returns the index of nearest Subsection to a provided sample
 */
int AudioSubsectionManager::getNearestSubsection (int64 Sample){
    
    int i;
    
    std::cout<<"SubsectionManager : getNearestSubsection = ";
    
    if (subsection.size() > 1){
        
        for(i = 1; i < subsection.size() -1 && subsection[i]->StartSample < Sample; i++){}
        
        if(fabs((double) subsection[i]->StartSample - Sample) <
           fabs((double) subsection[i-1]->StartSample - Sample))
            return i;
        
        else{
            if (i)  i--;
            else i = 0;
        }
    }
    else i =0;
    std::cout<<i<<"\n";
    return i;
}
/** Returns the index of the Subsection to the left of the sample clicked on
 */
int AudioSubsectionManager::getPreviousSubsection (int64 Sample){
    int i;
    if(subsection.size())
        for(i = 0; i < subsection.size() && subsection[i]->StartSample < Sample; i++){
            
        }
    return i -1;
}
/** Returns the index of subsection that contains sample
 
 WARNING: returns -1 if no subsection contains sample provided
 */
int AudioSubsectionManager::getSubsection (int64 Sample){
    bool flag = false;
    int i;
    if(subsection.size() > 1){
        for(i = 0; i < subsection.size();){
            
            int64 startSample = subsection[i]->StartSample;
            int64 endSample   = startSample + subsection[i]->LengthInSamples;
            
            //If the sample clicked on is between the start and end samples of a particular slice, delete it
            if (Sample> startSample && Sample < endSample){
                flag = true;
                break;
            }
            
            i++;
        }
    }
    if(flag)
        return i;
    else return -1;
}
//====================================================================================
/** Returns size of subsection array
 */
int  AudioSubsectionManager::size(){
    return subsection.size();
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


