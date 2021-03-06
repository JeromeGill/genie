/*
  ==============================================================================
  
  This file is part of the dRowAudio JUCE module
  Copyright 2004-12 by dRowAudio.
  
  ------------------------------------------------------------------------------
 
  dRowAudio can be redistributed and/or modified under the terms of the GNU General
  Public License (Version 2), as published by the Free Software Foundation.
  A copy of the license is included in the module distribution, or can be found
  online at www.gnu.org/licenses.
  
  dRowAudio is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
  
  ==============================================================================
*/

PitchDetector::PitchDetector()
    : detectionMethod (autoCorrelationFunction),
      sampleRate (44100.0),
      minFrequency (50), maxFrequency (1600),
      buffer1 (512), buffer2 (512),
      numSamplesNeededForDetection (int ((sampleRate / minFrequency) * 2)),
      currentBlockBuffer (numSamplesNeededForDetection),
      inputFifoBuffer (numSamplesNeededForDetection * 2),
      mostRecentPitch (0.0)
{
}

PitchDetector::~PitchDetector()
{
}

void PitchDetector::setDetectionMethod (DetectionMethod newMethod)
{
    detectionMethod = newMethod;
}

void PitchDetector::processSamples (const float* samples, int numSamples) noexcept
{
    if (inputFifoBuffer.getNumFree() < numSamples)
        inputFifoBuffer.setSizeKeepingExisting (inputFifoBuffer.getSize() * 2);
    
    inputFifoBuffer.writeSamples (samples, numSamples);
    
    while (inputFifoBuffer.getNumAvailable() >= numSamplesNeededForDetection)
    {
        inputFifoBuffer.readSamples (currentBlockBuffer.getData(), currentBlockBuffer.getSize());
        mostRecentPitch = detectPitchForBlock (currentBlockBuffer.getData(), currentBlockBuffer.getSize());
    }
}

double PitchDetector::detectPitch (float* samples, int numSamples) noexcept
{
    Array<double> pitches;
    pitches.ensureStorageAllocated (int (numSamples / numSamplesNeededForDetection));
    
    while (numSamples >= numSamplesNeededForDetection)
    {
        double pitch = detectPitchForBlock (samples, numSamplesNeededForDetection);//0.0;
        
        if (pitch > 0.0)
            pitches.add (pitch);
        
        numSamples -= numSamplesNeededForDetection;
        samples += numSamplesNeededForDetection;
    }
    
    if (pitches.size() == 1)
    {
        return pitches[0];
    }
    else if (pitches.size() > 1)
    {
        DefaultElementComparator<double> sorter;
        pitches.sort (sorter);
        
        const double stdDev = findStandardDeviation (pitches.getRawDataPointer(), pitches.size());
        const double medianSample = findMedian (pitches.getRawDataPointer(), pitches.size());
        const double lowerLimit = medianSample - stdDev;
        const double upperLimit = medianSample + stdDev;
        
        Array<double> correctedPitches;
        correctedPitches.ensureStorageAllocated (pitches.size());
        
        for (int i = 0; i < pitches.size(); ++i)
        {
            const double pitch = pitches.getUnchecked (i);
            
            if (pitch >= lowerLimit && pitch <= upperLimit)
                correctedPitches.add (pitch);
        }
        
        const double finalPitch = findMean (correctedPitches.getRawDataPointer(), correctedPitches.size());
        
        return finalPitch;
    }
    
    return 0.0;
}

void PitchDetector::setMinMaxFrequency (float newMinFrequency, float newMaxFrequency) noexcept
{
    minFrequency = newMinFrequency;
    maxFrequency = newMaxFrequency;
    
    lowFilter.makeLowPass (sampleRate, maxFrequency);
    highFilter.makeHighPass (sampleRate, minFrequency);

    numSamplesNeededForDetection = int (sampleRate / minFrequency) * 2;

    inputFifoBuffer.setSizeKeepingExisting (numSamplesNeededForDetection * 2);
    currentBlockBuffer.setSize (numSamplesNeededForDetection);

    buffer1.setSizeQuick (numSamplesNeededForDetection);
    buffer2.setSizeQuick (numSamplesNeededForDetection);
}

//==============================================================================
Buffer* PitchDetector::getBuffer (int stageIndex)
{
    switch (stageIndex)
    {
        case 1:     return &buffer1; break;
        case 2:     return &buffer2; break;
        default:    return nullptr;
    }
    
    return nullptr;
}

