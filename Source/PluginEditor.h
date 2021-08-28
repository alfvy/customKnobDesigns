/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

const float startAngle = juce::degreesToRadians(180.0f + 45.0f);
const float endAngle = juce::degreesToRadians(180.f - 45.0f) + juce::MathConstants<float>::twoPi;

struct Spin : public juce::Component, public juce::Timer
{
    double rotation = {0.};
    double speed = 3.141592741F / 4;

    Spin(KnobDesignAudioProcessor&);
    ~Spin();

    void timerCallback() override;
    void paint(juce::Graphics&) override;
    void resized() override;
    //void sliderValueChanged(juce::Slider&) override;

    juce::Path path;

    KnobDesignAudioProcessor& audioProcessor;

    juce::Rectangle<float> bounds = {100, 100, 150, 150};
};

struct LookAndFeel : juce::LookAndFeel_V4
{
    static void drawRotarySlider(juce::Graphics& g, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider);
    static juce::String getDisplayString(juce::Slider& slider);
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
    juce::Slider testSlider;

private:
    Spin spin;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KnobDesignAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobDesignAudioProcessorEditor)
};