#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

class FPSText : public sf::Drawable, public sf::Transformable
{
	int m_sampleSize;
	sf::Clock m_clock;
	std::deque<sf::Time> m_updates;
	
	double m_fps;

	sf::Font m_font;
	sf::Text m_fpsText;

public:
	FPSText(int sampleSize = 50);

	void nextFrame();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void setText();
};

