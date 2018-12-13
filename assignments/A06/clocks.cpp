/**
*  Course: CMPS 2143 Object Oriented Programming
*  Assignment: A06
*  Purpose: This program is a bouncing timer class.
*  It works exactly like the earlier non-bouncing version,
*  but this one bounces.  Also, it has some extra buttons.
*
*  @author Austin Riddle
*  @version 1.0 11/12/2018
*  @github repo: https://github.com/Preassume/2143-OOP-riddle
*/
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

//A button class to make button implementation easier
class myButton{
    RectangleShape button;
    Font buttonFont;
    Text buttonText;
    Vector2f buttonPos, buttonSize;
    Color releaseColor; //The color of the button while not pressed

public:

    /**
    *  Constructor for myButton. Loads the font and initializes
    *  a few variables to default setting.
    */
    myButton(){

        //Loads the font, or displays an error if it was unable to.
        if(!buttonFont.loadFromFile("Manjari-Regular.otf"))
            cout << "Error loading button font.\n";

        releaseColor = Color::White;
        button.setFillColor(releaseColor);

        buttonText.setColor(Color::Black);
        buttonText.setFont(buttonFont);
    }


    /**
    *  Function initialize
    *   A function which is used to initialize the remaining variables for
    *   the button. This allows you to set the size, text, and position of
    *   the button, all in one function call.
    *
    *  @params {string} text : The string to be displayed on the button
    *  @params {int} TSize : The size of the font
    *  @params {Vector2f} TPos : A pair of coordinates for the text
    *  @params {Vector2f} BSize : A pair of dimensions for the button
    *  @params {Vector2f} BPos : A pair of coordinates for the button
    *  @return void
    */
    void initialize(string text, int TSize, Vector2f TPos, Vector2f BSize, Vector2f BPos){
        //Position of the button
        buttonPos = BPos;
        button.setPosition(BPos);

        //Size of the button
        buttonSize = BSize;
        button.setSize(BSize);

        //Text on the button
        buttonText.setString(text);
        buttonText.setPosition(TPos);
        buttonText.setCharacterSize(TSize);
    }


    /**
    *  Function press
    *   Changes the button's color to indicate that it is being pressed
    *
    *  @return void
    */
    void press(){
        button.setFillColor(Color::Yellow);
    }


    /**
    *  Function release
    *   Reverts the button to its appropriate color to indicate that it
    *   is no longer being pressed.
    *
    *  @return void
    */
    void release(){
        button.setFillColor(releaseColor);
    }


    /**
    *  Function setColor
    *   Allows the color of the button to be changed to anything else
    *
    *  @return void
    */
    void setColor(Color c){
        releaseColor = c;
    }


    /**
    *  Function setString
    *   Allows the text on the button to be changed
    *
    *  @return void
    */
    void setString(string s){
        buttonText.setString(s);
    }


    /**
    *  Function onButton
    *   Checks to see if given coordinates fall within the coordinates of
    *   the button.  Used for checking the mouse coordinates.
    *
    *  @params {Vector2i} position : A pair of coordinates
    *  @return {bool} : Whether the coordinates are on the button
    */
    bool onButton(Vector2i position){
        int x = position.x;
        int y = position.y;
        int endX = buttonPos.x + buttonSize.x;
        int endY = buttonPos.y + buttonSize.y;

        if((x >= buttonPos.x && x <= endX) && (y >= buttonPos.y && y <= endY))
            return true;

        return false;
    }


    /**
    *  Function draw
    *   Draws the button. This is being called by the draw function
    *   in the Counter class so nothing else gets added to main().
    *
    *  @params {RenderWindow} window : The program window
    *  @return void
    */
    void draw(RenderWindow &window){
        window.draw(button);
        window.draw(buttonText);
    }
};

//The primary class containing the bouncing clock
class Counter{
private:
    bool countDown, isPaused, leftButton, keepMoving;
    double pausedSeconds; //Seconds spent while paused
    int speedMult; //Multiplier for how fast the timer will move

    Vector2f clockPos, moveSpeed;
    Clock clock, pausedClock;
    Time elapsed, startTime, endTime, pausedTime;
    Text timerText;
    Font timerFont, buttonFont;
    RectangleShape topBar, background, timerBack;

