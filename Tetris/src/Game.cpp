#include <random>
#include <fstream>
#include "Game.h"
#include "Application.h"
#include <iostream>
extern Point point[4], temp[4], next[4], hold[4], p;
const uint16_t startPosition{ 6 };

std::array<float, 20> Game::multiplier{ 0.0f, 0.1f, 0.2f ,0.3f ,0.4f ,0.5f ,0.6f ,0.7f ,0.8f ,0.9f ,1.0f ,1.1f ,1.2f ,1.3f ,1.4f ,1.5f, 1.6f, 1.7f, 1.8f };
std::array<float, 20> Game::delay{ 0.4f, 0.35f, 0.3f, 0.25f, 0.2f ,0.15f ,0.1f ,0.05f ,0.04f ,0.045f, 0.03f, 0.025f, 0.02f, 0.015f, 0.01f, 0.009f, 0.008f, 0.007f, 0.006f , 0.005f };
std::array<uint16_t, 20> Game::lines{ 5, 10, 15, 21, 27, 34, 41, 49, 57, 66, 75, 84, 94, 104, 114, 125, 136, 147, 160 };

uint32_t rd(const uint32_t& min, const uint32_t& max) {
	std::random_device r;
	std::mt19937 gen(r());
	std::uniform_int_distribution<> uid(min, max);
	return uid(gen);
}

Game::Game() {
	m_tTile.loadFromFile(tiles);
	m_sTile.setTexture(m_tTile);
	m_sTile.setTextureRect({ 0, 0, sizeTile, sizeTile });
}

Game::~Game() {
	uint32_t score { 0 };
	std::ifstream in(data);
	if (in.is_open()) {
		in >> score;
	}
	in.close();

	if (score < m_score) {
		std::ofstream out(data, std::ios::out);
		if (out.is_open()) {
			out << m_score << '\n';
			out << m_currentlvl << '\n';
			out << m_totallines << '\n';
		}
		out.close();
	}
}

void Game::setNewTetramino() {
	bool begin = Application::state == Application::GameState::BEGIN_GAME;
	if (begin) {
		t_tetraminoColor = rd(1, 6);
		t_tetramino      = rd(0, 6);
		Application::state = Application::GameState::GAME;
	}
	else {
	    t_tetraminoColor = t_NextColor;
	    t_tetramino      = t_Next;
	}

	t_Next      = rd(0, 6);
	t_NextColor = rd(1, 6);

	for (uint16_t i{0}; i < 4; ++i) {
		point[i].x = startPosition + figure[t_tetramino][i] % 2;
		point[i].y = figure[t_tetramino][i] / 2 ; 
	}	

	bool endSpace = !Game::checkUpY();
	if (endSpace) {
		Application::state == Application::GameState::END_GAME;
	}
}

void Game::holdTetramino() {
	if (m_holdEmpty) {
		t_holdTetramino  = t_tetramino;
		t_holdColor      = t_tetraminoColor;
		Game::setNewTetramino();
		m_holdEmpty = false;
	}
	else {
		t_tetramino = t_holdTetramino;
		t_tetraminoColor = t_holdColor;
		m_holdReady = false;
		m_holdEmpty = true;

		for (uint16_t i{ 0 }; i < 4; ++i) {
			point[i].x = startPosition + figure[t_tetramino][i] % 2;
			point[i].y = figure[t_tetramino][i] / 2;
		}
	}	
}

void Game::moveByX(const short& move) {
	for (uint16_t i{ 0 }; i < 4; ++i) {
		temp[i] = point[i];  
		point[i].x += move;
	}

	if (!Game::checkFieldSides()) {
		for (uint16_t i{ 0 }; i < 4; ++i)
			point[i] = temp[i];
	}
}

void Game::moveByY() {
	auto time  = Timer::get()->stop();
	auto delay = Timer::get()->m_delay;
	if (time > delay) {
		for (uint16_t i{ 0 }; i < 4; ++i) {
			temp[i] = point[i];
			point[i].y += 1;
		}
		if (!Game::checkFieldSides()) {
			for (uint16_t i{ 0 }; i < 4; ++i)
			{
				field[temp[i].y][temp[i].x] = t_tetraminoColor;
			}
			Game::setNewTetramino();
		}
		Timer::get()->reset();
	}
}

void Game::rotate() {
	if  (t_tetramino != 6) {
		p = point[2];	//rotate center
		for (uint16_t i{ 0 }; i < 4; ++i) {
			temp[i] = point[i];
			uint16_t x = point[i].y - p.y;
			uint16_t y = point[i].x - p.x;
			point[i].x = p.x - x;
			point[i].y = p.y + y;
		}
		short left{ 0 };
		short right{ 0 };
		for (uint16_t i{ 0 }; i < 4; ++i) {
			if (point[i].x < 0 && point[i].x < left) { left -= point[i].x; }
			else if (point[i].x >= FIELD_WIDTH && point[i].x > right) { right -= FIELD_WIDTH - 1 - point[i].x; }
		}
		for (uint16_t i{ 0 }; i < 4; ++i) {
			point[i].x += left;
			point[i].x -= right;
		}
	}
}

