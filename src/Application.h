#ifndef APPLICATION_H
#define APPLICATION_H
#include <SFML/Graphics.hpp>
#include "game.h"
#include "Menu.h"
#include <array>

class Application {
private:	
	sf::Texture m_tBackground;
	sf::Sprite m_sBackground;
	Menu* menu;
	Game* game;

public:	
	static sf::RenderWindow* window;
	enum class GameState {
		END_GAME = -1, BEGIN_GAME = 0, GAME = 1, MENU = 2,
		MENU_BEST_SCORE = 3, PAUSE = 4
	};
	static GameState state;
	
public:
	Application(sf::RenderWindow* wnd, Menu* _menu, Game* _game);
	~Application();
	void drawGame();
	sf::RenderWindow* getWindow();
	friend class Game;
	friend class Tetramino;
};

#endif // !APPLICATION_H