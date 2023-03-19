/*********
   CTIS164 - Template Source Program
----------
STUDENT :irem gökçe dönmez
SECTION :02
HOMEWORK: CTIS-164-212-Homework-1
----------
PROBLEMS:
----------
ADDITIONAL FEATURES: 
stars move randomly
left click changes color
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h> // add to generate random number

#define WINDOW_WIDTH  1300
#define WINDOW_HEIGHT 700

#define TIMER_PERIOD  10 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

#define FIRST 0
#define CLICK 1


#define MAN 2
#define AUTO 3


#define NOTSET 4
#define UP 5
#define DOWN 6
#define LEFT 7
#define RIGHT 8

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

int xU = 0, yU = 0;
int xS = 0, yS = 0;
int status = FIRST;
int mode = MAN;
int keypress = NOTSET;
int r = 100, g = 100, b = 100;


//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

//
// To display onto window using OpenGL commands
//


void ufo()
{
    glColor3f(1, 1, 1);
    circle(0+xU, 0+yU, 50);

    glColor3f(0.10, 0.33, 1);
    circle(-10+xU, 20+yU, 20);
    circle(10+xU, 20+yU, 20);
    glRectf(-10+xU,0+yU,10+xU,40+yU);


    glColor3ub(r, g, b);
    glRectf(-80+xU, -20+yU, 80+xU, 20+yU);
    circle(-80+xU, 0 + yU, 20);
    circle(80 + xU, 0 + yU, 20);
    
    glBegin(GL_TRIANGLES);
    glVertex2f(-30 + xU, -40 + yU);
    glVertex2f(-40 + xU, -30 + yU);
    glVertex2f(-45 + xU, -60 + yU);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(30 + xU, -40 + yU);
    glVertex2f(40 + xU, -30 + yU);
    glVertex2f(45 + xU, -60 + yU);
    glEnd();

    glRectf(-2 + xU, 50 + yU, 2 + xU, 65 + yU);

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(100 + xU, 0 + yU);
    glVertex2f(-100 + xU, 0 + yU);
    glEnd();

    

    glColor3ub(220, 220, 40);
    int i;
    for (i = -80; i <= 80; i = i + 20)
        circle(i + xU, 10 + yU, 3);
    circle(0 + xU, 62 + yU, 3);
}
void stars()
{
    int i;
    srand(time(0));
    
        for (i = 0; i < 200; i++)
        {   
            xS = rand() % (650 - (-650) + 1) + (-650);
            yS = rand() % (350 - (-350) + 1) + (-350);
            glColor3ub(255, 255, 255);
            glBegin(GL_LINES);
            // line 1
            glVertex2f(0 + xS, 5 + yS);
            glVertex2f(0 + xS, -5 + yS);
            //line2
            glVertex2f(-5 + xS, 0 + yS);
            glVertex2f(5 + xS, 0 + yS);
            //line3
            glVertex2f(-3 + xS, 4 + yS);
            glVertex2f(4 + xS, -3 + yS);
            //line4
            glVertex2f(-4 + xS, -3 + yS);
            glVertex2f(3 + xS, 4 + yS);
            glEnd();
        }
    
}
void background()
{
   
    stars();

    //planet1 saturn
    glColor3ub(137, 86, 20);
    circle(-380, 120, 20);
    circle(-300, 120, 20);

    glColor3ub(255, 145, 0);
    circle(-340, 120, 40);
 
    glColor3ub(137, 86, 20);
    glRectf(-380, 100, -300, 110);

    //planet 2 uranus
    glColor3ub(115, 215, 211);
    circle(300, -100, 50);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(250, -100);
    glVertex2f(340, -70);

    glVertex2f(350, -100);
    glVertex2f(270, -140);
    glEnd();

    //planet 3 sun
    glColor3ub(255, 255, 0);
    circle(640, 340, 100);
}

void display() {
    //
    // clear window to black
    //
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    background();
    glColor3f(0, 1, 1); 
    vprint(-610, -330, GLUT_BITMAP_8_BY_13, "Irem Gokce Donmez 22101982");
    vprint((winWidth / 2) - 300, -(winHeight / 2) + 80, GLUT_BITMAP_8_BY_13, "Up, Down, Left, Right Keys: Move Ufo");
    vprint((winWidth / 2) - 300, -(winHeight / 2) + 65, GLUT_BITMAP_8_BY_13, "Left Click : Change Color");
    vprint((winWidth / 2) - 300, -(winHeight / 2) + 50, GLUT_BITMAP_8_BY_13, "Right Click: Change Location");
    vprint((winWidth / 2) - 300, -(winHeight / 2) + 35, GLUT_BITMAP_8_BY_13, "F1: Change Mode");
    vprint((winWidth / 2) - 300, -(winHeight / 2) + 20, GLUT_BITMAP_8_BY_13, "Esc key: Exit");

    glColor3ub(255, 0, 0);
    if (mode == MAN)
        vprint((winWidth / 2) - 300, -(winHeight / 2) + 95, GLUT_BITMAP_8_BY_13, "Current Mode = Manuel");
    else
        vprint((winWidth / 2) - 300, -(winHeight / 2) + 95, GLUT_BITMAP_8_BY_13, "Current Mode = Auto");

    if (keypress == UP)
        vprint((winWidth / 2) - 300, -(winHeight / 2) + 110, GLUT_BITMAP_8_BY_13, "Direction: UP");
    else if (keypress == DOWN)
        vprint((winWidth / 2) - 300, -(winHeight / 2) + 110, GLUT_BITMAP_8_BY_13, "Direction: DOWN");
    else if (keypress == LEFT)
        vprint((winWidth / 2) - 300, -(winHeight / 2) + 110, GLUT_BITMAP_8_BY_13, "Direction: LEFT");
    else if (keypress == RIGHT)
        vprint((winWidth / 2) - 300, -(winHeight / 2) + 110, GLUT_BITMAP_8_BY_13, "Direction: RIGHT");
    else
        vprint((winWidth / 2) - 300, -(winHeight / 2) + 110, GLUT_BITMAP_8_BY_13, "Direction: NOTSET");

    if(status == FIRST)
        vprint((winWidth / 2) - 300, -(winHeight / 2) + 125, GLUT_BITMAP_8_BY_13, "Click To Create UFO");

    if(status==CLICK)
        ufo();
    
   
    glutSwapBuffers();
}

/*glBegin(GL_POLYGON); //background color
    glColor3ub(245, 114, 210);
    glVertex2f(-500, -400);
    glVertex2f(500, -400);
    glColor3f(0, 0, 0);
    glVertex2f(500, 600);
    glVertex2f(-500, 600);
    glEnd();
*/

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);
    
    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}


// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT

void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = true;break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }

    if (key == GLUT_KEY_F1)
    { 
        if (mode == MAN)
            mode = AUTO;
        else
            mode = MAN;
    }
    
    

    if (mode == MAN)
    {
        switch (key) {
        case GLUT_KEY_UP:
        {
            if (yU < winHeight / 2)
                yU=yU+5;
        }
        break;
        case GLUT_KEY_DOWN:
        {
            if (yU > -winHeight / 2)
                yU=yU-5;
        }
        break;
        case GLUT_KEY_LEFT:
        {
            if (xU > -winWidth / 2)
                xU=xU-5;
        }break;
        case GLUT_KEY_RIGHT:
        {
            if (xU < winWidth / 2)
                xU=xU+5;
        }
        break;
        }

    }
    
    
    if (key == GLUT_KEY_UP)
        keypress = UP;
    else if (key == GLUT_KEY_DOWN)
        keypress = DOWN;
    else if (key == GLUT_KEY_LEFT)
        keypress = LEFT;
    else if (key == GLUT_KEY_RIGHT)
        keypress = RIGHT;
    else
        keypress = NOTSET;
    
    // to refresh the window it calls display() function
    glutPostRedisplay();
}


//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
    // Write your codes here.
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;
    }

    if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN)
        if (status == FIRST)
        {
            status = CLICK;
            xU = x - winWidth / 2;
            yU = winHeight / 2 - y;
        }
        else
        {
            xU = x - winWidth / 2;
            yU = winHeight / 2 - y;
        }


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.
    if (mode == AUTO)
    {
        if (keypress == UP)
            if (yU < winHeight / 2)
                yU++;
            else
                keypress = DOWN;
        if (keypress == DOWN)
            if (yU > -winHeight / 2)
                yU--;
            else
                keypress = UP;
        if (keypress == RIGHT)
            if (xU < winWidth / 2)
                xU++;
            else
                keypress = LEFT;
        if (keypress == LEFT)
            if (xU > -winWidth / 2)
                xU--;
            else
                keypress = RIGHT;
            
    }


    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("164homework1");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}