bool Game::checkFieldSides() {
	for (uint16_t i{ 0 }; i < 4; ++i) {
		if (point[i].x < 0 || point[i].x >= FIELD_WIDTH || point[i].y >= FIELD_HEIGHT) return 0;
		else if (field[point[i].y][point[i].x]) return 0;
	}
	return 1;
}

void Game::checkFullLine() {
	uint16_t maxLineCount { 0 };  
	uint16_t lineCount    { 0 };
	int k = FIELD_HEIGHT - 1;
	for (uint16_t i { FIELD_HEIGHT - 1 }; i > 0; --i) {
		short count{ 0 };
		for (uint16_t j { 0 }; j < FIELD_WIDTH; ++j) {
			if (field[i][j]) count++;
			field[k][j] = field[i][j];
		}
		if (count < FIELD_WIDTH) {
			k--; 
			lineCount = 0;
		}
		else {
			lineCount++;
			m_totallines += 1;
			if (maxLineCount < lineCount)
				maxLineCount = lineCount;
		}	
	}
	changelvl(m_totallines);
	addScore(maxLineCount);
}

void Game::addScore(const uint16_t& count) {
	uint16_t points{ 0 };
	switch (count) {
	case 1: points = 100;
		break;
	case 2: points = 300;
		break;
	case 3: points = 700;
		break;
	case 4: points = 1500;
		break;
	}
	m_score += points + (std::ceil(points * multiplier[m_currentlvl]));
}

void Game::changelvl(const uint16_t& totalLines) {
	while (totalLines >= lines[m_currentlvl]) {
		m_currentlvl += 1;
		Timer::get()->m_delay = delay[m_currentlvl];
	}
}

bool Game::checkUpY() {
	for (uint16_t j{ 6 }; j < 8; ++j) {
		if (field[0][j]) return 0;
	}
	return 1;
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates state) const {	
	for (const auto& element : toDraw) 
		target.draw(element);		
}

void Game::drawFallenTiles() {
	for (uint16_t i{ 0 }; i < FIELD_HEIGHT; i++)
		for (uint16_t j{ 0 }; j < FIELD_WIDTH; j++) {
			if (field[i][j] == 0) continue;
			m_sTile.setTextureRect({ field[i][j] * sizeTile, 0, sizeTile, sizeTile });
			m_sTile.setPosition(j * sizeTile, i * sizeTile);
			m_sTile.move(108.f, 0.f);
			toDraw.push_back(m_sTile);
		}

	// moving tetramino
	for (uint16_t i{ 0 }; i < 4; ++i) {
		m_sTile.setTextureRect({ t_tetraminoColor * sizeTile, 0, sizeTile, sizeTile });
		m_sTile.setPosition(point[i].x * sizeTile, point[i].y * sizeTile);
		m_sTile.move(108.f, 0.f);
		
		toDraw.push_back(m_sTile);
	}	
}

void Game::drawNextTetramino() {
	for (uint16_t i{ 0 }; i < 4; ++i) {
		next[i].x = figure[t_Next][i] % 2;
		next[i].y = figure[t_Next][i] / 2;
	}

	for (uint16_t i{ 0 }; i < 4; ++i) {
		m_sTile.setTextureRect({t_NextColor * sizeTile, 0, sizeTile, sizeTile });
		m_sTile.setPosition(next[i].x * sizeTile, next[i].y * sizeTile);

		switch (t_Next) {
		case 0: m_sTile.move(405.f, 62.f);
			break;
		case 1: m_sTile.move(395.f, 72.f);
			break;
		case 2: m_sTile.move(395.f, 72.f);
			break;
		case 3: m_sTile.move(395.f, 72.f);
			break;
		case 4: m_sTile.move(395.f, 72.f);
			break;
		case 5: m_sTile.move(395.f, 72.f);
			break;
		case 6: m_sTile.move(395.f, 81.f);
			break;
		}

		toDraw.push_back(m_sTile);
	}
} 

void Game::drawHoldTetramino() {
	if (m_holdReady && !m_holdEmpty) {
		for (uint16_t i{ 0 }; i < 4; ++i) {
			hold[i].x = figure[t_holdTetramino][i] % 2;
			hold[i].y = figure[t_holdTetramino][i] / 2;
		}

		for (uint16_t i{ 0 }; i < 4; ++i) {
			m_sTile.setTextureRect({ t_holdColor * sizeTile, 0, sizeTile, sizeTile });
			m_sTile.setPosition(sizeTile * hold[i].x, sizeTile * hold[i].y);

			switch (t_holdTetramino)
			{
			case 0: m_sTile.move(45.f, 62.f);
				break;
			case 1: m_sTile.move(36.f, 72.f);
				break;
			case 2: m_sTile.move(36.f, 72.f);
				break;
			case 3: m_sTile.move(36.f, 72.f);
				break;
			case 4: m_sTile.move(36.f, 72.f);
				break;
			case 5: m_sTile.move(36.f, 72.f);
				break;
			case 6: m_sTile.move(36.f, 81.f);
				break;
			}

			toDraw.push_back(m_sTile);
		}
	}
}