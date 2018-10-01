/**
*  Course: CMPS 2143 Object Oriented Programming
*  Assignment: P03
*  Purpose: This is a test SFML program to ensure that SFML
*           is in working order.
*
*  @author Austin Riddle
*  @version 1.0 10/1/2018
*  @github repo: https://github.com/Preassume/2143-OOP-riddle
*/

#include <SFML/Graphics.hpp>

int main() {
 sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
 sf::CircleShape shape(100.f);
 shape.setFillColor(sf::Color::Green);
 while (window.isOpen()) {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();
  }
  window.clear();
  window.draw(shape);
  window.display();
}
  return 0;
}
