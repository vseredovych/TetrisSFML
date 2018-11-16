#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Cell.h"



using namespace std;
using namespace sf;



Cell::Cell() : Cell(0, 0) {};

Cell::Cell(int x, int y, string color) {
	this->color = color;
	file_name = Cell::getFileName(color);
	sprite = new Sprite;
	sprite_borders = BORDER;
	this->file_name = file_name;

	position.x = float(MATRIX_START_POS_Y + y * SPRITE_SIZE);
	position.y = float(MATRIX_START_POS_X + x * SPRITE_SIZE);

	sprite->setPosition(position);
	sprite->setTextureRect(sprite_borders);
}
Cell::Cell(int x, int y) {
	sprite = new Sprite;
	sprite_borders = BORDER;

	position.x = float(MATRIX_START_POS_Y + y * SPRITE_SIZE);
	position.y = float(MATRIX_START_POS_X + x * SPRITE_SIZE);

	sprite->setPosition(position);
	sprite->setTextureRect(sprite_borders);

}
Cell::~Cell() {
	delete sprite;
}
void Cell::operator=(const Cell& cell) {

	
	sprite = cell.sprite;
	this->color = cell.color;
	this->sprite_borders = cell.sprite_borders;
	this->file_name = cell.file_name;
	this->position = cell.position;
}
void Cell::copyShell(const Cell *cell) {


	*sprite = *(cell->sprite);
	this->color = cell->color;
	this->sprite_borders = cell->sprite_borders;
	this->file_name = cell->file_name;
	sprite->setPosition(position);
	sprite->setTextureRect(sprite_borders);

}

void Cell::setColor(string color) {
	this->color = color;
	file_name = Cell::getFileName(color);
}
void Cell::copyColor(Cell *cell) {
	this->color = cell->color;
}
string Cell::getFileName(string name) {

	if (name == "yellow") {
		return files[0];
	}
	else if (name == "green") {
		return files[1];
	}
	else if (name == "cyan") {
		return files[2];
	}
	else if (name == "orange") {
		return files[3];
	}
	else if (name == "blue") {
		return files[4];
	}
	else if (name == "purple") {
		return files[5];
	}
	else if (name == "red") {
		return files[6];
	}
	else {
		return files[7];
	}
}
int Cell::getFileIndex(string name) {

	if (name == "yellow") {
		return 0;
	}
	else if (name == "green") {
		return 1;
	}
	else if (name == "cyan") {
		return 2;
	}
	else if (name == "orange") {
		return 3;
	}
	else if (name == "blue") {
		return 4;
	}
	else if (name == "purple") {
		return 5;
	}
	else if (name == "red") {
		return 6;
	}
	else {
		return 7;
	}
}
string Cell::getColor() {
	return color;
}
Sprite& Cell::getSprite() const {
	return *sprite;
}
Sprite& Cell::getRealSprite() {
	return *sprite;
}