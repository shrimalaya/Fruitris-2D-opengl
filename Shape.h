//
//  Shape.h
//  CMPT361 Assignment 1
//
//  Created by Srimalaya Ladha on 2019-09-27.
//  Copyright © 2019 Srimalaya Ladha. All rights reserved.
//

#ifndef Shape_h
#define Shape_h

#include<GL/glut.h>
#include<string>
#include<cstring>
#include "time.h"
#include<cstdlib>
#include<stdio.h>

using namespace std;

#define GL_SILENCE_DEPRECATION

class Shape{
private:
    int  x_position;
    int  y_position=360;
    int  angle;
    
    string letter;
    int color[5] = {0, 0, 0, 0, 0};                    //1= Purple, 2= Red, 3= Yellow, 4= Green, 5= Orange
    int boxes[4][4];
    int grid[20][10];
    
public:
    Shape();
    void init();
            
    string randLetter(void);                           //Generate random shape for tetris
    void randTile(void);                               //Generate a random color for tetris
    void x_pos();                                      //Randomly assign a x coordinate
    void obj_angle();                                  //Initialize a random angle
                    
    void draw_box(int x, int y, int color);            //Draw one box for given (x,y) and color
    void drawShape(void);                              //Draw the tetris
    void drawGrid(void);                               //Draw the grid along with any fallen tetris
                    
    void rotateI();                                    //Separate case for the rotation of I instead of using a 5x5 matrix to store its data
    void rotate();                                     //Rotate function
    void move_down();                                  //move down
    void move_left();                                  //move left
    void move_right();                                 //move right

    bool collision_down();                             //Check for collision with bottom
    bool collision_left();                             //Check for collision with left
    bool collision_right();                            //Check for collision with right

    void update();                                     //Update the current grid
    void restart();                                    //Restart when 'r' is pressed
    void check_horizontal();                           //Check for horizontal patterns of 3 or more
    void check_vertical();                             //Check for vertical pattern of 3 or more successive tiles of same color
    void check_right_diagonal();                       //Check for right diagonal pattern of 3 or more successive tiles of same color
    void check_left_diagonal();                        //Check for left diagonal pattern of 3 or more successive tiles of same color
    bool screen_fill();                                //Check if the screen is full
};

Shape::Shape()
{
    srand(time(0));
    x_pos();                //Initialize random x position
    randTile();             //Random color
    letter=randLetter();    //Random shape for the tetris
    obj_angle();            //Random angle
    //Initialize grid to be empty
    for(int i=0; i<10; i++)
        for(int j=0; j<20; j++)
            grid[j][i] = 0;
}

void Shape::init()
{
    x_pos();                //Initialize random x position
    y_position = 360;
    randTile();             //Random color
    letter=randLetter();    //Random shape for the tetris
    obj_angle();            //Random angle
    return;
}

//Generate a random letter to give shape to the tetris.
//Assign the color data to each box in the shape in sequence of {a, b, c, d} in tiles
//Assign the value coordinates of the boxes of shape to 4x4 matrix 'boxes[4][4]'
string Shape::randLetter(void)
{
    int temp = rand()%6 +1; //7 shapes in total
    if(temp == 1) {
        int boxes_I[4][4] = {{0, 0, color[3], 0},{0, 0, color[2], 0},{0, 0, color[1], 0},{0, 0, color[0], 0}};
        memcpy(boxes, boxes_I, 4*4*sizeof(int));
        return "I";     //I
    }
    else if(temp == 2) {
        int boxes_S[4][4] = {{0, 0, 0, 0},{0, 0, color[2], color[3]},{0, color[0], color[1], 0},{0, 0, 0, 0}};
        memcpy(boxes, boxes_S, 4*4*sizeof(int));
        return "S";     //S
    }
    else if(temp == 3) {
        int boxes_L[4][4] = {{0, 0, color[3], 0},{0, 0, color[2], 0},{0, 0, color[1], color[0]},{0, 0, 0, 0}};
        memcpy(boxes, boxes_L, 4*4*sizeof(int));
        return "L";     //L
    }
    else if(temp==4){
        int boxes_T[4][4] = {{0, 0, 0, 0},{0, color[0], color[2], color[3]},{0, 0, color[1], 0},{0, 0, 0, 0}};
        memcpy(boxes, boxes_T, 4*4*sizeof(int));
        return "T";     //T
    }
    else if(temp == 5) {
        int boxes_J[4][4] = {{0, 0, color[3], 0},{0, 0, color[2], 0},{0, color[0], color[1], 0},{0, 0, 0, 0}};
        memcpy(boxes, boxes_J, 4*4*sizeof(int));
        return "J";     //Inverted L
    }
    else{
        int boxes_Z[4][4] = {{0, 0, 0, 0},{0, color[3], color[2], 0},{0, 0, color[1], color[0]},{0, 0, 0, 0}};
        memcpy(boxes, boxes_Z, 4*4*sizeof(int));
        return "Z";     //Inverted S
    }
}

