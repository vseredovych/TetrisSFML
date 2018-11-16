#include "Point.h"
#include "TetrisShape.h"
#include "ShapeControl.h"
#include "TetrisControl.h"

bool ShapeControl::ifNextStepTouch(Cell ***&cell_matrix, TetrisShape *&shape, int x_, int y_)
{
	Point *arrNext = new Point[ARRAY_LEN];
	for (int i = 0; i < ARRAY_LEN; i++) {
		arrNext[i].setX(shape->getPointsArr()[i].getX() + x_);
		arrNext[i].setY(shape->getPointsArr()[i].getY() + y_);
	}
	bool b = true;
	for (int i = 0; i < ARRAY_LEN; i++) {
		for (int j = 0; j < ARRAY_LEN; j++) {
			if (shape->getPointsArr()[j] == arrNext[i]) {
				b = false;
				break;
			}
		}
		if (b) {
			if (cell_matrix[arrNext[i].getX() + shape->getX()][arrNext[i].getY() + shape->getY()]->getColor() != SPACE_TEXTURE) {
				delete[] arrNext;
				return 0;
			}
		}
		b = true;
	}
	delete[] arrNext;
	return 1;
}
bool ShapeControl::ifNextRotate(Cell ***&cell_matrix, TetrisShape *&shape, int &x, int &y) {

	Cell ***temp = new Cell**[MATRIX_LEN];
	Point *arrNext = new Point[ARRAY_LEN];

	TetrisShape::makeMatrixEmpty(temp);

	for (int i = 0; i < MATRIX_LEN; i++) {
		for (int j = 0; j < MATRIX_LEN; j++) {
			temp[j][MATRIX_LEN - i - 1]->copyShell(shape->getMatrix()[i][j]);
		}
	}

	TetrisShape::fillPointsArray(arrNext, temp, shape->getColor());
	if (checkRotatePos(shape, arrNext) == 0) {
		TetrisShape::deleteMatrix(temp);
		delete[] arrNext;
		return 0;
	}

	bool b = true;
	for (int i = 0; i < ARRAY_LEN; i++) {
		for (int j = 0; j < ARRAY_LEN; j++) {
			if (shape->getPointsArr()[j] == arrNext[i]) {
				b = false;
				break;
			}
		}
		if (b) {
			if (cell_matrix[arrNext[i].getX() + shape->getX()][arrNext[i].getY() + shape->getY()]->getColor() != SPACE_TEXTURE) {
				TetrisShape::deleteMatrix(temp);
				delete[] arrNext;
				return 0;
			}
		}
		b = true;
	}

	TetrisShape::deleteMatrix(temp);
	delete[] arrNext;
	return 1;
}
bool ShapeControl::checkRight(TetrisShape *&shape) {

	for (int i = 0; i < ARRAY_LEN; i++) {
		if (shape->getPointsArr()[i].getY() + shape->getY() < WIDTH_LEN - 1) {
			continue;
		}
		else {
			return 0;
		}
	}
	return 1;
}

bool ShapeControl::checkBottom(TetrisShape *&shape) {

	for (int i = 0; i < ARRAY_LEN; i++) {
		if (shape->getPointsArr()[i].getX() + shape->getX() < HEIGHT_LEN - 1) {
			continue;
		}
		else {
			return 0;
		}
	}
	return 1;
}
bool ShapeControl::checkRotatePos(TetrisShape *&shape, Point *&arrNext) {
	while (arrNext[0].getX() + shape->getX() >= HEIGHT_LEN ||
		arrNext[1].getX() + shape->getX() >= HEIGHT_LEN ||
		arrNext[2].getX() + shape->getX() >= HEIGHT_LEN ||
		arrNext[3].getX() + shape->getX() >= HEIGHT_LEN)
	{
		//shape->setX(shape->getX() - 1);
		return 0;

	}

	while (arrNext[0].getY() + shape->getY() >= WIDTH_LEN ||
		arrNext[1].getY() + shape->getY() >= WIDTH_LEN ||
		arrNext[2].getY() + shape->getY() >= WIDTH_LEN ||
		arrNext[3].getY() + shape->getY() >= WIDTH_LEN)
	{

		//shape->setY(shape->getY() - 1);
		return 0;
	}
	return 1;
}