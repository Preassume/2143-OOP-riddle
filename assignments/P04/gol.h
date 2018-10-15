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
using namespace sf;

/**
 * tile : A single instance of a cell in a Game of Life array
 * @Extends:
 *   sf::Drawable
 * @Data-Elements:
 *     RectangleShape rect;  // sfml rectangle type
 *     bool alive;           // is cell alive or not
 *     int liveNeighbors     // number of living neighbors
 * @Methods:
 *     void setTilePos(int, int)
 */
struct tile{
	bool alive;
	int liveNeighbors;

    RectangleShape rect;
	int Width;
	int Height;


    /**
    *  Constructor for tile. Initializes with default values and color.
    */
	tile();

    /**
    *  Function setTilePos
    *   Positions this one tile to desired coordinates
    *
    *  @param {int} x : Desired x coordinate
    *  @param {int} y : Desired y coordinate
    *  @return void
    */
	void setTilePos(int, int);
};

/**
 * board : A 2D array of tiles with several methods to manipulate them
 * @Extends:
 *   sf::Drawable
 * @Data-Elements:
 *     tile **golBoard  //The 2D array of tiles
 *     int xAxis        //The width of the board
 *     int yAxis        //The height of the board
 *     int frameRate    //How frequently the board will be updated/printed
 *     RenderWindow window  //(SFML) The window we will be printing to
 * @Methods:
 *     board(int, int, int)
 *     void startGame(std::string, char*, std::string)
 *     void makeBoard(std::ifstream&)
 *     void positionTiles()
 *     void outputBoard(std::ofstream&)
 *     bool isAlive(int, int)
 *     int numNeigh(int, int)
 *     bool onBoard(int, int)
 *     void updateTile(int, int)
 *     void drawBoard()
 *     void updateBoard()
 *     void getNext()
 */
struct board{
	tile **golBoard;
	int xAxis;
	int yAxis;
	int frameRate;
	RenderWindow window;

    /**
    *  Constructor for board.  Sets frameRate, window width, and window height.
    *
    *  @param {int} w : Width of window
    *  @param {int} h : Height of window
    *  @param {int} fr : Frequency of drawing/updating the board
    */
	board(int, int, int);

public:
    /**
    *  Function startGame
    *   Starts and runs the game.  Handles calling of all other methods.
    *
    *  @param {string} iFilename : Filename for the input file
    *  @param {char*} runs : How many iterations the game will run
    *  @param {string} oFilename : Filename for the output file
    *  @return void
    */
	void startGame(std::string, char*, std::string);

private:

    /**
    *  Function makeBoard
    *   Builds the board.
    *
    *  @param {ifstream&} ifile : The input file
    *  @return void
    */
	void makeBoard(std::ifstream&);

    /**
    *  Function positionTiles
    *   Positions all of the tiles on the board to their proper location.
    *
    *  @return void
    */
	void positionTiles();

	/**
    *  outputBoard
    *   Saves an iteration of the board to a text file.
    *
    *  @param {ifstream&} ofile : The output file
    *  @return void
    */
	void outputBoard(std::ofstream&);

	/**
    *  Function isAlive
    *   Used for ease of syntax. Returns the 'alive' variable from within
    *   a tile at given coordinates.
    *
    *  @param {int} x : The x coordinate of the desired tile
    *  @param {int} y : The y coordinate of the desired tile
    *  @return {bool} : Whether the tile is alive or not
    */
	bool isAlive(int, int);

	/**
    *  Function numNeigh
    *   Used for ease of syntax. Returns the 'liveNeighbors' variable from
    *   within a tile at given coordinates.
    *
    *  @param {int} x : The x coordinate of the desired tile
    *  @param {int} y : The y coordinate of the desired tile
    *  @return {int} : Number of living neighbors
    */
	int numNeigh(int, int);


	/**
    *  Function onBoard
    *   Checks if given coordinates are within the board's dimensions.
    *
    *  @param {int} x : The desired x coordinate to check
    *  @param {int} y : The desired y coordinate to check
    *  @return {bool} : Whether the coordinates are on the board or not
    */
	bool onBoard(int, int);

	/**
    *  Function updateTile
    *   Checks how many living neighbors a tile has, and stores that number
    *   into the tile's 'numNeighbor' variable.
    *
    *  @param {int} x : The desired x coordinate to check
    *  @param {int} y : The desired x coordinate to check
    *  @return void
    */
	void updateTile(int, int);


	/**
    *  Function drawBoard
    *   Draws the board using SFML.
    *
    *  @return void
    */
	void drawBoard();


	/**
    *  Function updateBoard
    *   Traverses the entire board, calling the updateTile function for all tiles.
    *   This updates the 'numNeighbors' value for every tile on the board.
    *
    *  @return void
    */
	void updateBoard();


	/**
    *  Function getNext
    *   Updates the 'alive' value and color for every tile on the board.
    *   Used after the updateBoard has been used.
    *
    *  @return void
    */
	void getNext();
};
