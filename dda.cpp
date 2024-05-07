#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;
int option =1;

void drawLine(int x1, int y1, int x2, int y2,int s);

void menu(int index) {
    if (index == 1)
        option=1;
    else if (index == 2)
        option=2;
    else if (index == 3)
        option=3;
    else if (index == 4)
        option=4;
    else if (index == 5)
       option=5;
    else
        option=1;
}



void setpixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2,int s) {
    float x, y, dx, dy, length;
    int i;
    int t=0;

    dx = (x2 - x1);
    dy = (y2 - y1);

    if (abs(dx) >= abs(dy)) {
        length = abs(dx);
    } else {
        length = abs(dy);
    }

    dx = dx / length;
    dy = dy / length;

    x = x1;
    y = y1;

    glBegin(GL_POINTS);
    glVertex2i(round(x), round(y));
    glEnd();

    for (i = 1; i <= length; i++) {
    
		switch (s)
		{
		case 1:
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
			break;

		case 2:
			if (i % 20 == 0)
			{
				glBegin(GL_POINTS);
				glVertex2i(x, y);
				glEnd();
				break;
			}
		case 3:
			if (i % 15 == 0)
			{
				if (t == 0)
				{
					t = 1;
				}
				else
				{
					t = 0;
				}
			}
			if (t == 0)
			{
				glBegin(GL_POINTS);
				glVertex2i(x, y);
				glEnd();
			}
			break;
		case 4:
			glPointSize(3.0);
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
			break;
		case 5:
			glBegin(GL_POLYGON);  //boat base
			glColor3f(0,1,0);
			glVertex2i(-150,0);
			glVertex2i(150,0);
			glVertex2i(250,100);
			glVertex2i(-250,100);
			glEnd();
		
			glBegin(GL_TRIANGLES); //boat top
			glColor3f(0,0,1);
			glVertex2i(0,100);
			glVertex2i(0,300);
			glVertex2i(150,100);
			glEnd();
			 glColor3f(1, 1, 1);
			break;
			
			
		}
        x = x + dx;
        y = y + dy;

      
    }
}


void inputKeyboard(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 27:
		exit(0);
	}
}

void inputMouse(int button, int state, int x, int y)
{
	static int x1, x2, y1, y2;
	static int pt = 0;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
			if (pt == 0)
			{
				x1 = x;
				y1 = y;
				pt++;
			}
			else if (pt == 1)
			{
				x2 = x;
				y2 = y;
				drawLine(-500 + 2 * x1, 500 - 2 * y1, -500 + 2 * x2,  500 - 2 * y2, option);
				pt = 0;
			}
		
	}
	glFlush();
}
void display() {
    for (int i = -500; i <= 500; i++) {
        setpixel(i, 0);
        setpixel(0, i);
    }
    glFlush();
}

void init() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("DDA Algorithm");
        glutMouseFunc(inputMouse);
	glutKeyboardFunc(inputKeyboard);
    init();

    glutCreateMenu(menu);
    glutAddMenuEntry("SimpleLine", 1);
    glutAddMenuEntry("DashedLine", 2);
    glutAddMenuEntry("DottedLine", 3);
    glutAddMenuEntry("SolidLine", 4);
    glutAddMenuEntry("BoatObject", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}


