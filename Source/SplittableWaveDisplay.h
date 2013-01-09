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
#include "SubsectionOverlay.h"
/**==============================================================================
 
 SplittableWaveDisplay allows selecting sub-sections of a PositionableWaveDisplay.
 
 It 
 Features;
    Display 
 
 Todo;
    Represent selected subsections visually
        Create an array of start and end points and trim amounts
        Display Highlights in green and trim in grey
        Crop and scale highlights when zoomed in
    
    Manage Mouseclicks
        Creating subsections Mousedown = startposition, 
        if mouseX > startposition mouseup = endposition
        if mousex < next subsections start time endposition = next subsestion starttime -1
 
 ==============================================================================*/


class SplittableWaveDisplay :   public Component//,
//                                public AudioSubsectionManager::Listener,
//                                public AudioFilePlayer::Listener
{
public:
    SplittableWaveDisplay(AudioThumbnailImage& sourceToBeUsed,
                          TimeSliceThread& threadToUse_);
    ~SplittableWaveDisplay();
    //====================================================================================
    /** Internal */
    void resized();
    /** Internal */
    void paint(Graphics &g);
    
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
    void mouseDown (const MouseEvent& event);
    /**@Internal@*/
    void mouseDrag (const MouseEvent& event);
    /**@Internal@*/
    void mouseUp (const MouseEvent& event);
    
   
    
     //====================================================================================
    
private:
    
    int currentXScale;
    PositionableWaveDisplay waveDisplay;
    AudioSubsectionManager subsections;
    AudioFilePlayer* filePlayer;
    SubsectionOverlay overlay;

};




#endif  // __SPLITTABLEWAVEDISPLAY_H_995DED5__
