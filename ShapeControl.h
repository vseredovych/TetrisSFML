#ifndef SHAPE_CONTROL
#define SHAPE_CONTROL
#include "Point.h"
#include "TetrisShape.h"
#define SHAPES_EMOUNT 8


#pragma once
class ShapeControl {
public:
	static bool ifNextStepTouch(Cell ***&cell_matrix, TetrisShape *&shape, int x_, int y_);
	static bool ifNextRotate(Cell ***&cell_matrix, TetrisShape *&shape, int &x, int &y);
	static bool checkRight(TetrisShape *&shape);

	static bool checkBottom(TetrisShape *&shape);
	static bool checkRotatePos(TetrisShape *&shape, Point *&arrNext);
};

#endif