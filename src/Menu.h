#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <sstream>

class Menu : public sf::Drawable {
public:
	bool pressed = false;
private:
	sf::Texture m_tBackground;
	sf::Sprite m_sBackground;
	sf::Font m_font;
	sf::Text m_newGame, m_bestScore, m_lable;
	std::string m_score;
	std::string m_lvl;
	std::string m_lines;
	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
public:	
	Menu();
	~Menu();
	void drawMenu();
	void drawMenuBestScore();
	bool buttonPressed(sf::Text& text);
}; 

#endif // !MENU_H