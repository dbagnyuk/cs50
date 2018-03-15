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
#include <spl/ginteractors.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// heigh and width of paddle
#define PADDLE_WIDTH 75
#define PADDLE_HEIGHT 10

// heigh and width of paddle
#define BRICKS_WIDTH 35
#define BRICKS_HEIGHT 10

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboardPoints(GWindow window);
GLabel initScoreboardBricks(GWindow window);
GLabel initScoreboardLives(GWindow window);
GLabel initReadyStringPoints(GWindow window);
GLabel initOverStringPoints(GWindow window);
GLabel initWinStringPoints(GWindow window);
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
    GLabel labelPoints = initScoreboardPoints(window);
    GLabel labelBricks = initScoreboardBricks(window);
    GLabel labelLives = initScoreboardLives(window);
    
    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // initial velocity
    double velocityX = drand48() * 2;
    double velocityY = 2.0;

    // instantiate button
    GButton button = newGButton("Start");
    setActionCommand(button, "click");

    // add button to southern region of window
    addToRegion(window, button, "SOUTH");

    // listen for events
    while (true)
    {
        // instantiate Ready! string, centered in middle of window
        GLabel readyString = initReadyStringPoints(window);


        // wait for event
        GActionEvent event = waitForEvent(ACTION_EVENT);

        // if window was closed
        if (getEventType(event) == WINDOW_CLOSED)
        {
            closeGWindow(window);
            return 0;
        }

        // if action command is "click"
        if (strcmp(getActionCommand(event), "click") == 0)
        {
            removeGWindow(window, readyString);
            break;
        }
    }

    updateScoreboard(window, labelPoints, points);
    updateScoreboard(window, labelBricks, bricks);
    updateScoreboard(window, labelLives, lives);

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        // follow mouse forever
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows top cursor
                double x = getX(event) - getWidth(paddle) / 2;
                double y = getHeight(window) - (getHeight(paddle) * 5);
                
                if (x >= (getWidth(window) - getWidth(paddle)))
                    x = (getWidth(window) - getWidth(paddle));
                if (x <= 0)
                    x = 0;
                
                setLocation(paddle, x, y);
            }
        }

        // move circle along x-axis
        move(ball, velocityX, velocityY);

        // bounce off
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            // bounce off paddle
            if (object == paddle)
            {
                velocityY = -velocityY;
            }
            
            // bounce off bricks        
            else if (strcmp(getType(object), "GRect") == 0)
            {
                // TODO
                removeGWindow(window, object);
                velocityY = -velocityY;
                --bricks;
                ++points;
                updateScoreboard(window, labelPoints, points);
                updateScoreboard(window, labelBricks, bricks);
                // when left no brick end the game
                if (bricks == 0)
                {
                    removeGWindow(window, paddle);
                    removeGWindow(window, ball);
                    GLabel winString = initWinStringPoints(window);
                    //waitForClick();
                }
                // when brake the brick do ball little faster
                velocityY = velocityY * 1.01;
                velocityX = velocityX * 1.01;
            }
        }

        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocityX = -velocityX;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            velocityX = -velocityX;
        }

        // bounce off top edge of window
        else if (getY(ball) <= 0)
        {
            velocityY = -velocityY;
        }

        // bounce off bottom edge of window
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            //velocityY = -velocityY;
            --lives;
            updateScoreboard(window, labelLives, lives);
            removeGWindow(window, ball);
            if (lives > 0)
            {
                ball = initBall(window);
                GLabel readyString = initReadyStringPoints(window);
                waitForClick();
                removeGWindow(window, readyString);
            }
            else if (lives == 0)
            {
                removeGWindow(window, paddle);
                removeGWindow(window, ball);
                GLabel overString = initOverStringPoints(window);
                //waitForClick();
            }
            // when loose the ball do next ball faster
            velocityY = velocityY * 1.15;
            velocityX = velocityX * 1.15;
        }

        // linger before moving again
        pause(10);
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
    // create line of bricks with random colors
    int gap = 4;
    int x = (WIDTH - ((BRICKS_WIDTH * COLS) + ((COLS - 1) * gap))) / 2;
    int y = x, c;
    char color[12];
    
    for  (int i = 0; i < ROWS; ++i)
    {
        c = drand48() * 10;
        switch (c)
        {
            case 0 :
                strcpy(color, "BLUE");
                break;
            case 1 :
                strcpy(color, "GREEN");
                break;
            case 2 :
                strcpy(color, "ORANGE");
                break;
            case 3 :
                strcpy(color, "MAGENTA");
                break;
            case 4 :
                strcpy(color, "RED");
                break;
            case 5 :
                strcpy(color, "CYAN");
                break;
            case 6 :
                strcpy(color, "GRAY");
                break;
            case 7 :
                strcpy(color, "PINK");
                break;
            case 8 :
                strcpy(color, "YELLOW");
                break;
            case 9 :
                strcpy(color, "LIGHT_GRAY");
                break;
        }
        
        for (int j = 0; j < COLS; ++j)
        {
            GRect rect = newGRect(x, y, BRICKS_WIDTH, BRICKS_HEIGHT);
            setFilled(rect, true);
            setColor(rect, color);
            add(window, rect);
            x += BRICKS_WIDTH + gap;        
        }
        y += BRICKS_HEIGHT + gap;
        x = (WIDTH - ((BRICKS_WIDTH * COLS) + ((COLS - 1) * gap))) / 2;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval circle = newGOval((WIDTH / 2) - RADIUS, (HEIGHT / 2) - RADIUS, RADIUS * 2, RADIUS * 2);
    setFilled(circle, true);
    setColor(circle, "MAGENTA");
    add(window, circle);

    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    GRect rect = newGRect((WIDTH / 2) - (PADDLE_WIDTH / 2), HEIGHT - (PADDLE_HEIGHT * 5), PADDLE_WIDTH, PADDLE_HEIGHT);
    setFilled(rect, true);
    setColor(rect, "BLUE");
    add(window, rect);

    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboardPoints(GWindow window)
{
    // TODO
    // instantiate label
    GLabel label = newGLabel(" ");
    setFont(label, "SansSerif-28");
    setColor(label, "GRAY");

    // instantiate sign
    GLabel sign = newGLabel("Score");
    setFont(sign, "SansSerif-14");
    setColor(sign, "GRAY");

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    add(window, label);

    // center sign in window
    double xx = (getWidth(window) - getWidth(sign)) / 2;
    double yy = ((getHeight(window) - getHeight(sign)) / 2) - getHeight(label);
    setLocation(sign, xx, yy);
    add(window, sign);

    return label;
}

GLabel initScoreboardBricks(GWindow window)
{
    // TODO
    // instantiate label
    GLabel label = newGLabel(" ");
    setFont(label, "SansSerif-24");
    setColor(label, "GRAY");
    
    // instantiate sign
    GLabel sign = newGLabel("Bricks");
    setFont(sign, "SansSerif-14");
    setColor(sign, "GRAY");

    // center label in window
    double x = 1;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    add(window, label);
    
    // center sign in window
    double xx = 1;
    double yy = ((getHeight(window) - getHeight(sign)) / 2) - getHeight(label);
    setLocation(sign, xx, yy);
    add(window, sign);

    return label;
}

GLabel initScoreboardLives(GWindow window)
{
    // TODO
    // instantiate label
    GLabel label = newGLabel(" ");
    setFont(label, "SansSerif-24");
    setColor(label, "RED");
    // instantiate sign
    GLabel sign = newGLabel("Lives");
    setFont(sign, "SansSerif-14");
    setColor(sign, "GRAY");

    // center label in window
    double x = (getWidth(window) - getWidth(label) * 2);
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    add(window, label);
    
    // center sign in window
    double xx = (getWidth(window) - getWidth(sign));
    double yy = ((getHeight(window) - getHeight(sign)) / 2) - getHeight(label);
    setLocation(sign, xx, yy);
    add(window, sign);

    return label;
}

// Ready string
GLabel initReadyStringPoints(GWindow window)
{
    // TODO
    // instantiate label
    GLabel label = newGLabel("Ready!");
    setFont(label, "SansSerif-42");
    setColor(label, "GRAY");

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = ((getHeight(window) - getHeight(label)) / 2) - getHeight(label);
    setLocation(label, x, y);
    add(window, label);

    return label;
}

// Game Over string
GLabel initOverStringPoints(GWindow window)
{
    // TODO
    // instantiate label
    GLabel label = newGLabel("Game Over!");
    setFont(label, "SansSerif-42");
    setColor(label, "GRAY");

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = ((getHeight(window) - getHeight(label)) / 2) - getHeight(label);
    setLocation(label, x, y);
    add(window, label);

    return label;
}

// Game Win string
GLabel initWinStringPoints(GWindow window)
{
    // TODO
    // instantiate label
    GLabel label = newGLabel("You WIN!");
    setFont(label, "SansSerif-42");
    setColor(label, "GRAY");

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = ((getHeight(window) - getHeight(label)) / 2) - getHeight(label);
    setLocation(label, x, y);
    add(window, label);

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
//    double x = (getWidth(window) - getWidth(label)) / 2;
//    double y = (getHeight(window) - getHeight(label)) / 2;
//    setLocation(label, x, y);
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
