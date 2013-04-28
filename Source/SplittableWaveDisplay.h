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
/**SplittableWaveDisplay
 \brief SplittableWaveDisplay allows selecting sub-sections of a [drow::PositionableWaveDisplay].

 @see AudioSubsectionManager
 @see [drow::PositionableWaveDisplay]

 Shift-Double click creates new subsection
 Alt-Shift double click deletes one
 Shift click changes previous slices duration
 Alt shift drag moves nearest slice
 
 Todo;
 Zoom + Offset
 
 [drow::PositionableWaveDisplay]: http://drowaudio.co.uk/docs/class_positionable_wave_display.html (drow:PositionableWaveDisplay)
*///==============================================================================

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
    /** Sample to Pixel conversion
     */
    int  SampleToPixel(int64 sampleClickedOn);
    /** Pixel to Sample conversion
     */
    int64 PixelToSample(double PixelClickedOn);
    
    //====================================================================================
    /** @internal */
    void subsectionCreated(int SubsectionIndex);
    /** @internal */
    void subsectionDeleted(int SubsectionIndex);
    /** @internal */
    void subsectionChanged(int SubsectionIndex);
    /** @internal */
    void fileChanged (drow::AudioFilePlayer* player);
    //====================================================================================
    /** @internal */
    void resized();
    /** @internal */
    void paint(Graphics &g);
    /** @internal */
    void paintOverChildren(Graphics &g);
    //====================================================================================
    /** @internal */
    void mouseDown (const MouseEvent& event);
    /** @internal */
    void mouseDoubleClick (const MouseEvent& event);
    /** @internal */
    void mouseDrag (const MouseEvent& event);
    /** @internal */
    void mouseUp (const MouseEvent& event);
    
     //====================================================================================
    
private:
  
    int currentXScale;
    drow::PositionableWaveDisplay waveDisplay;
    AudioSubsectionManager& subsections;
    drow::AudioFilePlayer* filePlayer;
    

    Image highlightImage;
    Image *SubsectionImage;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SplittableWaveDisplay)
};




#endif  // __SPLITTABLEWAVEDISPLAY_H_995DED5__
