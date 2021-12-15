#include "Menu.h"
#include "settings.h"
#include "TextBox.h"
#include "Application.h"
#include <fstream>
#include <iostream>

Menu::Menu() {
	m_tBackground.loadFromFile(background);
	m_sBackground.setTexture(m_tBackground);
	m_sBackground.setTextureRect({ 467, 0, 468, 630});

	m_font.loadFromFile(font);
	m_newGame.setFont(m_font);
	m_newGame.setString("New Game");
	m_newGame.setCharacterSize(55);
	m_newGame.setPosition({ 95.f, 180.f });
	m_newGame.setFillColor(sf::Color::Black);

	m_bestScore = m_newGame;
	m_bestScore.setString("Best Score");
	m_bestScore.setPosition({ 95.f, 280.f });

	m_lable = m_newGame;
	m_lable.setString("TETRIS");
	m_lable.setCharacterSize(84);
	m_lable.setPosition({ 75.f, 0.f });

	std::ifstream in(data);
	if (in.is_open()) {
		in >> m_score;
		in >> m_lvl;
		in >> m_lines;
	}
	in.close();
}

Menu::~Menu() {}

void Menu::drawMenu() {
	Application::window->draw(m_sBackground);
	bool NewGameP  = buttonPressed(m_newGame);
	bool BestScore = buttonPressed(m_bestScore);
	if (NewGameP) {
		Application::state = Application::GameState::BEGIN_GAME;
	}
	else if (BestScore) {
		Application::state = Application::GameState::MENU_BEST_SCORE;
	}

	Application::window->draw(m_lable);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates state) const {	
	target.draw(m_sBackground);
	target.draw(m_newGame);
	target.draw(m_bestScore);
	target.draw(m_lable);
}

bool Menu::buttonPressed(sf::Text& text) {
	Application::window->draw(text);
	auto bounds = text.getGlobalBounds();
	auto mouseCoords = Application::window->mapPixelToCoords(sf::Mouse::getPosition(*Application::window));

	bool contains = bounds.contains(mouseCoords);
	if (contains && pressed) {
		pressed = false;
		return true;
	}
	if (contains) {
		text.setFillColor(sf::Color::Red);
	}
	else {
		text.setFillColor(sf::Color::Black);
	}

	return false;
}

void Menu::drawMenuBestScore() {
	Application::window->draw(m_sBackground);

	TextBox bestScore(36, sf::Color::White);
	bestScore.addText("Best Score", {130.f, 150.f});
	bestScore.addText(m_score, { 180.f, 200.f });
	bestScore.addText(m_lvl, { 180.f, 250.f });
	bestScore.addText(m_lines, { 180.f, 300.f });

	Application::window->draw(bestScore);
}