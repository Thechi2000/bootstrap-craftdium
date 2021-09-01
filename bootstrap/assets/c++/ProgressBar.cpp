#include "ProgressBar.h"
#include <iostream>
using namespace sf;

ProgressBar::ProgressBar(uint32_t currentValue, uint32_t maxValue, uint32_t width, uint32_t height) :
	m_currentValue(currentValue),
	m_maxValue(maxValue),
	m_width(width),
	m_height(height)
	//m_backgroundColor(Color::Blue),
	//m_foregroundColor(Color::Red)
{
	setBackgroundColor(Color::Blue);
	setForegroundColor(Color::Red);
}

void ProgressBar::setCurrentValue(uint32_t value)
{
	m_currentValue = (value > m_maxValue ? m_maxValue : value);
}
void ProgressBar::setMaxValue(uint32_t maxValue)
{
	m_maxValue = maxValue;
}
void ProgressBar::setWidth(uint32_t width)
{
	m_width = width;
}
void ProgressBar::setHeight(uint32_t height)
{
	m_height = height;
}
void ProgressBar::setBackgroundColor(sf::Color color)
{
	m_backgroundColor = color;
}
void ProgressBar::setForegroundColor(sf::Color color)
{
	m_foregroundColor = color;
}

uint32_t ProgressBar::getCurrentValue() const
{
	return m_currentValue;
}
uint32_t ProgressBar::getMaxValue() const
{
	return m_maxValue;
}
uint32_t ProgressBar::getWidth() const
{
	return m_width;
}
uint32_t ProgressBar::getHeight() const
{
	return m_height;
}
sf::Color ProgressBar::getBackgroundColor() const
{
	return m_backgroundColor;
}
sf::Color ProgressBar::getForegroundColor() const
{
	return m_foregroundColor;
}

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	FloatRect backgroundRect(0, 0, m_width, m_height);
	backgroundRect = states.transform.transformRect(backgroundRect);
	RectangleShape background({ backgroundRect.width, backgroundRect.height });
	background.setPosition(backgroundRect.left, backgroundRect.top);
	background.setFillColor(m_backgroundColor);

	FloatRect foregroundRect(0, 0, m_width * (((float)m_currentValue) / m_maxValue), m_height);
	foregroundRect = states.transform.transformRect(foregroundRect);
	RectangleShape foreground({ foregroundRect.width, foregroundRect.height });
	foreground.setPosition(foregroundRect.left, foregroundRect.top);
	foreground.setFillColor(m_foregroundColor);

	target.draw(background);
	target.draw(foreground);
}
