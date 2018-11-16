#include "TetrisControl.h"
#include "TetrisShape.h"
#include "Cell.h"
#include <conio.h>
#include <iostream>
#include <sstream>
#include <time.h>
#include <mutex>
#include <string>
#include <windows.h>
#include <fstream>
#include "ShapeControl.h"
std::mutex cout_guard;


Tetris::Tetris(RenderWindow& window)
{
	/*timer = 0;
	delay = 0.3;*/
	ifEnd = true;
	this->window = &window;
	this->x = 0;
	this->y = WIDTH_LEN / 2;
	srand((int)time(0));
	this->next = rand() % 6;

	shapes = new TetrisShape*[SHAPES_NUMBER];
	shapes[0] = new TetrisShapeG(x, y);
	shapes[1] = new TetrisShapeRectangle(x, y);
	shapes[2] = new TetrisShapeSquare(x, y);
	shapes[3] = new TetrisShapeFiga(x, y);
	shapes[4] = new TetrisShapeInversedG(x, y);
	shapes[5] = new TetrisShapeLightning(x, y);
	speed = 700;
}

void Tetris::ActionControl(Clock &clock) {

	//float time = clock.getElapsedTime().asSeconds();
	//clock.restart();
	//timer2 += time;
	enum Commands {
		UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 13,
		R = 114, ESC = 27, W = 119, A = 97, S = 115, D = 100
	};

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && x > 0) {
	//	if (ShapeControl::ifNextStepTouch(cell_matrix, shapes[current], -1, 0)) {
	//		x -= 1;
	//	}
	//}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && y > 0) {
		if (ShapeControl::ifNextStepTouch(cell_matrix, shapes[current], 0, -1)) {
			y -= 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		//delay = 0.05;
		touchCheck();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && ShapeControl::checkRight(shapes[current])) {
		if (ShapeControl::ifNextStepTouch(cell_matrix, shapes[current], 0, 1)) {
			y += 1;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		if (ShapeControl::ifNextRotate(cell_matrix, shapes[current], x, y)) {
			updateTetris();
			shapes[current]->rotateTetrisShape(cell_matrix);
			Sleep(75);
		}
	}
}


bool Tetris::tetrisStart() {

	Clock clock;
	Clock clock1;

	Texture *textures = new Texture[SHAPES_EMOUNT];
	for (int i = 0; i < SHAPES_EMOUNT; i++) {
		textures[i].loadFromFile(files[i]);
	}
	////////////////////////////////////////////
//	Texture border;
	//border.loadFromFile("resources/borders.png");
	//Sprite b;
	//b.setTexture(border);
	//b.setPosition(50, 50);
	//b.setTextureRect(IntRect(0, 0, 300, 600));


	createCellMatrix();

	SYSTEMTIME st;
	GetLocalTime(&st);
	int time = st.wMilliseconds;
	int timepass = 0;
	addNextShape();

	window->setVerticalSyncEnabled(true);
	while (window->isOpen())
	{
		/////////////////////Timer//////////////////////
		//float time = clock.getElapsedTime().asSeconds();
		//clock.restart();
		//timer += time;
		////////////////////////////////////////////////
		window->clear();
		window->setFramerateLimit(60);
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		if (ifEnd == false) {
			cout << "";
			return 1;
		}


		ActionControl(clock1);
		updateTetris();
		/*
		if (timer > delay) {
			touchCheck();
			timer = 0;
		}*/
		////////////////////
		GetLocalTime(&st);
		timepass += abs(time - st.wMilliseconds);
		////////////////////
		Sleep(50);
		if (timepass > 700) {
			
			touchCheck();
			/////////////////////
			timepass = 0;
			time = st.wMilliseconds;
			/////////////////////
			updateTetris();
		}

		printCellMatrix(textures);
		printNextShape(textures);
		printScore();
		window->display();
	}
	return 1;

}
void Tetris::touchCheck() {

	if (ShapeControl::checkBottom(shapes[current])) {
		if (ShapeControl::ifNextStepTouch(cell_matrix, shapes[current], 1, 0)) {
			x += 1;
		}
		else {
			ifFullRow();
			addNextShape();
		}
	}
	else {
		ifFullRow();
		addNextShape();
		//Sleep(30);
		//timer = 0;
	}
}
void Tetris::createCellMatrix() {

	cell_matrix = new Cell **[HEIGHT_LEN];
	for (int i = 0; i < HEIGHT_LEN; i++) {
		cell_matrix[i] = new Cell*[WIDTH_LEN];
		for (int j = 0; j < WIDTH_LEN; j++) {
			cell_matrix[i][j] = new Cell(i, j, SPACE_TEXTURE);
		}
	}
}
void Tetris::updateTetris() {

	cout_guard.lock();
	shapes[current]->updateTetrisShape(cell_matrix, x, y);
	cout_guard.unlock();

}

bool Tetris::addNextShape() {
	x = 0;
	y = WIDTH_LEN / 2;
	current = next;
	shapes[current]->setX(x);
	shapes[current]->setY(y);

	if (!shapes[current]->addNewTetrisShape(cell_matrix, x, y)) {
		ifEnd = false;
		return 0;
	}
	
	next = rand() % 6;
	return 1;	
}

void Tetris::ifFullRow() {
	int count = 0;
	while (findFullRows()) {
		count += 1;
		deleteRows(findFullRows());
		Score += count * count * 10;
	}
}
int Tetris::findFullRows()
{
	int index = 0;
	for (int i = 0; i < HEIGHT_LEN; i++) {
		for (int j = 0; j < WIDTH_LEN; j++) {
			if (cell_matrix[i][j]->getColor() != SPACE_TEXTURE) {
				if (j == WIDTH_LEN - 1) {
					index = i;
				}
				else {
					continue;
				}
			}
			else {
				break;
			}

		}
	}
	return index;
}

void Tetris::deleteRows(int index) {
	for (int i = index; i > 1; i--) {
		for (int j = 0; j < WIDTH_LEN; j++) {
			cell_matrix[i][j]->setColor((*cell_matrix[i - 1][j]).getColor());
		}
	}
}
void Tetris::setShape(int index) {
	if (index == 0) {
		shapes[index] = new TetrisShapeG(x, y);
	} 
	else if (index == 1) {
		shapes[index] = new TetrisShapeRectangle(x, y);
	}
	else if (index == 2) {
		shapes[index] = new TetrisShapeSquare(x, y);
	}
	else if (index == 3) {
		shapes[index] = new TetrisShapeFiga(x, y);
	}
	else if (index == 4) {
		shapes[index] = new TetrisShapeInversedG(x, y);
	}
	else if (index == 5) {
		shapes[index] = new TetrisShapeLightning(x, y);
	}
}


void Tetris::printCellMatrix(Texture *& textures) {

	Sprite s;
	int currentTexture;
	Vector2f pos;

	for (int i = 0; i < HEIGHT_LEN; i++) {
		for (int j = 0; j < WIDTH_LEN; j++) {
			currentTexture = Cell::getFileIndex(cell_matrix[i][j]->getColor());
			s = cell_matrix[i][j]->getRealSprite();
			s.setTexture(textures[currentTexture]);
			window->draw(s);
		}
	}
}
void Tetris::printNextShape(Texture *& textures) {
	Sprite s;
	int currentTexture;
	Cell ***temp;
	Vector2f pos;

	temp = shapes[next]->getMatrix();
	for (int i = 0; i < MATRIX_LEN; i++) {
		for (int j = 0; j < MATRIX_LEN; j++) {
			currentTexture = Cell::getFileIndex(temp[i][j]->getColor());
			s = temp[i][j]->getRealSprite();
			pos.x = MATRIX_START_POS_Y + i * SPRITE_SIZE + 350;
			pos.y = MATRIX_START_POS_X + j * SPRITE_SIZE + 120;
			s.setPosition(pos);
			s.setTexture(textures[currentTexture]);
			window->draw(s);
		}
	}
}
void Tetris::printScore() {
	string score_string;
	string temps;
	stringstream ss;
	ss << Score;
	ss >> temps;
	score_string = "Score: " + temps;

	Font font;
	font.loadFromFile("resources/font.ttf");
	Text text("Next:", font, 30);
	text.setPosition(350 + MATRIX_START_POS_Y, 110);

	Text score_text(score_string, font, 30);
	score_text.setPosition(MATRIX_START_POS_Y - 220, MATRIX_START_POS_Y - 240);


	window->draw(text);
	window->draw(score_text);
}