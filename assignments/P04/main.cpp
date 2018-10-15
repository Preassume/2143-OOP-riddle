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

int main(int argc, char** argv){
	board gol1(500, 400, 10000);
	gol1.startGame(argv[1], argv[2], argv[3]);
}