//Generate random color for 4 blocks
void Shape::randTile(void)
{
    for(int i=0; i<4; i++)
    {
        int temp = rand()%5+1;                              //1 = Purple, 2 = Red, 3 = Yellow, 4 = Green, 5 = Orange
        color[i] = temp;                                     //color data for the grid
    }
    return;
}

//Random x position coordinate
void Shape::x_pos()
{
    x_position = (rand()%7+2)*20;
    return;
}

//Random angle
void Shape::obj_angle()
{
    angle = (rand()%5)*90;
    if(letter=="I")                                            //Separate angle generation for I because of only two possible orientation changes
    {
        angle = (rand()%2 + 3)*90;                             //Angle either 0 or 270 degrees
        if(angle==270)                                         //Rotate clockwise
        {
            int temp[4][4];
            
            for(int i=0; i<4; i++)
                for(int j=0; j<4; j++)
                    temp[i][j] = boxes[i][j];
            
            for(int i=0; i<4; i++)
                for(int j=0; j<4; j++)
                    boxes[j-1][3-i] = temp[i][j];
            boxes[3][2]=0;
            return;
        }
        else if (angle==360)        //360 = 0 in coordinate system
        {
            angle=0;
            return;
        }
    }
    
    //Rotate counter-clockwise according to the given angle
    for(int i=0; i<angle/90; i++)
    {
        int temp[4][4];
        
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                temp[i][j] = boxes[i][j];
        
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                boxes[3-j][i+1] = temp[i][j];
    }
    return;
}

//Draw 1 box at a time according to the given positon (x,y) and color data from boxes[4][4]
void Shape::draw_box(int x, int y, int color)
{
    if(color==1)                                                //Purple
        glColor3f(145.0/255, 30.0/255, 180.0/255);
    else if(color==2)                                           //Red
        glColor3f(230.0/255, 25.0/255, 75.0/255);
    else if(color == 3)                                         //Yellow
        glColor3f(1.0,1.0, 25.0/255);
    else if(color == 4)                                         //Green
        glColor3f(60.0/255, 180.0/255, 75.0/255);
    else                                                        //Orange
        glColor3f(245.0/255, 130.0/255, 49.0/255);
    
    glBegin(GL_POLYGON);                                        //Draw a solid square for any given origin
        glVertex2f(x+ 0, y+ 0);
        glVertex2f(x+ 0, y+20);
        glVertex2f(x+20, y+20);
        glVertex2f(x+20, y+ 0);
    glEnd();
    
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_LINE_LOOP);                                      //Draw an outline for the given solid
        glVertex2f(x+ 0, y+ 0);
        glVertex2f(x+ 0, y+20);
        glVertex2f(x+20, y+20);
        glVertex2f(x+20, y+ 0);
    glEnd();
    
    return;
}

void Shape::drawShape(void)
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            if(boxes[i][j]!=0)                                  //Draw the shape according to the color data in **boxes
                draw_box(x_position+((j-2)*20), y_position - ((i-1)*20), boxes[i][j]);
    
    return;
}

void Shape::drawGrid(void)
{
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_LINES);  //Draw a 20x10 grid
        for(int i=0; i<10; i++)
        {
            glVertex2i(i*20, 0);
            glVertex2i(i*20, 400);
            glVertex2i(0, i*20);
            glVertex2i(400, i*20);
            glVertex2i(0, (i+10)*20);
            glVertex2i(400, (i+10)*20);
        }
    glEnd();
    
    //now update the grid to store the already fallen blocks along with their individual color
    for(int j=0; j<20; j++)
        for(int i=0; i<10; i++)
            if(grid[j][i]!=0)
                draw_box(i*20, (19-j)*20, grid[j][i]);
}

