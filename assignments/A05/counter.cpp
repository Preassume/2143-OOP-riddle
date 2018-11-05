/**
*  Course: CMPS 2143 Object Oriented Programming
*  Assignment: A05
*  Purpose: This program is a timer class. Contains a timer which can count
*  up or down, as well as buttons to pause or reset the timer.
*  Fractions of seconds can be passed in as decimals (ex: 2.46 seconds).
*  This will work, but the timer only displays whole seconds.
*
*  @author Austin Riddle
*  @version 1.0 11/5/2018
*  @github repo: https://github.com/Preassume/2143-OOP-riddle
*/
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

class Counter{
private:
    bool countDown, isPaused, leftButton;
    double pausedSeconds; //Seconds spent while paused

    Clock clock, pausedClock;
    Time elapsed, startTime, endTime, pausedTime;
    Text timerText, pauseText, resetText;
    Font timerFont, buttonFont;
    RectangleShape pauseButton, resetButton;

    /**
    *  Function isDone
    *   Checks to see if the timer has reached its end
    *
    *  @return {bool} : Whether the timer is done or not
    */
    bool isDone(){
        getElapsed();
        if(countDown){
            if(elapsed.asSeconds() <= endTime.asSeconds())
                return true;
            else
                return false;
        }
        else{
            if(elapsed.asSeconds() >= endTime.asSeconds())
                return true;
            else
                return false;
        }
    }


    /**
    *  Function getElapsed
    *   Calculate how much time has passed since the start of the timer.
    *   If the timer is counting down, elapsed will contain the starting
    *   time with the elapsed time subtracted from it.
    *   Time spent paused is subtracted from the elapsed time.
    *
    *  @return void
    */
    void getElapsed(){
        if(countDown)
            elapsed = startTime - (clock.getElapsedTime() - pausedTime);
        else
            elapsed = (clock.getElapsedTime() - pausedTime) + startTime;
    }


    /**
    *  Function update
    *   Calls the getElapsed function to get the current time value.
    *   Updates the timer's text to have the current time.
    *
    *  @return void
    */
    void update(){
        if(!isPaused){
            if(!isDone())
                timerText.setString(to_string(int(elapsed.asSeconds())));

            else
                timerText.setString(to_string(int(elapsed.asSeconds())));
        }
    }


    /**
    *  Function pause
    *   Pauses the timer
    *
    *  @return void
    */
    void pause(){
        pauseText.setString("Resume");
        isPaused = true;
        pausedClock.restart();
    }


    /**
    *  Function resume
    *   Resumes the timer
    *
    *  @return void
    */
    void resume(){
        pauseText.setString("Pause");
        isPaused = false;
        pausedTime += pausedClock.getElapsedTime();
    }


    /**
    *  Function reset
    *   Resets the timer to its original state
    *
    *  @return void
    */
    void reset(){
        clock.restart();
        pausedClock.restart();
        pausedTime = Time::Zero;
        isPaused = true;
        pauseText.setString("Start");

        if(startTime.asSeconds() > endTime.asSeconds())
            timerText.setString(to_string(int(startTime.asSeconds())));

        else
            timerText.setString(to_string(int(startTime.asSeconds())));
    }


    /**
    *  Function onReset
    *   Checks to see if given coordinates fall within the coordinates of
    *   the reset button.  Used for checking the mouse coordinates.
    *
    *  @params {Vector2i} position : A pair of coordinates
    *  @return {bool} : Whether the coordinates are on the reset button
    */
    bool onReset(Vector2i position){
        int x = position.x;
        int y = position.y;

        if((x >= 250 && x <= 350) && (y >= 10 && y <= 70))
            return true;

        return false;
    }


    /**
    *  Function onPause
    *   Checks to see if given coordinates fall within the coordinates of
    *   the pause button.  Used for checking the mouse coordinates.
    *
    *  @params {Vector2i} position : A pair of coordinates
    *  @return {bool} : Whether the coordinates are on the pause button
    */
    bool onPause(Vector2i position){
        int x = position.x;
        int y = position.y;

        if((x >= 10 && x <= 240) && (y >= 10 && y <= 70))
            return true;

        return false;
    }


