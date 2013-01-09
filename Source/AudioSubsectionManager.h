/*
  ==============================================================================

    AudioSubsectionManager.h
    Created: 7 Jan 2013 7:01:22pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __AudioSubsectionManager_H_8C3A6156__
#define __AudioSubsectionManager_H_8C3A6156__
#include "genieHeader.h"



struct SubSection{
    int64 StartSample;
    int64 LengthInSamples = 0;
};

class SubsectionComparator
{
public:
    int compareElements (SubSection* first, SubSection* second){
        return first->StartSample - second->StartSample;
    }
};

class AudioSubsectionManager
{
public:

    AudioSubsectionManager(AudioFilePlayer &filePlayer_);
    ~AudioSubsectionManager();
 

    //====================================================================================
    /** Creates a Subsection on a specific sample of the waveDisplay
     */
    void addSubsection (int64 startSample);
    /** Deletes a Subsection at a particular index
     */
    void removeSubsection (int SubsectionIndex);
    /** Returns a subsection's start sample
     */
    int64 getStart(int SubsectionIndex);
    /** Returns a subsection's duration
     */
    int64 getLength(int SubsectionIndex);
    /** Amends the start point of a Subsection at index provided
     */
    void SetSubsectionStart (int64 startSample, int SubsectionIndex);
    /** Sets a Subsections duration
     */
    void SetSubsectionDuration (int64 lengthInSamples, int SubsectionIndex);
    
    /** Returns the index of nearest Subsection to a provided sample
     */
    int getNearestSubsection (int64 Sample);
    /** Returns the index of the Subsection to the left of the sample clicked on
     */
    int getPreviousSubsection (int64 Sample);
    
    //====================================================================================
    /** Returns size of subsection array
     */
    int size();
    /** Clears all Subsections
     */
    void clear();
    /** Sorts subsections by StartSample
     */
    void sortSubsections();
    
   
    //====================================================================================
    /** Sample to time conversion
     */
    double SampleToTime(int64 sample);
    
    //====================================================================================
    /** Listener 
     */
    class Listener
    {
    public:
        virtual ~Listener(){};
        /** Called when a subsection is created
         */
        virtual void subsectionCreated(){};
        /** Called when a subsection is deleted
         */
        virtual void subsectionDeleted(){};
        /** Called when a subsection has a value changed
         */
        virtual void subsectionChanged(int SubsectionIndex){};
    };
    /** add a listener 
     */
    void addListener(Listener* listener);
    /** Remove a listener
     */
    void removeListener(Listener* listener);
    
    //====================================================================================
    /**@Internal@*/
    
private:
  
    ListenerList<Listener> listenerList;
    
    SubsectionComparator subsectionComparator;
    OwnedArray<SubSection> subsection;
    AudioFilePlayer* filePlayer;

    
};




#endif  // __AudioSubsectionManager_H_8C3A6156__
