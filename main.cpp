#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "TetrisShape.h"
#include "TetrisControl.h"
#include <iostream>
using namespace std;

int main()
{	
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Tetris");

    Tetris tetris(window);
	tetris.tetrisStart();
	
	return 0;
}