//
//  audioFile.h
//  Genie
//
//  Created by Jerome on 12/10/2012.
//
//

#ifndef __audioFileLoader__
#define __audioFileLoader__

#include <iostream>
#include "genieHeader.h"


/**=====================================================================================================================
 audioFileLoader is a generic wav and aiff file load bar
 It contains an AudioFilePlayer object from the dRowAudio Module for JUCE to handle playback
 
 Functions
 
 Open File in finder
 Play
 Stop
 
 To Do

 Loop toggle
 Set BPM
======================================================================================================================*/

class AudioFileLoader  :  public  Component,
                    public  MenuBarModel,
                    public  FilenameComponentListener,
                    public  Button::Listener
{
public:
    AudioFileLoader (AudioFilePlayer &audioFilePlayer_);
    ~AudioFileLoader();
    
    /**@Internal@*/
    void paint (Graphics& g);
    /**@Internal@*/
    void resized ();
    

    /**Internal@*/
    void filenameComponentChanged (FilenameComponent* filenameComponent);
    
    /**Internal@ */
    void buttonClicked (Button* button);
    
    enum Buttons
    {
        play,
        stop,
        numButtons
    };
    
    //MenuBarEnums/Callbacks========================================================
    enum Menus
	{
		FileMenu=0,
		
		NumMenus
	};
    
    enum FileMenuItems
	{
        AudioPrefs = 1,
		
		NumFileItems
	};
    StringArray getMenuBarNames();
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName);
	void menuItemSelected (int menuItemID, int topLevelMenuIndex);
    
private:
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioFileLoader);
    
    
    //FileLoader and browser
    ScopedPointer<FilenameComponent> fileChooser;
    OwnedArray<TextButton> buttons;
    AudioFilePlayer &audioFilePlayer;
  
    
    
};




#endif /* defined(__Genie__audioFile__) */
