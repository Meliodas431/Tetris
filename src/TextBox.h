#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <string>

class TextBox : public sf::Drawable {
private:
	sf::Text m_text;
	sf::Font m_font;
	uint16_t m_size = 0;
	sf::Color m_color;
	std::vector<sf::Text> m_vecText;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
public:
	TextBox();
	TextBox(const uint16_t& size, const sf::Color& color);
	void setSettings(const uint16_t& size, const sf::Color& color);
	void addText(const std::string& text, const sf::Vector2f& position);
};

#endif // !TEXTBOX_H