#include "Play.h"

Play game;

void init(void) {
    glClearColor(1, 1, 1, 1.0);                                  //Clear color to default value
    glMatrixMode(GL_PROJECTION);                                 //Set to projection mode
    glLoadIdentity();                                            //Load the identity matrix
    gluOrtho2D(0.0, 200, 0.0, 400);                              //Set the window's dimensions
    glMatrixMode(GL_MODELVIEW);                                  //Set to MODEL and VIEWPORT mode
    glDisable(GL_DEPTH_TEST);
}
        
void keyboard(int key, int x, int y)                             //Initialize the keyboard function in main.cpp
{
    game.keyboard(key, x, y);
    return;
}
        
void normal_Keyboard(unsigned char key, int x, int y)            //Initialize the normal_keyboard function in main.cpp
{
    game.normal_Keyboard(key, x, y);
    return;
}
        
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    game.init();                                                 //Initialize the game sequence from Play.h
    glutSwapBuffers();
}

void timer(int)
{
    glutTimerFunc(1000/4, timer, 0);                            // blocks fall down with the speed of 4 fps
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(normal_Keyboard);
    if(game.isPaused()==0)                                      //Run the game sequence only when not is paused state
    {
        display();                                              //Call to display is used instead of glutPostRedisplay() in order to facilitate the pause feature
    }
    
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);                //Double buffer display
    glutInitWindowPosition(50,50);                              //Position of the window on the screen
    glutInitWindowSize(400, 800);                               //Window size with aspect ratio 1:2
    glutCreateWindow("FRUITris");
    
    init();
    glutDisplayFunc(display);                                   //Call to the display funciton
    glutTimerFunc(0, timer, 0);                                 //Run the timer function
    glutMainLoop();
}
