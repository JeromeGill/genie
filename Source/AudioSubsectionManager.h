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

#define DEBUGSSM 0 //set to a positive value to print debug messages

struct SubSection{
    int64 StartSample;
    int64 LengthInSamples = 0;
    String name = "null";
};

class SubsectionComparator
{
public:
    int compareElements (SubSection* first, SubSection* second){
        return first->StartSample - second->StartSample;
    }
};


/**==============================================================================
 AudioSubsectionManager holds an OwnedArray of SubSection data structures.
 
 Contains a JUCE style Listener Class
 
 Features;
    Create subsection
    Delete Subsection
    Set start + length of a particular subsection
    Return subsection that contains a particular sample
    Return the nearest subsection to a particular sample
 
    Sort subsections by startsample
    Convert samples to timestamps
 
 ToDo;
 
 ============================================================================== */

class AudioSubsectionManager
{
public:

    AudioSubsectionManager(AudioFilePlayer &filePlayer_);
    ~AudioSubsectionManager();
 
    //====================================================================================
    /**Set False to prevent subsection overlap
     */
    void allowOverlap(bool allowSubsectionsToOverlap);

    //====================================================================================
    /** Creates a Subsection on a specific sample of the waveDisplay
     */
    void addSubsection (int64 startSample);
    /** Names a Subsection
     */
    void nameSubsection (int SubsectionIndex, String Name);
    /** Returns a Subsection's name
     */
    String getName(int SubsectionIndex);
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
    /** Returns the index of subsection that contains Sample
     
     Returns -1 if no subsection contains sample provided
     */
    int getSubsection (int64 Sample);
    
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
        virtual void subsectionCreated(int SubsectionIndex){};
        /** Called when a subsection is deleted
         */
        virtual void subsectionDeleted(int SubsectionIndex){};
        /** Called when a subsection has a value changed
         */
        virtual void subsectionChanged(int SubsectionIndex){};
        /** Called when subsection array is cleared
         */
        virtual void subsectionsCleared(){};
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
  
    bool Overlap;
    
    ListenerList<Listener> listenerList;
    
    SubsectionComparator subsectionComparator;
    OwnedArray<SubSection> subsection;
    AudioFilePlayer* filePlayer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSubsectionManager)
    
};




#endif  // __AudioSubsectionManager_H_8C3A6156__
