/*
  ==============================================================================

    SubsectionOverlay.h
    Created: 9 Jan 2013 7:02:59pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SUBSECTIONOVERLAY_H_4F13024B__
#define __SUBSECTIONOVERLAY_H_4F13024B__
#include "genieHeader.h"
#include "AudioSubsectionManager.h"

class SubsectionOverlay : public Component,
public AudioSubsectionManager::Listener,
public AudioFilePlayer::Listener
{
public:
    SubsectionOverlay(AudioSubsectionManager *AudioSubsectionManager_,
                      AudioFilePlayer* filePlayer_);
    ~SubsectionOverlay();
    
    void resized();
    void paint(Graphics &g);
    
    //====================================================================================
    /**@Internal@*/
    void subsectionCreated();
    /**@Internal@*/
    void subsectionDeleted();
    /**@Internal@*/
    void subsectionChanged(int SubsectionIndex);
    /**@Internal@*/
    void fileChanged (AudioFilePlayer* player);
    
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
    void mouseDrag (const MouseEvent& event);
    /**@Internal@*/
    void mouseUp (const MouseEvent& event);
    
private:
    int currentXScale;
    Image highlightImage;
    Image *SubsectionImage;
    AudioSubsectionManager &subsections;
    AudioFilePlayer *filePlayer;
};





#endif  // __SUBSECTIONOVERLAY_H_4F13024B__
