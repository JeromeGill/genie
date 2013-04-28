/*
 ==============================================================================
 
 AudioSubsectionManager.cpp
 Created: 7 Jan 2013 7:01:22pm
 Author:  Jerome
 
 ==============================================================================
 */

#include "AudioSubsectionManager.h"

AudioSubsectionManager::AudioSubsectionManager(drow::AudioFilePlayer &filePlayer_)
: filePlayer(&filePlayer_)
{
    HitTypeStringArray.add("Unnamed");
    HitTypeStringArray.add("Kick");
    HitTypeStringArray.add("Snare");
    HitTypeStringArray.add("High-Hat");
    HitTypeStringArray.add("Crash");
    HitTypeStringArray.add("Ride");
    
    Overlap = false;
}
AudioSubsectionManager::~AudioSubsectionManager(){
    
}

/**Returns a copy of a Subsection
 */
 SubSection AudioSubsectionManager::operator[] (int SubsectionIndex){
   
    SubSection s;
    if(SubsectionIndex >= 0 && SubsectionIndex < subsection.size()){
        s = *subsection[SubsectionIndex];

    }
    else if(DEBUGSSM){
        std::cout<<"SubsectionManager : Name received invalid index.\n";
    }
    return s;
}


//====================================================================================
/**Return HitTypeValue as Juce String
 */
const String AudioSubsectionManager::HitTypeString(HitTypeValue hitTypeValue){
    return HitTypeStringArray[hitTypeValue];
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
    if (filePlayer->getFile().exists()) {
    std::cout<<"Adding Subsection \n";
    subsection.add(new SubSection);
    subsection.getLast()->StartSample = startSample;
    subsection.getLast()->name = "Slice ";
    subsection.getLast()->name += subsection.size() - 1;
    sortSubsections();
    
    index = getSubsection(startSample);
    listenerList.call(&Listener::subsectionCreated, index);
    }
    else if(DEBUGSSM){
        std::cout<<"SubsectionManager : Add Subsection... File doesn't exist.\n";
    }
        
    
}
/** Names a Subsection
 */
void AudioSubsectionManager::nameSubsection(int SubsectionIndex, String Name){
    if(SubsectionIndex >= 0 && SubsectionIndex < subsection.size()){
        subsection[SubsectionIndex]->name << " : "<<Name;
    }
    else if(DEBUGSSM){
        std::cout<<"SubsectionManager : Name received invalid index.\n";
    }
}

/** Returns a Subsection's name
 */
String AudioSubsectionManager::getName(int SubsectionIndex){
    String Name = "Null";
    if(SubsectionIndex >= 0 && SubsectionIndex < subsection.size()){
        Name = subsection[SubsectionIndex]->name;
    }
    else if(DEBUGSSM){
        std::cout<<"SubsectionManager : Name received invalid index. Returning 'Null' \n";
    }
    return Name;
}
/** Returns a Subsection's type as a Juce String
 
 May return "Unnamed" if a type has not yet been set.
 */
const String AudioSubsectionManager::getTypeAsString(int SubsectionIndex){
    String Name = "Null";
    if(SubsectionIndex >= 0 && SubsectionIndex < subsection.size()){
        HitTypeValue v = subsection[SubsectionIndex]->TypeValue;
        Name = HitTypeStringArray[v];
    }
    else if(DEBUGSSM){
        std::cout<<"SubsectionManager : Name received invalid index. Returning 'Null' \n";
    }
    return Name;
}

/** Sets a Subsection's type
 */
void AudioSubsectionManager::setSubsectionType(int SubsectionIndex, int type){
    
    HitTypeValue i = (HitTypeValue) type;
    
    if(SubsectionIndex >= 0 && SubsectionIndex < subsection.size()){
        if (type > 0 && type < TotalHitTypes) {
            
            subsection[SubsectionIndex]->TypeValue = i;
            subsection[SubsectionIndex]->name =getTypeAsString(SubsectionIndex);
            std::cout<<"SubsectionManager : "<<getTypeAsString(SubsectionIndex)<<"\n";
        }
        else if (DEBUGSSM){
           std::cout<<"SubsectionManager : setSubsectionType received invalid type value.\n";
        }
    }
    else if(DEBUGSSM){
        std::cout<<"SubsectionManager : setSubsectionType received invalid index.\n";
    }
}
/** returns a Subsection's type
 */
HitTypeValue AudioSubsectionManager::getSubsectionType(int SubsectionIndex){
    HitTypeValue v = Unnamed;
    
    if(SubsectionIndex >= 0 && SubsectionIndex < subsection.size()){
        v = subsection[SubsectionIndex]->TypeValue;

    }
    else if(DEBUGSSM){
        std::cout<<"SubsectionManager : getSubsectionType received invalid index.\n";
    }
    return v;
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
    
    if(DEBUGSSM)std::cout<<"SubsectionManager : getNearestSubsection = ";
    
    if (subsection.size() > 1){
        
        for(i = 1; i < subsection.size() -1 && subsection[i]->StartSample < Sample; i++){} //Scan subsection array until a subsection with a greater
        
        if(fabs((double) subsection[i]->StartSample - Sample) <
           fabs((double) subsection[i-1]->StartSample - Sample))
            return i;
        
        else{
            if (i)  i--;
            else i = 0;
        }
    }
    else i =0;
    
    if(DEBUGSSM)std::cout<<i<<"\n";
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
    listenerList.call(&Listener::subsectionsCleared);
}
/** Sorts subsections by StartSample
 */
void AudioSubsectionManager::sortSubsections(){
    if(subsection.size() > 2)
        subsection.sort(subsectionComparator);
    for(int i = 0; i < subsection.size() -1; i ++){
        if (subsection[i]->StartSample == subsection[i+1]->StartSample)
            subsection.remove(i);
        subsection[i]->name = "Slice ";
        subsection[i]->name += i;
        
        if (subsection[i]->TypeValue != Unnamed) {
            subsection[i]->name <<" ";
            subsection[i]->name += HitTypeString(subsection[i]->TypeValue);
        }
        std::cout<<"subsection Start"<<subsection[i]->StartSample<<"\n";
    }
}

//====================================================================================
double AudioSubsectionManager::SampleToTime(int64 sample){
    return (double) sample * (filePlayer->getLengthInSeconds() / filePlayer->getTotalLength());
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