void Shape::rotateI()                                           //Separate case for I since only two types of rotations possible 0->270 and 270->0
{
    if(angle==0)                                                //Rotate clockwise
    {
        int temp[4][4];
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                temp[i][j] = boxes[i][j];
        
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                boxes[j-1][3-i] = temp[i][j];
        boxes[3][2]=0;
        if(collision_right())
        {
            memcpy(boxes, temp, 4*4*sizeof(int));
            return;
        }
        angle = 270;
        return;
    }
    else if(angle == 270)                                       //Rotate normally (counter-clockwise)
    {
        int temp[4][4];
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                temp[i][j] = boxes[i][j];
        
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                boxes[3-j][i+1] = temp[i][j];
        if(collision_down())
        {
            memcpy(boxes, temp, 4*4*sizeof(int));
            return;
        }
        angle = 0;
        return;
    }
}

void Shape::rotate()                                            //rotate 90 degrees counter-clockwise
{
    if(letter=="I")                                             //Check for separate case of I
    {
        rotateI();
        return;
    }
    //Continue standard operation
    if(angle==360 || angle==0)                                  //set angle to 0 if block make one full rotation of 360 degrees
        angle = 0;
    
    int temp[4][4];
    
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            temp[i][j] = boxes[i][j];
    
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            boxes[3-j][i+1] = temp[i][j];
    
    // Check for collision after rotation and
    // go back to original if collision exists
    
    int left = 0;                                              //count the number of times left or right to avoid over-shifting blocks
    if(collision_left()==0)
    {
        left++;
        move_left();
    }
    if(collision_right())
    {
        memcpy(boxes, temp, 4*4*sizeof(int));                   //revert back to the original orientation since collision detected
        if(left>0)
            move_right();
        return;
    }
    if(left>0)
        move_right();                                           //Take use of "counting the moves" to avoid shifting

    int right=0;
    if(collision_right()==0)
    {
        right++;
        move_right();
    }
    if(collision_left())
    {
        memcpy(boxes, temp, 4*4*sizeof(int));                   //revert back to the original orientation since collision detected
        if(right>0)
            move_left();
        return;
    }
    if(right>0)
        move_left();
    
    y_position+=20;
    //move_down();
    angle+=90;
    return;
}
void Shape::move_down()                                         //Move down
{
    if(collision_down()==1) {                                   //Check for collision with either window or another block
        update();                                               //If collision detected, stop and store the current grid data
        init();                                                 //Initialize new Shape
        return;
    }
    y_position-=20;                                             //if no collision, move down by one row (20 units)
    return;
}
void Shape::move_left()                                         //Move left
{
    if(collision_left()==1)                                     //Check for collision with either window or another block
        return;
    
    x_position-=20;                                             //if no collision, move left by one column (20 units)
    return;
}

void Shape::move_right()                                        //Move right
{
    if(collision_right()==1)                                    //Check for collision with either window or another block
        return;
    
    x_position +=20;                                            //Move right by one block if no collision detected
    return;
}

bool Shape::collision_down()                                    //Check for collision from bottom
{
    for(int i=3; i>=0; i--)
        for(int j=0; j<4; j++)
            if(boxes[i][j]!=0)
            {
                int x1 = x_position/20-2+j;
                int y1 = 19-y_position/20+i;                    //Check the entire next row from bottom of the Shape
                if(grid[y1][x1]!=0||y1>19)                      //Collision from another block or window detected
                    return 1;
            }
    return 0;
}

bool Shape::collision_left()                                    //check for Collision from the left side
{
    for(int i=3; i>=0; i--)
        for(int j=0; j<4; j++)
            if(boxes[i][j]!=0)
            {
                int x1 = x_position/20-2+j;
                int y1 = 19-y_position/20+i;
                if(grid[y1-1][x1-1]!=0 || x1-1<0)               //Check the entire column on the left
                    return 1;                                   //Collision from another block or window detected
            }
    return 0;
}

bool Shape::collision_right()                                   //Check for collision from the right side
{
    for(int i=3; i>=0; i--)
        for(int j=0; j<4; j++)
            if(boxes[i][j]!=0)
            {
                int x1 = x_position/20-2+j;
                int y1 = 19-y_position/20+i;                    //Check the entire column on the right
                if(grid[y1-1][x1+1]!=0 || x1+1>9)               //Collision from another block or window detected
                    return true;
            }
    return false;
}

