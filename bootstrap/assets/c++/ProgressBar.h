#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>

class ProgressBar : public sf::Drawable, public sf::Transformable
{
public:
	ProgressBar(uint32_t currentValue, uint32_t maxValue, uint32_t width, uint32_t height);

	void setCurrentValue(uint32_t value);
	void setMaxValue(uint32_t maxValue);
	void setWidth(uint32_t width);
	void setHeight(uint32_t height);
	void setBackgroundColor(sf::Color color);
	void setForegroundColor(sf::Color color);

	uint32_t getCurrentValue() const;
	uint32_t getMaxValue() const;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	sf::Color getBackgroundColor() const;
	sf::Color getForegroundColor() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	uint32_t m_currentValue, m_maxValue, m_width, m_height;
	sf::Color m_backgroundColor, m_foregroundColor;
};

