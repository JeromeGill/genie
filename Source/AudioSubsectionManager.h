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
#include "SubSection.h"


#define DEBUGSSM 0 //set to a positive value to print debug messages


class SubsectionComparator
{
public:
    int compareElements (SubSection* first, SubSection* second){
        return first->StartSample - second->StartSample;
    }
};



//==============================================================================
/**AudioSubsectionManager
 \brief AudioSubsectionManager manages an array of SubSection data structures.

 It features;
 Several useful search algorithms for selecting SubSections, getNearest, getPrevious.
 Sort by start time
 
 Juce [ListenerList] style feature for returning created and modified subection indexes
 Sample to time conversion for a [drow:AudioFilePlayer]
 
 [ListenerList]:http://rawmaterialsoftware.com/juce/api/classListenerList.html (Listener)
 [drow:AudioFilePlayer]: http://drowaudio.co.uk/docs/class_audio_file_player.html (drow:AudioFilePlayer)

 
*/
//==============================================================================

class AudioSubsectionManager
{
public:
    
    
    StringArray HitTypeStringArray;
    
    AudioSubsectionManager(drow::AudioFilePlayer &filePlayer_);
    ~AudioSubsectionManager();

    /**Returns a copy of a Subsection
     */
    SubSection operator[] (int subsectionIndex);

    
    //====================================================================================
    /**Set False to prevent subsection overlap
     */
    void allowOverlap(bool allowSubsectionsToOverlap);

    //====================================================================================
    /** Creates a Subsection on a specific sample of the waveDisplay
     */
    void addSubsection (int64 startSample);
   
    /** Deletes a Subsection at a particular index
     */
    void removeSubsection (int SubsectionIndex);
    //====================================================================================
    /** Amends the start point of a Subsection at index provided
     */
    void SetSubsectionStart (int64 startSample, int SubsectionIndex);
    /** Sets a Subsections duration
     */
    void SetSubsectionDuration (int64 lengthInSamples, int SubsectionIndex);
    //====================================================================================
    /** Names a Subsection
     */
    void nameSubsection (int SubsectionIndex, String Name);
    /** Sets a Subsection's type
     */
    void setSubsectionType(int SubsectionIndex, int type);
    /** Returns a Subsection's Type as a Juce String
     */
    const String getTypeAsString(int SubsectionIndex);
    /** Returns a Subsection's Type
     */
    HitTypeValue getSubsectionType(int SubsectionIndex);
    
    //====================================================================================
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
    /**Return HitTypeValue as Juce String
     */
    const String HitTypeString(HitTypeValue hitTypeValue);
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
    
private:
  
    bool Overlap;
    
    ListenerList<Listener> listenerList;
    
    SubsectionComparator subsectionComparator;
    OwnedArray<SubSection> subsection;
    drow::AudioFilePlayer* filePlayer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSubsectionManager)
    
};

#endif  // __AudioSubsectionManager_H_8C3A6156__
