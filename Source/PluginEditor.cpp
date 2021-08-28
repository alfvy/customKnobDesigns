/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

Spin::Spin(KnobDesignAudioProcessor& p) : audioProcessor(p)
{
    startTimerHz(30);
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
    g.setColour(juce::Colours::white);

    path.addRoundedRectangle(bounds.reduced(40.0f), 6.0f);

    auto transform = juce::AffineTransform().rotated(juce::degreesToRadians(rotation * 10.0f),
        bounds.reduced(60.0f).getCentreX(), bounds.reduced(60.0f).getCentreY());

    auto strokeType = juce::PathStrokeType(1.0f);

    path.applyTransform(transform);

    g.fillPath(path);
    path.clear();
}

void Spin::resized()
{
    //path.addRoundedRectangle(audioProcessor.activeEditor.getBounds().reduced(60.0f), 6.0f);
}

juce::Rectangle<int> getSliderBounds(juce::Slider& slider)
{
    //return getLocalBounds();

    auto bounds = slider.getLocalBounds();

    auto size = juce::jmin(bounds.getWidth(), bounds.getHeight());

    size -= 14 * 2;

    juce::Rectangle<int> r;

    r.setSize(size, size);
    r.setCentre(bounds.getCentreX(), 0);
    r.setY(2);

    return r;
}

juce::String LookAndFeel::getDisplayString(juce::Slider& slider)
{
    juce::String str;
    bool addK = false;

    float val = slider.getValue();

    if (val > 999.9f)
    {
        val /= 1000.0f;
        addK = true;
    }


    str = juce::String(val, (addK ? 2 : 0));

    if (addK)
    {
        str << "k";
    }

    return str;
}

//function for drawing the custom rotary sliders
void LookAndFeel::drawRotarySlider(juce::Graphics& g, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    slider.setAlpha(0.0f);
    juce::Range<double> bruh = { 0, 6 };

    bool isDistTypeSlider = slider.getRange() == bruh;

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);

    auto x = slider.getX();
    auto y = slider.getY();
    auto width = slider.getWidth();
    auto height = slider.getHeight();

    auto bounds = juce::Rectangle<float>(x, y, width, height);

    g.setColour(juce::Colour(71u, 91u, 202u));
    g.fillEllipse(bounds);

    g.setColour(juce::Colour(230u, 217u, 200u));
    g.drawEllipse(bounds, 1.f);

    if (auto* rswl = dynamic_cast<juce::Slider*>(&slider))
    {
        auto center = bounds.getCentre();

        juce::Path p;

        juce::Rectangle<float> r;

        r.setLeft(center.getX() - 2);
        r.setRight(center.getX() + 2);
        r.setTop(bounds.getY() + 5);
        r.setBottom(center.getY());// -testSlider.getTextBoxHeight() * 1.25f);
        r.setSize(10, 10);

        p.addEllipse(r);

        float sliderPosProportional = juce::jmap(slider.getValue(), slider.getRange().getStart(), slider.getRange().getEnd(), 0.0, 1.0);



        jassert(startAngle < endAngle);

        auto sliderAngleRad = juce::jmap(sliderPosProportional, 0.0f, 1.0f, startAngle, endAngle);

        p.applyTransform(juce::AffineTransform().rotated(sliderAngleRad, center.getX(), center.getY()));

        g.fillPath(p);

        g.setFont(14);

        auto text = getDisplayString(slider);
        auto strWidth = g.getCurrentFont().getStringWidth(text);

        juce::Point<float> offset = { 0.0f, 20.0f };

        r.setSize(100, 14 + 2);
        r.setCentre(bounds.getCentre() + offset);


        g.setColour(juce::Colours::white);
        g.drawFittedText(text, r.toNearestInt(), juce::Justification::centred, 1);
    }
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

    addAndMakeVisible(testSlider);
    LookAndFeel::drawRotarySlider(g, startAngle, endAngle, testSlider);
}

void KnobDesignAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    spin.setBounds(getBounds());
    addAndMakeVisible(spin);

    testSlider.setBounds(100, 100, 150, 150);
}
