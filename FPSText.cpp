#include "FPSText.h"
#include <sstream>

FPSText::FPSText(int sampleSize)
	: m_fps(0), m_sampleSize(sampleSize)
{
	m_font.loadFromFile("arial.ttf");

	m_fpsText.setFont(m_font);
	m_fpsText.setCharacterSize(20);
	m_fpsText.setFillColor(sf::Color::Red);
	setText();
}

void FPSText::nextFrame()
{
	m_updates.push_front(m_clock.getElapsedTime());

	if (m_updates.size() >= m_sampleSize)
		m_updates.resize(m_sampleSize);

	if (m_updates.size() > 1) {
		m_fps = m_updates.size() / (m_updates.front() - m_updates.back()).asSeconds();
		setText();
	}
}

void FPSText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_fpsText, states);
}

void FPSText::setText()
{
	std::stringstream ss;
	ss << round(m_fps);
	std::string fpsString;
	ss >> fpsString;
	m_fpsText.setString(fpsString);
}
