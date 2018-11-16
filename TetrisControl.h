#ifndef TETRIS_CONTROL
#define TETRIS_CONTROL
#include "TetrisShape.h"
#include "Cell.h"
#define WIDTH_LEN 10
#define HEIGHT_LEN 20


#pragma once
class Tetris
{
private:
	int x;
	int y;
	int current;
	int next;
	int speed;
	int Score;
	bool ifEnd;
	//float timer;
	//float timer2;
	float delay;
	Cell ***cell_matrix;
	RenderWindow *window;

	void createCellMatrix();
	void updateTetris();
	void ActionControl(Clock &clock);
	void touchCheck();
	bool addNextShape();
	void setShape(int index);
	void ifFullRow();
	int findFullRows();
	void deleteRows(int index);
	void printCellMatrix(Texture *& textures);
	void printNextShape(Texture *& textures);
	void printScore();
	void GG();
public:

	TetrisShape **shapes;
	Tetris(RenderWindow& window);
	bool tetrisStart();
};

#endif