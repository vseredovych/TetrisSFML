#ifndef CELL
#define CELL

#define MATRIX_START_POS_X 50
#define MATRIX_START_POS_Y 350
#define SPRITE_SIZE 30
#define BORDER IntRect(0, 0, 30, 30)

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const string files[8] = { "resources/yellow.jpg", "resources/green.jpg",
   "resources/cyan.jpg",  "resources/orange.jpg",
   "resources/blue.jpg",  "resources/purple.jpg",
   "resources/red.jpg", "resources/black.png" };

#pragma once
class Cell {
private:
	Sprite *sprite;

	IntRect sprite_borders;
	string file_name;
	string color;
	Vector2f position;

public:
	Cell();
	Cell(int x, int y, string color);
	Cell(int x, int y);
	~Cell();
	void operator=(const Cell& cell);
	void copyShell(const Cell *cell);
	void setColor(string color);
	void copyColor(Cell *cell);
	static string getFileName(string name);
	static int getFileIndex(string name);
	string getColor();
	Sprite& getSprite() const;
	Sprite& getRealSprite();
};
#endif