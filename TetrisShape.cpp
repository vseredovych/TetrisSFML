#include <iostream>
#include <string>
#include "Point.h"
#include "Cell.h"
#include "TetrisShape.h"
using namespace std;

	int TetrisShape::shift_x = 0;
	int TetrisShape::shift_y = 0;

	TetrisShape::TetrisShape() : TetrisShape(1, 1) {};
	TetrisShape::TetrisShape(int x, int y) {
		matrix = new Cell**[MATRIX_LEN];
		arr = new Point[ARRAY_LEN];
		this->x = x;
		this->y = y;
	}
	TetrisShape::~TetrisShape() {
		{
			deleteMatrix(matrix);
			delete[] arr;
		}
	}
	Point*& TetrisShape::getPointsArr() {
		return arr;
	}
	Cell***& TetrisShape::getMatrix() {
		return matrix;
	}
	int TetrisShape::getX() {
		return x;
	}
	int TetrisShape::getY() {
		return y;
	}
	string TetrisShape::getColor() {
		return color;
	}
	void TetrisShape::setX(int x) {
		this->x = x;
		fillPointsArray(arr, matrix, color);
	}
	void TetrisShape::setY(int y) {
		this->y = y;
		fillPointsArray(arr, matrix, color);
	}
	void TetrisShape::rotateTetrisShape(Cell ***&cell_matrix) {
			Cell ***temp = new Cell**[MATRIX_LEN];

			makeMatrixEmpty(temp);

			for (int i = 0; i < MATRIX_LEN; i++) {
				for (int j = 0; j < MATRIX_LEN; j++) {
					temp[j][MATRIX_LEN - i - 1]->copyShell(matrix[i][j]);
				}
			}
			for (int i = 0; i < MATRIX_LEN; i++) {
				for (int j = 0; j < MATRIX_LEN; j++) {
					matrix[i][j]->copyShell(temp[i][j]);
				}
			}
			deleteMatrix(temp);
	}
	void TetrisShape::fillPointsArray(Point *&arr, Cell ***&matrix, string color/*, int shift_x, int shift_y*/) {
		int count = 0;
		shift_x = 0;
		shift_y = 0;

		findShifts(shift_x, shift_y, matrix, color);

		for (int i = 0; i < MATRIX_LEN; i++) {
			for (int j = 0; j < MATRIX_LEN; j++) {
				if (matrix[i][j]->getColor() == color) {
					arr[count] = Point(i - shift_y, j - shift_x);
					count++;
				}
			}
		}


	}
	void TetrisShape::findShifts(int &shift_x, int &shift_y, Cell ***&matrix, string color)
	{
		bool b = true;
		for (int i = 0; i < MATRIX_LEN; i++) {
			for (int j = 0; j < MATRIX_LEN; j++) {
				if (matrix[i][j]->getColor() == color) {
					b = false;
					break;
				}
				else if (j == 3) {
					shift_y++;
				}
			}
			if (b == false)
			{
				break;
			}
		}
		b = true;
		for (int i = 0; i < MATRIX_LEN; i++) {
			for (int j = 0; j < MATRIX_LEN; j++) {
				if (matrix[j][i]->getColor() != SPACE_TEXTURE) {
					b = false;
					break;
				}
				else if (j == 3) {
					shift_x++;
				}
			}
			if (b == false)
			{
				break;
			}
		}
	}

	void TetrisShape::makeMatrixEmpty(Cell ***&matrix) {
		for (int i = 0; i < MATRIX_LEN; i++) {
			matrix[i] = new Cell*[MATRIX_LEN];
			for (int j = 0; j < MATRIX_LEN; j++) {
				matrix[i][j] = new Cell(0, 0, "black");
			}
		}
	}
	void TetrisShape::updateTetrisShape(Cell ***&cell_matrix, int &x, int &y) {

		eraseCurrentTetrisShape(cell_matrix);

		this->x = x;
		this->y = y;
		fillPointsArray(arr, matrix, color);
		addCurrentTetrisShape(cell_matrix);
	}
	bool TetrisShape::addNewTetrisShape(Cell ***&cell_matrix, int &x, int &y) {

		this->x = x;
		this->y = y;
		fillPointsArray(arr, matrix, color);
		//HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		for (int i = 0; i < ARRAY_LEN; i++) {
			if (cell_matrix[arr[i].getX() + x][arr[i].getY() + y]->getColor() != SPACE_TEXTURE)
			{
				return 0;
			}
			else {
				cell_matrix[arr[i].getX() + x][arr[i].getY() + y]->setColor(color);
			}
		}
		return 1;

	}
	void TetrisShape::addCurrentTetrisShape(Cell ***&cell_matrix) {

		for (int i = 0; i < ARRAY_LEN; i++) {
		cell_matrix[arr[i].getX() + x][arr[i].getY() + y]->setColor(color);
		}
	}
	void TetrisShape::eraseCurrentTetrisShape(Cell ***&cell_matrix) {
		for (int i = 0; i < ARRAY_LEN; i++) {
			cell_matrix[arr[i].getX() + x][arr[i].getY() + y]->setColor(SPACE_TEXTURE);
		}
	}
	void TetrisShape::deleteMatrix(Cell ***& matrix) {
		for (int i = 0; i < MATRIX_LEN; i++) {
			for (int j = 0; j < MATRIX_LEN; j++) {
				delete matrix[i][j];
			}
			delete[] matrix[i];
		}
		delete[] matrix;
	}
	

	
	TetrisShapeG::TetrisShapeG() : TetrisShapeG(1, 1) {};
	TetrisShapeG::TetrisShapeG(int x, int y)
	{
		this->color = "yellow";
		this->x = x;
		this->y = y;
		matrix = new Cell**[MATRIX_LEN];
		arr = new Point[ARRAY_LEN];

		makeMatrixEmpty(matrix);

		matrix[1][0]->setColor(color);
		matrix[2][0]->setColor(color);
		matrix[2][1]->setColor(color);
		matrix[2][2]->setColor(color);

		fillPointsArray(arr, matrix, color);
	}
	TetrisShapeG::~TetrisShapeG()
	{
		deleteMatrix(matrix);
		delete[] arr;
	}
	

	TetrisShapeInversedG::TetrisShapeInversedG() : TetrisShapeInversedG(1, 1) {};
	TetrisShapeInversedG::TetrisShapeInversedG(int x, int y)
	{

		this->color = "green";
		this->x = x;
		this->y = y;
		matrix = new Cell**[MATRIX_LEN];
		arr = new Point[ARRAY_LEN];

		makeMatrixEmpty(matrix);

		matrix[1][2]->setColor(color);
		matrix[2][0]->setColor(color);
		matrix[2][1]->setColor(color);
		matrix[2][2]->setColor(color);

		fillPointsArray(arr, matrix, color);
	}
	TetrisShapeInversedG::~TetrisShapeInversedG()
	{
		deleteMatrix(matrix);
		delete[] arr;
	}



	TetrisShapeRectangle::TetrisShapeRectangle() : TetrisShapeRectangle(1, 1) {};
	TetrisShapeRectangle::TetrisShapeRectangle(int x, int y)
	{

		this->color = "blue";
		this->x = x;
		this->y = y;
		matrix = new Cell**[MATRIX_LEN];
		arr = new Point[ARRAY_LEN];

		makeMatrixEmpty(matrix);

		matrix[0][0]->setColor(color);
		matrix[1][0]->setColor(color);
		matrix[2][0]->setColor(color);
		matrix[3][0]->setColor(color);

		fillPointsArray(arr, matrix, color);
	}
	TetrisShapeRectangle::~TetrisShapeRectangle()
	{
		deleteMatrix(matrix);
		delete[] arr;
	}



	TetrisShapeSquare::TetrisShapeSquare() : TetrisShapeSquare(1, 1) {};
	TetrisShapeSquare::TetrisShapeSquare(int x, int y)
	{

		this->color = "red";
		this->x = x;
		this->y = y;
		matrix = new Cell**[MATRIX_LEN];
		arr = new Point[ARRAY_LEN];

		makeMatrixEmpty(matrix);

		matrix[0][0]->setColor(color);
		matrix[0][1]->setColor(color);
		matrix[1][0]->setColor(color);
		matrix[1][1]->setColor(color);

		fillPointsArray(arr, matrix, color);
	}
	TetrisShapeSquare::~TetrisShapeSquare()
	{
		deleteMatrix(matrix);
		delete[] arr;
	}


	TetrisShapeFiga::TetrisShapeFiga() : TetrisShapeFiga(1, 1) {};
	TetrisShapeFiga::TetrisShapeFiga(int x, int y)
	{

		this->color = "cyan";
		this->x = x;
		this->y = y;
		matrix = new Cell**[MATRIX_LEN];
		arr = new Point[ARRAY_LEN];

		makeMatrixEmpty(matrix);

		matrix[1][1]->setColor(color);
		matrix[2][0]->setColor(color);
		matrix[2][1]->setColor(color);
		matrix[2][2]->setColor(color);

		fillPointsArray(arr, matrix, color);
	}
	TetrisShapeFiga::~TetrisShapeFiga()
	{
		deleteMatrix(matrix);
		delete[] arr;
	}


	TetrisShapeLightning::TetrisShapeLightning() : TetrisShapeLightning(1, 1) {};
	TetrisShapeLightning::TetrisShapeLightning(int x, int y)
	{

		this->color = "purple";
		this->x = x;
		this->y = y;
		matrix = new Cell**[MATRIX_LEN];
		arr = new Point[ARRAY_LEN];

		makeMatrixEmpty(matrix);

		matrix[1][1]->setColor(color);
		matrix[1][2]->setColor(color);
		matrix[2][0]->setColor(color);
		matrix[2][1]->setColor(color);

		fillPointsArray(arr, matrix, color);
	}
	TetrisShapeLightning::~TetrisShapeLightning()
	{
		deleteMatrix(matrix);
		delete[] arr;
	}