    /**
    *  Function getClick
    *   Checks a pair of coordinates to see it is located on either the
    *   pause or reset button.  If so, it calls the appropriate functions.
    *
    *  @params {Vector2i} position : A pair of coordinates
    *  @return void
    */
    void getClick(Vector2i position){
        if(onPause(position)){
            if(isPaused)
                resume();
            else
                pause();
        }
        else if(onReset(position)){
            reset();
        }
    }

public:

    /**
    *  Constructor for Counter.  Sets the starting and stopping time.
    *  Also defines all of the SFML objects.
    *  Accepts doubles instead of integers, so fractions of a second
    *  can be used if desired.  The timer will only display whole seconds.
    *
    *  @param {int} start : Starting time for the timer
    *  @param {int} stop : Stopping time for the timer
    */
    Counter(double start, double stop){
        leftButton = false; //keeps track of the left mouse button being pressed
        isPaused = true;
        pausedSeconds = 0; //How many seconds have been spent paused
        startTime = seconds(start);
        endTime = seconds(stop);

        //Loads the fonts, or displays an error if it was unable to.
        if(!timerFont.loadFromFile("Segment7Standard.otf"))
            cout << "Error loading timer font.\n";

        if(!buttonFont.loadFromFile("Manjari-Regular.otf"))
            cout << "Error loading button font.\n";

        //Text used for the timer itself
        timerText.setFont(timerFont);
        timerText.setCharacterSize(60);
        timerText.setString(to_string(int(start)));
        timerText.setColor(Color::Red);
        timerText.setPosition(10, 110);

        //Text on the pause button
        pauseText.setFont(buttonFont);
        pauseText.setCharacterSize(30);
        pauseText.setString("Start");
        pauseText.setColor(Color::Black);
        pauseText.setPosition(80, 20);

        //The pause button
        pauseButton.setSize(Vector2f(230, 60));
        pauseButton.setPosition(10, 10);
        pauseButton.setFillColor(Color::White);

        //Text on the reset button
        resetText.setFont(buttonFont);
        resetText.setCharacterSize(30);
        resetText.setString("Reset");
        resetText.setColor(Color::Black);
        resetText.setPosition(260, 20);

        //The reset button
        resetButton.setSize(Vector2f(100, 60));
        resetButton.setPosition(250, 10);
        resetButton.setFillColor(Color::White);

        //Check if the timer should count up or down
        if(start > stop)
            countDown = true;
        else
            countDown = false;
    }


    /**
    *  Function drawClock
    *   Draws the clock.  Should be placed inside of event loop.
    *   Also checks for mouse clicks on the pause and reset buttons.
    *
    *  @params {RenderWindow} window : The program window
    *  @return void
    */
    void drawClock(RenderWindow &window){
        update(); //Update the timer's text before drawing

        //Draw the SFML objects
        window.draw(timerText);
        window.draw(resetButton);
        window.draw(resetText);
        window.draw(pauseButton);
        window.draw(pauseText);

        if(isDone()) //Close window once the timer is done
            window.close();

        if(Mouse::isButtonPressed(Mouse::Left)){
            leftButton = true;

            //If the left button is pressed while the mouse is on a button,
            //then make the button yellow.
            if(onPause(Mouse::getPosition(window))){
                pauseButton.setFillColor(Color::Yellow);
                resetButton.setFillColor(Color::White);
            }
            else if(onReset(Mouse::getPosition(window))){
                pauseButton.setFillColor(Color::White);
                resetButton.setFillColor(Color::Yellow);
            }
            else{
                pauseButton.setFillColor(Color::White);
                resetButton.setFillColor(Color::White);
            }

        }

        //Checks for when the mouse is released after being pressed.
        if(!Mouse::isButtonPressed(Mouse::Left) && leftButton == true){
            leftButton = false;
            getClick(Mouse::getPosition(window));

            pauseButton.setFillColor(Color::White);
            resetButton.setFillColor(Color::White);
        }
    }
};


int main(){
    RenderWindow window(VideoMode(360, 200), "The most amazing timer in all of history");

    Counter timer(5, 0);

    while (window.isOpen()){
        Event event;

        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        timer.drawClock(window);
        window.display();
    }
    return 0;
}