void Shape::update()                                            //update the integer value of the position og the shape on the grid
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            if(boxes[i][j]!=0)
                grid[19-((y_position/20)+1)+i][(x_position/20)-2+j] = boxes[i][j];
    
    return;
}

void Shape::restart()                                           //If 'r' is toggled, restart the game and clear the entire grid
{
    for(int i=0; i<10; i++)
        for(int j=0; j<20; j++)
            grid[j][i]=0;                                       //Clear grid data
    init();                                                     //Re-initialize
    return;
}

void Shape::check_horizontal()
{
    int data=0;
    
    for(int j=19; j>=2; j--)
    {
        int count=0;                                            //Count number of same colored tiles
        int zeros=0;                                            //Count number of zeros
        data=grid[j][0];
        for(int i=0; i<10; i++)
        {
            if(data==0) {
                zeros++;
                data = grid[j][i];
                count = 1;
            }
            else if(data==grid[j][i])
                count++;
            else if(data!=grid[j][i])
            {
                data = grid[j][i];
                count=1;
            }
            
            if(count>2) {
                for(count=2; count>=0; count--)
                    for(int k=j; k>=3; k--)
                        grid[k][i-count]=grid[k-1][i-count];
            }
        }
        if(zeros==0 || zeros==10)                               //If the entire row if filled, remove the row and
            for(int k=0; k<10; k++)                             //  move down each row above
                for(int l=j; l>=3; l--)
                    grid[l][k]=grid[l-1][k];
    }
    return;
}

void Shape::check_vertical()
{
    int data=0;
    
    for(int i=0; i<10; i++)
    {
        int count=0;                                            //Count the number of same colored tiles
        data=grid[19][i];
        for(int j=19; j>=2; j--)
        {
            if(data==0) {
                data = grid[j][i];
                count=1;
            }
            else if(data==grid[j][i])
                count++;
            else if(data!=grid[j][i]){
                data = grid[j][i];
                count=1;
            }
            
            if(count>2) {
                for(int k=j+count-1; k>=4; k--)                 //If 3 tiles of same color are encountered, remove those tiles
                    grid[k][i]=grid[k-count][i];                //Shift all the tiles above them down by 3 blocks
                count=0;
            }
        }
    }
    return;
}

void Shape::check_right_diagonal()
{
    int data=0;
    //check right diagonal
    for(int j=19; j>=2; j--)
    {
        int count=0;
        data = grid[j][0];
        for(int i=0; i+2<10; i++)
        {
            if(data==0)
            {
                data=grid[j][i+1];
                count=0;
            }
            else if(data==grid[j][i])
            {
                for(int k=0; k<3; k++)
                {
                    if(data==grid[j-k][i+k])
                        count++;
                    else {
                        count=0;
                        break;
                    }
                }
                if(count<3)
                {
                    data = grid[j][i+1];
                    count = 0;
                }
            }
            if(count>2)
                for(count=2; count>=0; count--)
                    for(int k=j; k>=4; k--)
                        grid[k-count][i+count]=grid[k-count-1][i+count];
        }
    }
}

void Shape::check_left_diagonal() {
    int data=0;
    //check left diagonal
    for(int j=19; j>=3; j--)
    {
        int count=0;
        data = grid[j][2];
        for(int i=2; i<10; i++)
        {
            if(data==0)
            {
                data=grid[j][i+1];
                count=0;
            }
            else if(data==grid[j][i])
            {
                for(int k=0; k<3; k++)
                {
                    if(data==grid[j-k][i-k]) {
                        count++;
                    }
                    else {
                        count=0;
                        break;
                    }
                }
                if(count<3)
                {
                    data = grid[j][i+1];
                    count = 0;
                }
            }
            if(count>2)
                for(int m=count-1; m>=0; m--)
                    for(int k=j; k>=4; k--)
                        grid[k-m][i-m]=grid[k-m-1][i-m];
        }
    }
}

bool Shape::screen_fill()                                                   //If the screen if full, quit the game
{
    for(int i=0; i<10; i++)
        if(grid[1][i]!=0)
            return true;
    
    return false;
}


#endif /* Shape_h */
