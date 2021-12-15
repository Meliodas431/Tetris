#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Settings.h"
#include "Time.h"
#include "Game.h"
#include "Menu.h"
#include "Application.h"
Point point[4], temp[4], next[4], hold[4], p;
uint16_t field[FIELD_HEIGHT][FIELD_WIDTH]{0};

int main() {
	Menu menu;
	Game game;
	Timer timer;

	sf::RenderWindow window(sf::VideoMode(467, 630), "Tetris", sf::Style::Close);

	Application app(&window, &menu, &game);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) 
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if(event.mouseButton.button == sf::Mouse::Left) {
					menu.pressed = true;
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up) {
					game.rotate();
				}
				else if (event.key.code == sf::Keyboard::Enter) {
					if (game.m_holdReady) {
						game.holdTetramino();
					}
				}
				else if (event.key.code == sf::Keyboard::P) {
					app.state = Application::GameState::PAUSE;
	
				}
				else if (event.key.code == sf::Keyboard::Left) { 
					game.moveByX(-1);					
				}
				else if (event.key.code == sf::Keyboard::Right) { 
					game.moveByX(1);
				}
			}
		}	
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			Timer::get()->m_delay = 0.05f;

		window.clear();

		switch (app.state) {
		case Application::GameState::MENU:
			menu.drawMenu();
			break;
		case Application::GameState::MENU_BEST_SCORE:
			menu.drawMenuBestScore();
			break;
		case Application::GameState::BEGIN_GAME:
			app.drawGame();
			break;
		default:
			app.drawGame();
			break;
		}
		window.display();
	}
	return 0;
}