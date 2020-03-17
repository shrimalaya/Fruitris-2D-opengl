//Play.h works as the application runner for Shape object

#include "Shape.h"

class Play{
private:
    Shape shape;
    bool paused=0;
public:
    void init(void);                                                //Initialize the sequence of operations when game is run
    void keyboard(int key, int x, int y);                           //Define the keyboard functions for moving and rotating
    void normal_Keyboard(unsigned char key, int x, int y);          //Keyboard functions for other keys
    bool isPaused();                                                //Check if the game is paused
};

void Play::init()                                                   //Follow the sequence of operations for every frame
{
    shape.check_horizontal();
    shape.check_vertical();
    shape.check_right_diagonal();
    shape.check_left_diagonal();
    shape.drawGrid();
    shape.drawShape();
    shape.move_down();
    
    if(shape.screen_fill()==true)                                   //Quit the game if screen is full
        exit(EXIT_SUCCESS);
}

void Play::keyboard(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:                                           //Rotate when up arrow key is pressed
            shape.rotate();
            break;
        case GLUT_KEY_DOWN:                                         //Move down when down key is pressed
            shape.move_down();
            break;
        case GLUT_KEY_LEFT:                                         //Move left is left key is pressed
            shape.move_left();
            break;
        case GLUT_KEY_RIGHT:                                        //Move right if right key is pressed
            shape.move_right();
            break;
    }
}

void Play::normal_Keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'p':                                                   //Press 'p' for pause
            if(isPaused()==0)
                paused = 1;
            else
                paused = 0;
            break;
        case 'q':                                                   //Press 'q' to quit the game
            exit(EXIT_SUCCESS);
            break;
        case 'r':                                                   //Press 'r' while playing to reset and restart the game
            shape.restart();
            break;
    }
}

bool Play::isPaused()
{
    return paused;                                                  //Return the paused status of the game
}
