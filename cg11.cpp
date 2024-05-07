#include <iostream>
#include <GL/glut.h>


using namespace std;
int option;

void drawLine(int xx1, int yy1, int xx2, int yy2, int s)
{
	float x, y, dx, dy, length;
	int i, t = 0;

	dx = (xx2 - xx1);
	dy = (yy2 - yy1);

	if (abs(dx)>=abs(dy))
	{
		length = abs(dx);
	}
	else
	{
		length = abs(dy);
	}

	dx =dx / length;
	dy = dy / length;

	x = xx1;
	y = yy1;
	i = 1;

	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();

	while (i <= length)
	{
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
		}
		x = x + dx;
		y = y + dy;
		i++;
	}
}

void display()
{
	glFlush();
}

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
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
			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_LINES);
			glVertex2i(-500.0, 0);
			glVertex2i(500.0, 0);
			glVertex2i(0, -500.0);
			glVertex2i(0, 500.0);
			glEnd();
			pt++;
		}
		else
		{
			if (pt == 1)
			{
				x1 = x;
				y1 = y;
				pt++;
			}
			else if (pt == 2)
			{
				x2 = x;
				y2 = y;
				drawLine(-500 + 2 * x1, 500 - 2 * y1, -500 + 2 * x2,  500 - 2 * y2, option);
				pt = 0;
			}
		}
	}
	glFlush();
}

int main(int argc, char** argv)
{
	cout << "1. Simple Line\n";
	cout << "2. Dotted Line\n";
	cout << "3. Dashed Line\n";
	cout << "4. Solid Line\n";
	cout << "Enter option: ";
	cin >> option;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("DDA Algorithm");
	glutMouseFunc(inputMouse);
	glutKeyboardFunc(inputKeyboard);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
