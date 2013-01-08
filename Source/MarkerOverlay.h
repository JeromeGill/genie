/*
  ==============================================================================

    MarkerOverlay.h
    Created: 7 Jan 2013 7:01:22pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __MARKEROVERLAY_H_8C3A6156__
#define __MARKEROVERLAY_H_8C3A6156__
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

class MarkerOverlay :  public Component,
                                AudioFilePlayer::Listener
{
public:
    
    
    MarkerOverlay(AudioFilePlayer &filePlayer_);
    ~MarkerOverlay();
 

    //====================================================================================
    /** Creates a marker on a specific sample of the waveDisplay
     */
    void addMarker (int64 startSample);
    /** Deletes the nearest marker to the sample passed on
     */
    void removeMarker (int MarkerIndex);
    /** Amends the start point of a marker at index provided
     */
    void SetSubsectionStart (int64 startSample, int MarkerIndex);
    /** Sets a markers duration
     */
    void SetSubsectionDuration (int64 lengthInSamples, int MarkerIndex);
    /** Returns the index of nearest marker to a provided sample
     */
    int getNearestMarker (int64 Sample);
    /** Clears all markers
     */
    void clear();
    /** Sorts subsections by StartSample
     */
    void sortSubsections();
    
    //====================================================================================
    /** Sample to Pixel conversion
     */
    int  SampleToPixel(int64 sampleClickedOn);
    /** Pixel to Sample conversion
     */
    int64 PixelToSample(double PixelClickedOn);
    /** Sample to time conversion
     */
    double SampleToTime(int64 sample);
    
   //====================================================================================
    /**@Internal@*/
    void paint(Graphics &g);
    /**@Internal@*/
    void resized();
    /**@Internal@*/
    void fileChanged (AudioFilePlayer* player);
    
    /**@Internal@*/
    void mouseDown (const MouseEvent& event);
    /**@Internal@*/
    void mouseDrag (const MouseEvent& event);
    /**@Internal@*/
    void mouseUp (const MouseEvent& event);
private:
    Image markerImage;
    Image highlightImage;
    
    SubsectionComparator subsectionComparator;
    OwnedArray<SubSection> subsection;
    AudioFilePlayer* filePlayer;
    int currentXScale;
    
};




#endif  // __MARKEROVERLAY_H_8C3A6156__
