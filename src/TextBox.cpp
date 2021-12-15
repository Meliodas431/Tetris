#include "TextBox.h"
#include "settings.h"

TextBox::TextBox() {}

TextBox::TextBox(const uint16_t& size, const sf::Color& color) {
	setSettings(size, color);
}

void TextBox::setSettings(const uint16_t& size, const sf::Color& color) {
	m_font.loadFromFile(font);
	m_text.setFont(m_font);
	m_text.setCharacterSize(size);
	m_text.setFillColor(color);
}

void TextBox::addText(const std::string& text, const sf::Vector2f& position) {
	m_text.setString(text);
	m_text.setPosition(position);
	m_vecText.push_back(m_text);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	for (const auto& element: m_vecText)
		target.draw(element);
}