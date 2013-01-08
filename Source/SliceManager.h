/*
  ==============================================================================

    SliceManager.h
    Created: 2 Dec 2012 6:35:45pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SLICEMANAGER_H_375C4A0F__
#define __SLICEMANAGER_H_375C4A0F__

#include "genieHeader.h"
#include "SliceData.h"
#include "PolyAudioFilePlayer.h"

/**==============================================================================
 SliceManager is responsable for an array of SliceData objects.
 
 Features;
    Sorts created slices by their start points
    Returns a cropped Image of a subsection of an AudioThumbnailImage
 
 ToDo;
    Rethink the way slices are created and deleted, perhaps just do it all with samples
==============================================================================*/
class SliceComparator
{
public:
    int compareElements (SliceData* first, SliceData* second){
        return first->getStartPosition() - second->getStartPosition();
    }
};

class SliceManager :    public Component,
                        public AudioFilePlayer::Listener,
                        public MidiKeyboardStateListener
{
public:
    SliceManager(AudioFilePlayer &audioFilePlayer_,
                 MidiKeyboardState &keyboardState_,
                 PolyAudioFilePlayer &polyPlayer_);
    ~SliceManager();
    
    /**@Internal@*/
    void resized();
    /**@Internal@*/
    void paint(Graphics &g);
    
    /**Initialise SliceData array
     Called when the AudioFilePlayer's file is changed*/
    void initialiseSlices();
    
    /**Sets the AudioThumbnailImage used*/
    void setAudioThumbnailImage(AudioThumbnailImage *image);
    
    
    void setBPM(int BPM);
    
    /**Create a Slice from a mouseX < Definately needs rethinking*/
    void createSlice(double mouseX);
    /**Deletes whatever slice that includes a mouseX < Definately needs rethinking*/
    void deleteSlice(double mouseX);
    
    /**Returns a SliceData at a particular index*/
    SliceData* getSlice(int sliceIndex);
    
    /**Set the start sample for a particular slice from a time position*/
    void setSliceStartSample   (int markerIndex, double position);
     /**Set the end sample for a particular slice from a time position*/
    void setSliceEndSample     (int markerIndex, double position);
    
    /**returns the start sample for a slice at a particular index*/
    int64 getSliceStartSample   (int markerIndex);
    /**returns the end sample for a slice at a particular index*/
    int64 getSliceEndSample     (int markerIndex);
    
    /**Play a slice at a particular index
     Optionally set a gain as a float between 0 and 1
     */
    void playSlice(int sliceIndex, float gain = 1);
    /**Stop a slice playing at a particular index*/
    void stopSlice(int sliceIndex);
    
    
    //void makeImageForSlice(int sliceIndex);
    
    /**@Internal@*/
    void fileChanged(AudioFilePlayer *player);
    
    /**@Internal@*/
    void handleNoteOn (MidiKeyboardState* source,
                       int midiChannel,
                       int midiNoteNumber,
                       float velocity);
    /**@Internal@*/
    void handleNoteOff (MidiKeyboardState* source,
                        int midiChannel,
                        int midiNoteNumber);
    
    /**returns the AudioFilePlayer used*/
    AudioFilePlayer* getAudioFilePlayer();
    
  
    class Listener
    {
    public:
        virtual ~Listener() {};
        virtual void sliceCreated(){};
        virtual void sliceDeleted(){};
        virtual void sliceInitialised(){};
    };
    
    void addListener(Listener *listener);
    void removeListener(Listener *Listener);

private:
    
    void SortSliceArray();
    
    int TimeToTick(double Time){
        int tick;
        return tick;
    }
    
    uint64  SampleToPixel(int64 sampleClickedOn){ // needs to include zoom ratio and offset values
        return sampleClickedOn / currentXScale;
    }
    int64   PixelToSample(double PixelClickedOn){
        int64 sampleClickedOn = roundToInt((float)currentXScale * PixelClickedOn);
        return sampleClickedOn;
    }
    double  SampleToTime(int64 sample){
        
        double time = (double) sample * (audioFilePlayer->getTotalLength() / audioFilePlayer->getLengthInSeconds());
        return time;
    }
    
   
    
    AudioFilePlayer* audioFilePlayer;
    MidiKeyboardState* keyboardState;
    
    AudioThumbnailImage* audioThumbnailImage;

    ListenerList<Listener> Listeners;
    
    //resizing
    int w,h;
    int sampleRate, bpm;
    int currentXScale;
    double currentTScale;
    
    PolyAudioFilePlayer* polyAudioFilePlayer; //The key to polyphony
    OwnedArray<SliceData> sliceArray;
    SliceComparator sliceComparator;
    uint64 audioFileLength;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliceManager)
};



#endif  // __SLICEMANAGER_H_375C4A0F__
