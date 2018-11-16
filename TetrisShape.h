#ifndef TETRIS_SHAPE
#define TETRIS_SHAPE

#define ARRAY_LEN 4
#define MATRIX_LEN 4
#define SHAPES_NUMBER 6
#define SPACE_TEXTURE "black"

#include "Point.h"
#include "Cell.h"

#pragma once
class TetrisShape
{
protected:
	int x;
	int y;
	static int shift_x;
	static int shift_y;
	Cell ***matrix;
	Point *arr;
	string color;
public:
	TetrisShape();
	TetrisShape(int x, int y);
	~TetrisShape();
	Point*& getPointsArr();
	Cell***& getMatrix();

	int getX();
	int getY();
	string getColor();
	void setX(int x);
	void setY(int y);
	void rotateTetrisShape(Cell ***&cell_matrix);
	static void fillPointsArray(Point *&arr, Cell ***&matrix, string color);
	static void makeMatrixEmpty(Cell ***&matrix);
	static void findShifts(int &shift_x, int &shift_y, Cell ***&matrix, string color);
	bool addNewTetrisShape(Cell ***&cell_matrix, int &x, int &y);
	void eraseCurrentTetrisShape(Cell ***&cell_matrix);
	void updateTetrisShape(Cell ***&cell_matrix, int &x, int &y);
	void addCurrentTetrisShape(Cell ***&cell_matrix);
	static void deleteMatrix(Cell ***& matrix);
};

class TetrisShapeG : public TetrisShape
{
public:
	TetrisShapeG();
	TetrisShapeG(int x, int y);
	~TetrisShapeG();
};

class TetrisShapeInversedG : public TetrisShape
{
public:
	TetrisShapeInversedG();
	TetrisShapeInversedG(int x, int y);
	~TetrisShapeInversedG();
};

class TetrisShapeRectangle : public TetrisShape
{
public:
	TetrisShapeRectangle();
	TetrisShapeRectangle(int x, int y);
	~TetrisShapeRectangle();
};

class TetrisShapeSquare : public TetrisShape
{
public:
	TetrisShapeSquare();
	TetrisShapeSquare(int x, int y);
	~TetrisShapeSquare();
};


class TetrisShapeFiga : public TetrisShape
{
public:
	TetrisShapeFiga();
	TetrisShapeFiga(int x, int y);
	~TetrisShapeFiga();
};

class TetrisShapeLightning : public TetrisShape
{
public:
	TetrisShapeLightning();
	TetrisShapeLightning(int x, int y);
	~TetrisShapeLightning();
};

#endif