    myButton moveButton, pauseButton, resetButton, raiseSpeed, lowerSpeed;


    /**
    *  Function isDone
    *   Checks to see if the timer has reached its end
    *
    *  @return {bool} : Whether the timer is done or not
    */
    bool isDone(){
        if(!isPaused){
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
        pauseButton.setString("Resume");
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
        pauseButton.setString("Pause");
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
        pauseButton.setString("Start");

        if(startTime.asSeconds() > endTime.asSeconds())
            timerText.setString(to_string(int(startTime.asSeconds())));

        else
            timerText.setString(to_string(int(startTime.asSeconds())));
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
        if(pauseButton.onButton(position)){
            if(isPaused)
                resume();
            else
                pause();
        }
        else if(resetButton.onButton(position)){
            reset();
        }
        else if(moveButton.onButton(position)){
            if(!keepMoving){
                keepMoving = true;
                moveButton.setColor(Color::White);
            }
            else{
                keepMoving = false;
                moveButton.setColor(Color(180, 180, 180));
            }
        }
        else if(raiseSpeed.onButton(position)){
            if(speedMult < 20)
                speedMult++;
            else
                speedMult = 20;

            updateSpeed();
        }
        else if(lowerSpeed.onButton(position)){
            if(speedMult > 1)
                speedMult--;
            else
                speedMult = 1;

            updateSpeed();
        }
    }


    /**
    *  Function updateSpeed
    *   Updates the speed of the timer.  This is used to change the speed
    *   without having to wait for it to bounce off of the walls.
    *
    *  @return void
    */
    void updateSpeed(){
        if(moveSpeed.x > 0) //If the speed is positive, keep it positive
            moveSpeed.x = 0.01 * speedMult;
        else //Otherwise, it should be negative
            moveSpeed.x = -0.01 * speedMult;

        if(moveSpeed.y > 0)
            moveSpeed.y = 0.01 * speedMult;
        else
            moveSpeed.y = -0.01 * speedMult;
    }


    /**
    *  Function moveTimer
    *   Controls the movement of the timer. It will also bounce the timer off
    *   of the window boundaries (or whatever boundary is passed in.)
    *   Called in the draw function.
    *
    *  @params {Vector2u} winSize : Size of the window or boundary
    *  @return void
    */
    void moveTimer(Vector2u winSize){
        clockPos = timerText.getPosition();

        if(isPaused && !keepMoving){
            timerText.move(0, 0); //Stops the timer
            timerBack.move(0, 0);
        }
        else{
            //Checks the clock's coordinates to see if it should bounce
            if(clockPos.x > winSize.x - 82)
                moveSpeed.x = -0.01 * speedMult;

            else if(clockPos.x < 12)
                moveSpeed.x = 0.01 * speedMult;


            if(clockPos.y > winSize.y - 72)
                moveSpeed.y = -0.01 * speedMult;

            else if(clockPos.y < 82) //Makes sure the clock bounces off the top bar
                moveSpeed.y = 0.01 * speedMult;

            timerText.move(moveSpeed);
            timerBack.move(moveSpeed);
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
        speedMult = 4;
        moveSpeed.x = 0.01 * speedMult;
        moveSpeed.y = 0.01 * speedMult;
        keepMoving = true;

        //Loads the font, or displays an error if it was unable to.
        if(!timerFont.loadFromFile("Segment7Standard.otf"))
            cout << "Error loading timer font.\n";

        //Bar at the top
        topBar.setPosition(0, 0);
        topBar.setFillColor(Color(80, 80, 80));
        topBar.setSize(Vector2f(700, 80));

        //Background of the window
        background.setPosition(0, 80);
        background.setFillColor(Color(20, 20, 20));
        background.setSize(Vector2f(700, 400));

        //Text used for the timer itself
        timerText.setFont(timerFont);
        timerText.setCharacterSize(60);
        timerText.setString(to_string(int(start)));
        timerText.setColor(Color(255, 0, 0));
        timerText.setPosition(10, 140);

        //Background of the timer
        timerBack.setPosition(0, 140);
        timerBack.setFillColor(Color(20, 20, 20));
        timerBack.setOutlineColor(Color(110, 110, 110));
        timerBack.setOutlineThickness(2);
        timerBack.setSize(Vector2f(90, 70));

        //The buttons
        pauseButton.initialize("Start", 30, Vector2f(80, 20), Vector2f(230, 60), Vector2f(10, 10));
        resetButton.initialize("Reset", 30, Vector2f(260, 20), Vector2f(100, 60), Vector2f(250, 10));
        moveButton.initialize("Move while paused", 30, Vector2f(370, 20), Vector2f(275, 60), Vector2f(360, 10));
        raiseSpeed.initialize("+", 30, Vector2f(660, 0), Vector2f(45, 25), Vector2f(645, 10));
        lowerSpeed.initialize("-", 30, Vector2f(660, 35), Vector2f(45, 25), Vector2f(645, 45));

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

        moveTimer(window.getSize());

        //Draw the SFML objects
        window.draw(background);
        window.draw(timerBack);
        window.draw(topBar);
        window.draw(timerText);

        resetButton.draw(window);
        pauseButton.draw(window);
        moveButton.draw(window);
        raiseSpeed.draw(window);
        lowerSpeed.draw(window);

        if(isDone()) //Close window once the timer is done
            window.close();

        if(Mouse::isButtonPressed(Mouse::Left)){
            leftButton = true;

            //If the left button is pressed while the mouse is on a button,
            //then make the button yellow.
            if(pauseButton.onButton(Mouse::getPosition(window))){
                pauseButton.press();
            }
            else if(resetButton.onButton(Mouse::getPosition(window))){
                resetButton.press();
            }
            else if(moveButton.onButton(Mouse::getPosition(window))){
                moveButton.press();
            }
            else if(raiseSpeed.onButton(Mouse::getPosition(window))){
                raiseSpeed.press();
            }
            else if(lowerSpeed.onButton(Mouse::getPosition(window))){
                lowerSpeed.press();
            }
            else{
                resetButton.release();
                pauseButton.release();
                moveButton.release();
                raiseSpeed.release();
                lowerSpeed.release();
            }

        }

        //Checks for when the mouse is released after being pressed.
        if(!Mouse::isButtonPressed(Mouse::Left) && leftButton == true){
            leftButton = false;
            getClick(Mouse::getPosition(window));

            moveButton.release();
            resetButton.release();
            pauseButton.release();
            raiseSpeed.release();
            lowerSpeed.release();
        }
    }


    /**
    *  Function setColor
    *   Allows the color of the timer to be changed
    *
    *  @params {Color} c : The desired color
    *  @return void
    */
    void setColor(Color c){
        timerText.setColor(c);
    }


    /**
    *  Function setSize
    *   Allows the size of the timer's font to be changed
    *
    *  @params {int} s : The desired font size
    *  @return void
    */
    void setFontSize(int s){
        timerText.setCharacterSize(s);
    }


    /**
    *  Function setBackgroundColor
    *   Allows the color of the window background to be changed
    *
    *  @params {Color} c : The desired color
    *  @return void
    */
    void setBackgroundColor(Color c){
        background.setFillColor(c);
    }


    /**
    *  Function setTimerBackColor
    *   Allows the color of the timer background to be changed
    *
    *  @params {Color} c : The desired color
    *  @return void
    */
    void setTimerBackColor(Color c){
        timerBack.setFillColor(c);
    }

    /**
    *  Function setTimerOutlineColor
    *   Allows the color of the timer outline to be changed
    *
    *  @params {Color} c : The desired color
    *  @return void
    */
    void setTimerOutlineColor(Color c){
        timerBack.setOutlineColor(c);
    }

    /**
    *  Function setPosition
    *   Allows the position of the timer to be changed
    *
    *  @params {int} x : The x coordinate
    *  @params {int} y : The y coordinate
    *  @return void
    */
    void setPosition(int x, int y){
        timerText.setPosition(Vector2f(x, y));
        timerBack.setPosition(Vector2f(x - 10, y));
    }
};


int main(){
    RenderWindow window(VideoMode(700, 480), "The even better most amazing timer of all time");

    Counter timer(11, 0);
    timer.setBackgroundColor(Color(0, 0, 0));
    timer.setTimerBackColor(Color(0, 0, 0));
    timer.setTimerOutlineColor(Color(0, 255, 0));
    timer.setColor(Color(0, 255, 0));
    timer.setPosition(500, 300);

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
