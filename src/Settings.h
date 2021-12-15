#ifndef SETTINGS_H
#define SETTINGS_H
#include <string>

const uint16_t FIELD_HEIGHT   { 27 }; //высота поля FIELD_HEIGHT
const uint16_t FIELD_WIDTH    { 14 }; //ширина поля FIELD_WIDTH
const uint16_t sizeTile       { 18 };

const std::string tiles       { "textures/tiles.png" };
const std::string background  { "textures/background.jpg" };
const std::string data        { "data.txt" };
const std::string font        { "font/arial.ttf" };

extern struct Point {
	short x{ 0 }, y{ 0 };
}; 

extern uint16_t field[FIELD_HEIGHT][FIELD_WIDTH];
extern uint16_t figure[7][4];

#endif // !SETTINGS_H