double PitchDetector::detectPitchForBlock (float* samples, int numSamples)
{
    switch (detectionMethod)
    {
        case autoCorrelationFunction:
            return detectAcfPitchForBlock (samples, numSamples);
            break;
        case squareDifferenceFunction:
            return detectSdfPitchForBlock (samples, numSamples);
            break;
        default:
            return 0.0;
            break;
    }
}

double PitchDetector::detectAcfPitchForBlock (float* samples, int numSamples)
{
    const int minSample = int (sampleRate / maxFrequency);
    const int maxSample = int (sampleRate / minFrequency);

    lowFilter.reset();
    highFilter.reset();
    lowFilter.processSamples (samples, numSamples);
    highFilter.processSamples (samples, numSamples);
    
    autocorrelate (samples, numSamples, buffer1.getData());
    normalise (buffer1.getData(), buffer1.getSize());

//    float max = 0.0f;
//    int sampleIndex = 0;
//    for (int i = minSample; i < maxSample; ++i)
//    {
//        const float sample = buffer1.getData()[i];
//        if (sample > max)
//        {
//            max = sample;
//            sampleIndex = i;
//        }
//    }

    float* bufferData = buffer1.getData();
//    const int bufferSize = buffer1.getSize();
    int firstNegativeZero = 0;
    
    // first peak method
    for (int i = 0; i < numSamples - 1; ++i)
    {
        if (bufferData[i] >= 0.0f && bufferData[i + 1] < 0.0f)
        {
            firstNegativeZero = i;
            break;
        }
    }
    
    // apply gain ramp
//    float rampDelta = 1.0f / numSamples;
//    float rampLevel = 1.0f;
//    for (int i = 0; i < numSamples - 1; ++i)
//    {
//        bufferData[i] *= cubeNumber (rampLevel);
//        rampLevel -= rampDelta;
//    }
    
    float max = -1.0f;
    int sampleIndex = 0;
    for (int i = jmax (firstNegativeZero, minSample); i < maxSample; ++i)
    {
        if (bufferData[i] > max)
        {
            max = bufferData[i];
            sampleIndex = i;
        }
    }
    
    
//    buffer2.setSizeQuick (numSamples);
/*    autocorrelate (buffer1.getData(), buffer1.getSize(), buffer2.getData());
    normalise (buffer2.getData(), buffer2.getSize());*/
    //buffer2.quickCopy (buffer1.getData(), buffer1.getSize());
//    differentiate (buffer1.getData(), buffer1.getSize(), buffer2.getData());
//    normalise (buffer2.getData()+2, buffer2.getSize()-2);
//    differentiate (buffer2.getData(), buffer2.getSize(), buffer2.getData());
    
/*    for (int i = minSample + 1; i < maxSample - 1; ++i)
    {
        const float previousSample = buffer2.getData()[i - 1];
        const float sample = buffer2.getData()[i];
        const float nextSample = buffer2.getData()[i + 1];

        if (sample > previousSample
            && sample > nextSample
            && sample > 0.5f)
            sampleIndex = i;
    }*/
    
    //differentiate (buffer2.getData(), buffer2.getSize(), buffer2.getData());
    //normalise (buffer2.getData() + minSample, buffer2.getSize() - minSample);
    
//    float min = 0.0f;
//    int sampleIndex = 0;
//    for (int i = minSample; i < maxSample; ++i)
//    {
//        const float sample = buffer2.getData()[i];
//        if (sample < min)
//        {
//            min = sample;
//            sampleIndex = i;
//        }
//    }


    if (sampleIndex > 0)
        return sampleRate / sampleIndex;
    else
        return 0.0;
}

double PitchDetector::detectSdfPitchForBlock (float* samples, int numSamples)
{
    const int minSample = int (sampleRate / maxFrequency);
    const int maxSample = int (sampleRate / minFrequency);
    
    lowFilter.reset();
    highFilter.reset();
    lowFilter.processSamples (samples, numSamples);
    highFilter.processSamples (samples, numSamples);
    
    sdfAutocorrelate (samples, numSamples, buffer1.getData());
    normalise (buffer1.getData(), buffer1.getSize());
    
    // find first minimum that is below a threshold
    const float threshold = 0.25f;
    const float* sdfData = buffer1.getData();
    float min = 1.0f;
    int index = 0;
    
    for (int i = minSample; i < maxSample; ++i)
    {
        const float prevSample = sdfData[i - 1];
        const float sample =  sdfData[i];
        const float nextSample =  sdfData[i + 1];
        
        if (sample < prevSample
            && sample < nextSample
            && sample < threshold)
        {
            if (sample < min)
            {
                min = sample;
                index = i;
            }
//            return sampleRate / i;
//            break;
        }
    }
    
    if (index != 0)
        return sampleRate / index;
    
    return 0.0;
}
