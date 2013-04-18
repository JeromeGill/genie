//
//  audioFile.cpp
//  Genie
//
//  Created by Jerome on 12/10/2012.
//
//

/**
//=======================================================================================================================

//======================================================================================================================= 
*/

 
#include "audioFile.h"

AudioFile::AudioFile (AudioFilePlayer &audioFilePlayer_)
: audioFilePlayer(audioFilePlayer_)
{    
    
    
    
    //fileChooser setup
    
    //formatManager = audioFilePlayer->getAudioFormatManager();

    
    fileChooser = new FilenameComponent ("AudioFile",
                                         File::nonexistent,
                                         true, false, false,
                                         audioFilePlayer.getAudioFormatManager()->getWildcardForAllFormats(),
                                         String::empty,
                                         "(choose an audio file)");
    
  
    
    addAndMakeVisible (fileChooser);
    fileChooser->addListener (this);
    fileChooser->setBrowseButtonText ("...");
    
    
    for (int i = 0; i < numButtons; i++)
    {
        buttons.add (new TextButton());
        addAndMakeVisible (buttons[i]);
        buttons[i]->addListener (this);
    }
    
    buttons[play]->setButtonText ("Preview");
    buttons[stop]->setButtonText ("Stop");
    
    
        
}
AudioFile::~AudioFile()
{
    fileChooser->removeListener(this);
    
    for (int i = 0; i < numButtons; i++)
    {
        buttons[i]->removeListener (this);
    }
}

//ComponentCallbacks============================================================

void AudioFile::resized()
{
    int w = getWidth();
    int h = getHeight();

    fileChooser->setBounds(0, 0, w/2, h);
    for (int i = 0; i < numButtons; i++)
    {
           buttons[i]->setBounds ((w / numButtons * i / 2) + w/2, 0, w / numButtons / 2, h);
        }
   
}


void AudioFile::paint (Graphics& g)
{


}

//FilenameComponent Callback=====================================================

void AudioFile::filenameComponentChanged (FilenameComponent* filenameComponent)
{
    audioFilePlayer.setFile(filenameComponent->getCurrentFile());
    
}

//Button Callbacks
void AudioFile::buttonClicked (Button* button)
{
    if (button == buttons[play])
    {
        audioFilePlayer.start();
        std::cout<<"Playing\n";
        buttons[stop]->setButtonText("stop");
    }
    else if (button == buttons[stop])
    {
        if (audioFilePlayer.isPlaying()) {
        audioFilePlayer.stop();
        std::cout<<"Stop\n";
            buttons[stop]->setButtonText("reset");
        }
        else{
            audioFilePlayer.setNextReadPosition(0);
        }
    }
}

//MenuBarCallbacks==============================================================
StringArray AudioFile::getMenuBarNames()
{
	const char* const names[] = { "File", 0 };
	return StringArray (names);
}

PopupMenu AudioFile::getMenuForIndex (int topLevelMenuIndex, const String& menuName)
{
	PopupMenu menu;
    if (topLevelMenuIndex == 0)
        menu.addItem(AudioPrefs, "Audio Prefrences", true, false);
	return menu;
}

void AudioFile::menuItemSelected (int menuItemID, int topLevelMenuIndex)
{
//	if (topLevelMenuIndex == FileMenu)
//    {
//          if (menuItemID == AudioPrefs)
//          {
//              AudioDeviceSelectorComponent audioSettingsComp (audioDeviceManager,
//                                                              0, 2, 2, 2,
//                                                              true, true, true, true);
//              audioSettingsComp.setSize (500, 250);
//              DialogWindow::showModalDialog ("Audio Settings", &audioSettingsComp, this, Colours::azure, true);
//        }
//    }
}

