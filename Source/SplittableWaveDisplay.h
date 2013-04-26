/*
  ==============================================================================

    SplittableWaveDisplay.h
    Created: 31 Dec 2012 3:42:49pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SPLITTABLEWAVEDISPLAY_H_995DED5__
#define __SPLITTABLEWAVEDISPLAY_H_995DED5__
#include "genieHeader.h"
#include "AudioSubsectionManager.h"
//==============================================================================
/*

 \breif SplittableWaveDisplay allows selecting sub-sections of a [drow::PositionableWaveDisplay].

 @see AudioSubsectionManager
 @see [drow::PositionableWaveDisplay]

 Shift-Double click creates new subsection
 Alt-Shift double click deletes one
 Shift click changes previous slices duration
 Alt shift drag moves nearest slice
 
 [drow::PositionableWaveDisplay]: http://drowaudio.co.uk/docs/class_positionable_wave_display.html
*/
//==============================================================================

class SplittableWaveDisplay :   public Component,
                                public AudioSubsectionManager::Listener,
                                public drow::AudioFilePlayer::Listener
{
public:
    SplittableWaveDisplay(drow::AudioThumbnailImage& sourceToBeUsed,
                          TimeSliceThread& threadToUse_,
                          AudioSubsectionManager& subsectionManager_);
    ~SplittableWaveDisplay();
    //====================================================================================
    /** Internal */
    void resized();
    /** Internal */
    void paint(Graphics &g);
    /** Internal */
    void paintOverChildren(Graphics &g);
    
    //====================================================================================
	/** Sets whether or not the transport cursor should be displayed;
     */
    void setCursorDisplayed (bool shoudldDisplayCursor);
    
    /** Sets the colour to use for the background.
     */
    void setBackgroundColour (Colour newBackgroundColour);
    
    /** Sets the colour to use for the waveform.
     */
    void setWaveformColour (Colour newWaveformColour);
    
	/** Sets the current horizontal zoom.
     1.0 displays the whole waveform, 0.5 will show half etc.
     */
	void setZoomRatio (double newZoomRatio);
    
    /** Sets an offset used to start the waveform at a faction of the display.
     A value of 0.5 will show the waveform starting at the halfway point etc.
     */
	void setStartOffsetRatio (double newStartOffsetRatio);
    
    /** Sets a new vertical zoom ratio.
     Values greater than 1.0 will expand the waveform vertically, less will contract it.
     */
    void setVerticalZoomRatio (double newVerticalZoomRatio);
    
    //====================================================================================
    /**@Internal@*/
    void subsectionCreated(int SubsectionIndex);
    /**@Internal@*/
    void subsectionDeleted(int SubsectionIndex);
    /**@Internal@*/
    void subsectionChanged(int SubsectionIndex);
    /**@Internal@*/
    void fileChanged (drow::AudioFilePlayer* player);
    
    //====================================================================================
    /** Sample to Pixel conversion
     */
    int  SampleToPixel(int64 sampleClickedOn);
    /** Pixel to Sample conversion
     */
    int64 PixelToSample(double PixelClickedOn);
    
    //====================================================================================
    /**@Internal@*/
    void mouseDown (const MouseEvent& event);
    /**@Internal@*/
    void mouseDoubleClick (const MouseEvent& event);
    /**@Internal@*/
    void mouseDrag (const MouseEvent& event);
    /**@Internal@*/
    void mouseUp (const MouseEvent& event);
    
     //====================================================================================
    
private:
    int FlagforRepaint;
    int currentXScale;
    drow::PositionableWaveDisplay waveDisplay;
    AudioSubsectionManager& subsections;
    drow::AudioFilePlayer* filePlayer;
    

    Image highlightImage;
    Image *SubsectionImage;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SplittableWaveDisplay)
};




#endif  // __SPLITTABLEWAVEDISPLAY_H_995DED5__
