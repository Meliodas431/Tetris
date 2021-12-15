#ifndef GAME_H
#define GAME_H
#include "settings.h"
#include "Game.h"
#include "Time.h"

class Game : public sf::Drawable {
public:
	sf::Texture m_tTile;
	sf::Sprite m_sTile;
	uint16_t t_tetramino;
	uint16_t t_tetraminoColor;
	uint16_t t_holdTetramino;
	uint16_t t_holdColor;
	uint16_t t_Next;
	uint16_t t_NextColor;

	bool m_holdReady { true };
	bool m_holdEmpty { true };
	uint32_t m_score;
	uint16_t m_totallines;
	uint16_t m_currentlvl;
	short m_move;

	static std::array<float, 20> multiplier;
	static std::array<float, 20> delay;
	static std::array<uint16_t, 20> lines;

	std::vector<sf::Sprite> toDraw;

private:
	uint16_t figure[7][4]{
	  0,2,4,6, //I 
	  0,2,3,5, //S
	  1,2,3,4, //Z
	  1,2,3,5, //T
	  0,1,3,5, //L
	  0,1,2,4, //J
	  0,1,2,3, //O
	};
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;

public:
	 Game();
	 ~Game();
	 void setNewTetramino();   
	 void moveByX(const short& move);
	 void moveByY();
	 void rotate();
	 bool checkFieldSides();   
	 void checkFullLine();     
	 bool checkUpY();
	 void holdTetramino();
	 void addScore(const uint16_t& count);
	 void changelvl(const uint16_t& lines);
	 void drawHoldTetramino();
	 void drawNextTetramino();
	 void drawFallenTiles();
};

#endif // GAME_H