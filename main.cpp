#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "game.h"
#include<stdlib.h>
#define COLUMNS 40.0
#define ROWS 40.0
#define FPS 10


extern short sDirection;
bool gameOver=false;
int score=0;
void timer_callback(int);
void display_callback();
void reshape_callback(int, int);
void keyboard_callback(int, int, int); //key pressed, baki duita position keyboard press er shomoy
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); //4th value is alpha value
    initGrid(COLUMNS, ROWS);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //GLUT_DOUBLE is used for redraw and swapping buffer
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mahedi");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0, timer_callback, 0); //delay, function pointer, jei integer value ta pass kora hoiche
    glutSpecialFunc(keyboard_callback);
    init();
    glutMainLoop(); //projcessing of all the staff will be started

    return 0;
}

void display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT); //Clearing color buffer
    drawGrid();
    drawSnake();
    drawFood();
    glutSwapBuffers(); //It will swap the buffers, it will display the next frame, whenever the display_callback is called
    if(gameOver)
    {
        char _score[10];
        itoa(score, _score, 10); //converts int to char, first argument is int value score, then destination, then argument is decimal base 10
        char text[50] = "Your Score Is: ";
        strcat(text, _score);
        MessageBox(NULL, text, "Game Over", 0);
        exit(0);
    }
}

void reshape_callback(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); //4 parameters are x, y positions of the Rect. and W & H of the viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //No changes will change from beginning
    //The glOrtho function multiplies the current matrix by an orthographic matrix.
    glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0); //x er left right, y er bottom top, z er near far
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int)
{
    glutPostRedisplay();//display function call korar jonyo use hoy
    glutTimerFunc(1000/FPS, timer_callback, 0); //last parameter ta hocche int value, jeta pass hobe

}

void keyboard_callback(int key, int, int)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(sDirection != DOWN)
        {
            sDirection=UP;
            break;
        }
    case GLUT_KEY_DOWN:
        if(sDirection != UP)
        {
            sDirection=DOWN;
            break;
        }
    case GLUT_KEY_RIGHT:
        if(sDirection != LEFT)
        {
            sDirection=RIGHT;
            break;
        }
    case GLUT_KEY_LEFT:
        if(sDirection != RIGHT)
        {
            sDirection=LEFT;
            break;
        }
    }
}
