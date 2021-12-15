#include "Application.h"
#include "TextBox.h"
#include <functional>

Application::GameState Application::state = GameState::MENU;
sf::RenderWindow* Application::window = nullptr;

Application::Application(sf::RenderWindow* wnd, Menu* _menu, Game* _game) {
	window = wnd;
	menu = _menu;
	game = _game;

	m_tBackground.loadFromFile(background);
	m_sBackground.setTexture(m_tBackground);
	m_sBackground.setTextureRect({ 0, 0, 467, 630 });
}

Application::~Application() {}

sf::RenderWindow* Application::getWindow() {
	return window;
}

void Application::drawGame() {
	TextBox Text(18, sf::Color::White);

	if (state == GameState::BEGIN_GAME) {
		game->setNewTetramino();
		state = GameState::GAME;
	}

	game->moveByY();
	game->checkFullLine();

	Timer::get()->m_delay = game->delay[game->m_currentlvl];

	game->toDraw.clear();

	Text.addText("Next", { 395.f, 15.f });
	Text.addText("Hold", { 37.f, 15.f });
	Text.addText("Score", { 200.f, 500.f });
	Text.addText("Lines", { 200.f, 530.f });
	Text.addText("lvl", { 110.f, 500.f });
	Text.addText(std::to_string(game->m_score), { 280.f, 500.f });
	Text.addText(std::to_string(game->m_currentlvl + 1), { 140.f, 500.f });
	Text.addText(std::to_string(game->m_totallines), { 280.f, 530.f });
	if (!game->m_holdReady) {
		auto holdTimer = Timer::get()->printTimer();
		game->m_holdReady = holdTimer.first;
		Text.addText("00:" + std::to_string(holdTimer.second), { 30.f, 170.f });
	}

	window->draw(m_sBackground);

	game->drawFallenTiles();
	game->drawNextTetramino();
	game->drawHoldTetramino();
	window->draw(Text);
	window->draw(*game);
}

