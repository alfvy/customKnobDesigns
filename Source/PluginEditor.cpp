/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

Spin::Spin(KnobDesignAudioProcessor& p) : audioProcessor(p)
{
  startTimerHz(60);
}

Spin::~Spin()
{
  stopTimer();
}

void Spin::timerCallback()
{
  rotation += speed;
  repaint();
}

void Spin::paint(juce::Graphics& g)
{
  g.fillPath(path);
}

void Spin::resized()
{
  path.addRoundedRectangle(100, 100, 60, 60, 6.0f);
}

//==============================================================================
KnobDesignAudioProcessorEditor::KnobDesignAudioProcessorEditor (KnobDesignAudioProcessor& p)
  : AudioProcessorEditor (&p), audioProcessor (p), spin(audioProcessor)
{
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize (400, 300);
}

KnobDesignAudioProcessorEditor::~KnobDesignAudioProcessorEditor()
{
}

//==============================================================================
void KnobDesignAudioProcessorEditor::paint (juce::Graphics& g)
{
  // (Our component is opaque, so we must completely fill the background with a solid colour)
  g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

  g.setColour (juce::Colours::white);
  g.setFont (15.0f);
  g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void KnobDesignAudioProcessorEditor::resized()
{
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
}
