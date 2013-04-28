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


//==============================================================================
/**AudioFileLoader
 \brief AudioFileLoader is a file browser and loader for a [drow::AudioFilePlayer]
 
 It also features preview buttons.
 
 [drow::AudioFilePlayer]: http://drowaudio.co.uk/docs/class_audio_file_player.html (drow:AudioFilePlayer)
 *///==============================================================================

class AudioFileLoader  :  public  Component,
                    public  MenuBarModel,
                    public  FilenameComponentListener,
                    public  Button::Listener
{
public:
    AudioFileLoader (drow::AudioFilePlayer &audioFilePlayer_);
    ~AudioFileLoader();
    
    /** @internal */
    void paint (Graphics& g);
    /** @internal */
    void resized ();
    

    /** @internal */
    void filenameComponentChanged (FilenameComponent* filenameComponent);
    
    /** @internal */
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
    drow::AudioFilePlayer &audioFilePlayer;
  
    
    
};




#endif /* defined(__Genie__audioFile__) */
