#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;
int option =1;

void drawBresenhamLine (int x1, int y1, int x2, int y2,int s);

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
    glColor3f(0.0, 0.0, 0.0); // Set color to black
    glPointSize(1.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}


 void pattern(int x,int y)
 {
 int px = x, py =y, qx = x, qy = y + 200, rx = x + 300, ry = y + 200, tx = x + 300, ty = y;
                  
                    drawBresenhamLine(px, py, qx, qy, 1);
                    drawBresenhamLine(rx, ry, qx, qy, 1);
                    drawBresenhamLine(rx, ry, tx, ty, 1);
                    drawBresenhamLine(px, py, tx, ty, 1);

                    drawBresenhamLine((px + qx) / 2, (py + qy) / 2, (qx + rx) / 2, (qy + ry) / 2, 1);
                    drawBresenhamLine((qx + rx) / 2, (qy + ry) / 2, (rx + tx) / 2, (ry + ty) / 2, 1);
                    drawBresenhamLine((rx + tx) / 2, (ry + ty) / 2, (px + tx) / 2, (py + ty) / 2, 1);
                    drawBresenhamLine((px + tx) / 2, (py + ty) / 2, (px + qx) / 2, (py + qy) / 2, 1);
                     int ux = (px + qx) / 2, uy = (py + qy) / 2, vx = (qx + rx) / 2, vy = (qy + ry) / 2,
                        wx = (rx + tx) / 2, wy = (ry + ty) / 2, xx = (px + tx) / 2, xy = (py + ty) / 2;

                    drawBresenhamLine((ux + vx) / 2, (uy + vy) / 2, (vx + wx) / 2, (vy + wy) / 2, 1);
                    drawBresenhamLine((xx + wx) / 2, (xy + wy) / 2, (vx + wx) / 2, (vy + wy) / 2, 1);
                    drawBresenhamLine((xx + wx) / 2, (xy + wy) / 2, (ux + xx) / 2, (uy + xy) / 2, 1);
                    drawBresenhamLine((ux + vx) / 2, (uy + vy) / 2, (ux + xx) / 2, (uy + xy) / 2, 1);
   }             



void drawBresenhamLine(int x1, int y1, int x2, int y2, int s)
{
    int interchange, err;
    int i = 0, t = 0;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int x = x1;
    int y = y1;

    if (dy > dx)
    {
        swap(dx, dy);
        interchange = 1;
    }
    else
    {
        interchange = 0;
    }
    err = 2 * dy - dx;
while (i < dx)
    {
        if (err >= 0)
        {
            if (interchange == 1)
                x += sx;
            else
                y += sy;
            err -= 2 * dx;
        }

        if (interchange == 1)
            y += sy;
        else
            x += sx;

        err += 2 * dy;
        i++;
        
        switch (s)
        {
        case 1:
            setpixel(x,y);
            break;
	 case 2:
            if (i % 20 == 0)
            {
                setpixel(x,y);
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
                setpixel(x,y);
            }
            break;

        case 4:
            glColor3f(0.0, 0.0, 0.0); // Set color to black
            glPointSize(3.0);
            glBegin(GL_POINTS);
            glVertex2i(x, y);
	    glEnd();
            break;
        case 5:
             pattern( x1, y1);
            break;
         
        }
       
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
				drawBresenhamLine(-500 + 2 * x1, 500 - 2 * y1, -500 + 2 * x2,  500 - 2 * y2, option);
				pt = 0;
			}
		
	}
	glFlush();
}
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
    for (int i = -500; i <= 500; i++) {
        setpixel(i, 0);
        setpixel(0, i);
    }
    glFlush();
}

void init() {
   
    glClearColor(1.0, 1.0, 1.0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham Line Drawing Algorithm");
       
    init();

    glutCreateMenu(menu);
    glutAddMenuEntry("SimpleLine", 1);
    glutAddMenuEntry("DashedLine", 2);
    glutAddMenuEntry("DottedLine", 3);
    glutAddMenuEntry("SolidLine", 4);
    glutAddMenuEntry("Pattern", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
     glutMouseFunc(inputMouse);
	glutKeyboardFunc(inputKeyboard);
    glutMainLoop();

    return 0;
}


