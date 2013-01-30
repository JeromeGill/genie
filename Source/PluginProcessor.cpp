/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
GenieAudioProcessor::GenieAudioProcessor()
{
    
    audioFormatManager = new AudioFormatManager();
    audioFormatManager->registerBasicFormats();
    audioFilePlayer = new AudioFilePlayer();
    audioFilePlayer->setAudioFormatManager(audioFormatManager, false);
    
    polyPlayer = new PolyAudioFilePlayer(*audioFilePlayer);
   
    
    mixerAudioSource.addInputSource(audioFilePlayer, false);
    mixerAudioSource.addInputSource(polyPlayer, false);
    
    subsectionManager = new AudioSubsectionManager(*audioFilePlayer);
    midiManager = new MidiManager(*polyPlayer, *subsectionManager, keyboardState);

}

GenieAudioProcessor::~GenieAudioProcessor()
{
    mixerAudioSource.removeAllInputs();
}

//==============================================================================
const String GenieAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int GenieAudioProcessor::getNumParameters()
{
    return 0;
}

float GenieAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void GenieAudioProcessor::setParameter (int index, float newValue)
{
}

const String GenieAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String GenieAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String GenieAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String GenieAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool GenieAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool GenieAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool GenieAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GenieAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GenieAudioProcessor::silenceInProducesSilenceOut() const{
    return false;
}

int GenieAudioProcessor::getNumPrograms()
{
    return 0;
}

int GenieAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GenieAudioProcessor::setCurrentProgram (int index)
{
}

const String GenieAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void GenieAudioProcessor::changeProgramName (int index, const String& newName)
{
}


//==============================================================================
void GenieAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    
    std::cout<<"samplerate : " <<sampleRate<<"\n";
    std::cout<<getNumOutputChannels()<<" outs \n";
    
    osc.initialiseOscillator (sampleRate, 220.0);                //Initialise Oscilator Object(s)
    
   
    mixerAudioSource.prepareToPlay(samplesPerBlock, sampleRate);
    
    
    
   //stream.createReaderFor (audioFilePlayer.getInputStream(),true); //Audiofile player is reading from a file not a stream??
    
   
}

void GenieAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    mixerAudioSource.releaseResources();
}

void GenieAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    
    float LchannelData;
    float RchannelData;
    
    const int numSamples = buffer.getNumSamples();
    
    //const float *pfInBuffer0;
    //const float *pfInBuffer1;
    
    AudioSourceChannelInfo channelInfo(buffer);
    
    mixerAudioSource.getNextAudioBlock(channelInfo);

    keyboardState.processNextMidiBuffer(midiMessages, 0, numSamples, true);
    
    
    
//    float *channel0 = buffer.getArrayOfChannels()[0]; //A pointer to the buffer for channel one
//    float *channel1 = buffer.getArrayOfChannels()[1]; //A pointer to the buffer for channel two

//    // This is the place where you'd normally do the guts of your plugin's
//    // audio processing...
//
//    
//    
//    //While the frames to process remain <0 do the following processing
//    while (numSamples --)
//    {
//        LchannelData = RchannelData = 0.f;
//        
//      //  *channel0 = LchannelData;
//        //*channel1 = RchannelData;
//        
//        //Move the pointer to next frame. Stride allows the possibilty of interlacing channels to a single buffer to speed things up if the project gets big
//       // channel0 += STRIDE;
//        //channel1 += STRIDE;
//    }
//    
//    // In case we have more outputs than inputs, we'll clear any output
//    // channels that didn't contain input data, (because these aren't
//    // guaranteed to be empty - they may contain garbage).
//    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
//    {
//       // buffer.clear (i, 0, buffer.getNumSamples());
//    }
//    
//    
    
}

//==============================================================================
bool GenieAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GenieAudioProcessor::createEditor()
{
    return new GenieAudioProcessorEditor (this, *audioFilePlayer, *subsectionManager);
}

//==============================================================================
void GenieAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GenieAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GenieAudioProcessor();
}
