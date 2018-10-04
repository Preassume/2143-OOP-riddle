/**
*  Course: CMPS 2143 Object Oriented Programming
*  Assignment: A04
*  Purpose: This program draws a grid of squares on the screen.  It has been
*           modified to only print every nth frame, specified by the user
*           upon construction.  Default frame rate is 5.
*
*  @author Austin Riddle
*  @version 1.0 10/5/2018
*  @github repo: https://github.com/Preassume/2143-OOP-riddle
*/
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

struct golCell {
  bool isAlive;
  int neighborCount;
  RectangleShape Rect;
  int Width;
  int Height;

  golCell(){
      Width = 10;
      Height = 10;
      Rect.setSize(sf::Vector2f(Width, Height));
      Rect.setFillColor(Color::Green);
      Rect.setOutlineColor(Color::Black);
      Rect.setOutlineThickness(1);
  }

  void setCellPos(int x,int y){
      Rect.setPosition(x*Width, y*Height);
  }

};

struct gameOfLife{
    int frameCount = 0;
    int frameRate = 5; //A default value for frameRate.
    int Width;
    int Height;
    RenderWindow Window;
    golCell** World;

    gameOfLife(int width,int height) {
        Width = width;
        Height = height;
        Window.create(VideoMode(Width, Height), "Game of Life");

        World = new golCell*[height];

        for(int i=0;i<height;i++){
            World[i] = new golCell[width];
            for(int j=0;j<width;j++){
                World[i][j].setCellPos(i,j);
            }
        }
    }

    gameOfLife(int width, int height, int rate) {
        frameRate = rate; //Lets the user specify upon declaration

        Width = width;
        Height = height;
        Window.create(VideoMode(Width, Height), "Game of Life");

        World = new golCell*[height];

        for(int i=0;i<height;i++){
            World[i] = new golCell[width];
            for(int j=0;j<width;j++){
                World[i][j].setCellPos(i,j);
            }
        }
    }

    void drawWorld(){
        //std::cout << "drawing... " << frameCount << ' ' << frameRate << '\n';
        Window.clear();
        for(int i=0;i<Height;i++){
            for(int j=0;j<Width;j++){
                Window.draw(World[i][j].Rect);
            }
        }
        Window.display();
    }
};



int main(){

    gameOfLife Gol(1000, 1000, 20);

    while (Gol.Window.isOpen())
    {
        Event event;
        while (Gol.Window.pollEvent(event))
        {
            Gol.frameCount++; //Keep track of how many frames have happened

            //Only draws the world once per specified ammount
            if((Gol.frameCount % Gol.frameRate) == 0){
                Gol.drawWorld();
            }

            if (event.type == Event::Closed)
                Gol.Window.close();
        }


    }

    return 0;
}
