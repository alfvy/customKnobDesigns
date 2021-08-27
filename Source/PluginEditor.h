/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

struct Spin : public juce::Component, public juce::Timer
{
  double rotation = {0.};
  double speed = 3.141592741F / 4;

  Spin(KnobDesignAudioProcessor&);
  ~Spin();

  void timerCallback() override;
  void paint(juce::Graphics&) override;
  void resized() override;

  juce::Path path;

  KnobDesignAudioProcessor& audioProcessor;

};

//==============================================================================
class KnobDesignAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    KnobDesignAudioProcessorEditor (KnobDesignAudioProcessor&);
    ~KnobDesignAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Spin spin;

    juce::Slider testSlider;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KnobDesignAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobDesignAudioProcessorEditor)
};