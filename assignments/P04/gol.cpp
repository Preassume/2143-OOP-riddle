/**
*  Course: CMPS 2143 Object Oriented Programming
*  Assignment: P04
*  Purpose: This program is an implementation of John Conway's Game of Life.
*          Cells live or die based on how many living cells are near them.
*          It is visualized using SFML.  Also outputs final board as a text file.
*          Requires 3 command line arguments:
*          - Input file name (including file extension)
*          - Number of iterations to run
*          - Output file name (including file extension)
*
*  @author Austin Riddle
*  @version 1.0 10/15/2018
*  @github repo: https://github.com/Preassume/2143-OOP-riddle
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "gol.h"
using namespace sf;

tile::tile(){
    Width = 10;
    Height = 10;
    rect.setSize(sf::Vector2f(Width, Height));
    rect.setFillColor(Color::White);
    rect.setOutlineColor(Color::Black);
    rect.setOutlineThickness(1);
}

void tile::setTilePos(int x, int y){
    rect.setPosition(x * Width, y * Height);
}

board::board(int w, int h, int fr){
    frameRate = fr;
    window.create(VideoMode(w, h), "Game of Life");
}

void board::startGame(std::string iFilename, char* runs, std::string oFilename){
	std::ifstream ifile;
	ifile.open(iFilename);

	int numRun = atoi(runs); //converts the string 'runs' into an int

	makeBoard(ifile);

	int frameCount = 0; //counts how many times the board has been drawn
	int loopCount = 0; //counts how many times we have gone through the loop

    while (window.isOpen() && frameCount < numRun){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
        }
        if(loopCount % frameRate == 0){
            updateBoard();
            drawBoard();
            frameCount++;
        }
        loopCount++;
    }

	std::ofstream ofile;
	ofile.open(oFilename);

	outputBoard(ofile);
}

void board::makeBoard(std::ifstream& ifile){
    //xAxis and yAxis are swapped to get proper orientation of the board
	ifile >> yAxis;
	ifile >> xAxis;

	std::string line; //one line from input file

	golBoard = new tile*[xAxis];

	for(int x = 0; x < xAxis; x++){
		golBoard[x] = new tile[yAxis];
	}

	int inChar; //used to convert character from input to integer

	for(int y = 0; y < yAxis; y++){
		ifile >> line;
		for(int x = 0; x < xAxis; x++){
			inChar = line[x] - 48;
			golBoard[x][y].alive = inChar;
		}
	}
	positionTiles();
}

void board::positionTiles(){
    for(int y = 0; y < yAxis; y++){
		for(int x = 0; x < xAxis; x++){
			golBoard[x][y].setTilePos(x, y);
		}
	}
}

void board::outputBoard(std::ofstream& ofile){
	for(int y = 0; y < yAxis; y++){
		for(int x = 0; x < xAxis; x++){
			ofile << golBoard[x][y].alive << ' ';
		}
		ofile << '\n';
	}
	ofile << '\n';
}

bool board::isAlive(int x, int y){
	return golBoard[x][y].alive;
}

int board::numNeigh(int x, int y){
	return golBoard[x][y].liveNeighbors;
}

bool board::onBoard(int x, int y){
	if(x >= 0 && x < xAxis && y >= 0 && y < yAxis)
		return true;
	else
		return false;
}

void board::updateTile(int x, int y){
	int numLiveNeighbors = 0;

	//check all 8 neighbors if they are alive (but only if they are on the board)
	if(onBoard(x-1, y-1))
		numLiveNeighbors += isAlive(x-1, y-1);

	if(onBoard(x-1, y))
		numLiveNeighbors += isAlive(x-1, y);

	if(onBoard(x-1, y+1))
		numLiveNeighbors += isAlive(x-1, y+1);

	if(onBoard(x, y-1))
		numLiveNeighbors += isAlive(x, y-1);

	if(onBoard(x, y+1))
		numLiveNeighbors += isAlive(x, y+1);

	if(onBoard(x+1, y-1))
		numLiveNeighbors += isAlive(x+1, y-1);

	if(onBoard(x+1, y))
		numLiveNeighbors += isAlive(x+1, y);

	if(onBoard(x+1, y+1))
		numLiveNeighbors += isAlive(x+1, y+1);

	golBoard[x][y].liveNeighbors = numLiveNeighbors;
}

void board::drawBoard(){
	window.clear();
	for(int y = 0; y < yAxis; y++){
        for(int x = 0; x < xAxis; x++){
            window.draw(golBoard[x][y].rect);
        }
        window.display();
	}
}

void board::updateBoard(){
	for(int y = 0; y < yAxis; y++){
		for(int x = 0; x < xAxis; x++){
			updateTile(x, y);
		}
	}
	getNext();
}

void board::getNext(){
	for(int y = 0; y < yAxis; y++){
		for(int x = 0; x < xAxis; x++){
			if(isAlive(x, y)){
				if(numNeigh(x, y) < 2 || numNeigh(x, y) > 3){
					golBoard[x][y].alive = 0;
					golBoard[x][y].rect.setFillColor(Color::White);
                }
			}
			else if(!isAlive(x, y)){
				if(numNeigh(x, y) == 3){
					golBoard[x][y].alive = 1;
					golBoard[x][y].rect.setFillColor(Color::Green);
                }
			}
		}
	}
}
