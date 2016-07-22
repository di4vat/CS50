//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// Paddle dimension
#define PADDLEWIDTH 60
#define PADDLEHEIGHT 10

// Brick dimension
#define BRICKWIDTH 36
#define BRICKHEIGHT 10

// Ball dimension
#define BALLWIDTH 20
#define BALLHEIGHT 20

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // starts game
    waitForClick();
    
    double velocityX = drand48(); 
    double velocityY = 4.0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        // Scoreboard
        updateScoreboard(window, label, points);
       
        // move ball
        move(ball, velocityX, velocityY);

        pause(10);
        
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure Paddle move on the x axis only
                double x = getX(event) - getWidth(paddle) / 2;
                double y = HEIGHT - 60;
                setLocation(paddle, x, y);
            }
         } 
             
        GObject object = detectCollision(window, ball);
       
        if (object != NULL)
        {
            // If the ball hits the paddle.
            if (object == paddle)
            {
                velocityY = -velocityY;
            }
           
                /**
                *  If ball hits a block remove block, add a point,
                *  decrement count and bounce.
                */
            else if (strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                points++;
                bricks--;
                velocityY = -velocityY;
                               
            }
        }
        
        // If the ball hits the right wall.
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocityX = -velocityX;
        }
       
        // If the ball hits the left wall.
        if (getX(ball) <= 0)
        {
            velocityX = -velocityX;
        }
       
        // If the ball hits the top wall.
        if (getY(ball) <= 0)
        {
            velocityY = -velocityY;
        }
       
        // If the ball hits the bottom. Remove a life. Start over.
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            // move ball to start
            setLocation(ball, WIDTH / 2, HEIGHT / 2);
            // move paddle to start
            setLocation(paddle, WIDTH / 2, HEIGHT - 60);
            waitForClick();
        }
       
    }
    
    if (bricks == 0)
    {
        GLabel game_over = newGLabel("YOU WIN!");
        setFont(game_over, "SansSerif-70");
        setColor(game_over, "GREEN");
        add(window, game_over);
        setLocation(game_over, 15, 300);
    }
    if (lives == 0)
    {
        GLabel game_over = newGLabel("YOU LOSE!");
        setFont(game_over, "SansSerif-70");
        setColor(game_over, "RED");
        add(window, game_over);
        setLocation(game_over, 15, 300);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    
    int i, j, y;
    int x = -38;
 
    // instantiate bricks in window, ROWS and COLS represent grid dimensions
    // iterate over columns
    for (j = 0; j < COLS; j++)
    { 
        // create the row of 10 bricks (10 cols)
        x = x + 40;
        y = 40;
        GRect brick = newGRect(x, y, BRICKWIDTH, BRICKHEIGHT);
        add (window, brick);
 
        // set color for initial row of 10 cols
        setColor(brick, "#2D2926");
        setFilled(brick, true);
 
        // create a row of bricks under each col in row (5 rows)   
        for (i = 0; i < ROWS - 1; i++)
        {
            y = y + 12;
            GRect brick = newGRect(x, y, BRICKWIDTH, BRICKHEIGHT);
            add (window, brick);
 
            // set colors for each row individually
            if (i == 0)
            {
                setColor(brick, "#009ACE");
                setFilled(brick, true);
            }
 
            if (i == 1)
            {
                setColor(brick, "#44D62C");
                setFilled(brick, true);
            }
 
            if (i == 2)
            {
                setColor(brick, "#EA27C2");
                setFilled(brick, true);
            }
 
            if (i == 3)
            {
                setColor(brick, "#FF5E00");
                setFilled(brick, true);
            } 
        }
    }
        
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval ball = newGOval(WIDTH / 2, HEIGHT / 2, BALLWIDTH, BALLHEIGHT);
    setColor(ball, "#000000");
    setFilled(ball, true);
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    // creates paddle and center position tobuttom of window
    GRect Paddle = newGRect(WIDTH / 2, HEIGHT - 60, PADDLEWIDTH, PADDLEHEIGHT);
    setColor(Paddle, "#000000" );
    setFilled(Paddle, true);
    add(window, Paddle);
    
    return Paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    // instantiate scoreboard, value is a number (a char*)
    GLabel label = newGLabel (" 0 ");
    add (window, label);
    setLocation(label, 150, 200);
    setFont(label, "SansSerif-70");
 
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
