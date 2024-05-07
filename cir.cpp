
#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

int xc, yc, x2, y2, option = 1;

void menu(int choice) {
    option = choice;
}

void plot(int a, int b) {
     glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(a, b);
    glEnd();
}

void drawCircle(int h, int k, int r) {
    int x = 0, y = r;
    float d = 3 - 2 * r;

    while (x <= y) {
        if (d <= 0) {
            d = d + 4 * x + 6;
            x++;
        } else {
            d = d + 4 * (x - y) + 10;
            x++;
            y--;
        }

        plot(x + h, y + k);
        plot(-x + h, -y + k);
        plot(y + h, x + k);
        plot(-y + h, -x + k);
        plot(-y + h, x + k);
        plot(y + h, -x + k);
        plot(-x + h, y + k);
        plot(x + h, -y + k);
    }
}

void drawConcentricCircles(int h, int k, int r) {
    while (r <= 500) {
        drawCircle(h, k, r);
        r += 100;
    }
}

void drawSpiral(int hc, int k, int x, int y, int a) {
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 0.0);

    for (int i = 0; i < 10; i++) {
        if (a % 2 == 0) {
            glVertex2i(hc + x, k + y);
            glVertex2i(hc - x, k + y);
            glVertex2i(hc + y, k + x);
            glVertex2i(hc - y, k + x);
        }

        if (a % 2 != 0) {
            glVertex2i(hc + x, k - y);
            glVertex2i(hc - x, k - y);
            glVertex2i(hc + y, k - x);
            glVertex2i(hc - y, k - x);
        }
    }

    glEnd();
    glFlush();
}

void drawOlympicRings(int xc, int yc, int distance) {
    drawCircle(xc, yc, 2 * distance);
    drawCircle(xc + (4.35 * distance), yc, 2 * distance);
    drawCircle(xc + (8.75 * distance), yc, 2 * distance);
    drawCircle(xc + (2.15 * distance), yc - (2.5 * distance), 2 * distance);
    drawCircle(xc + (6.5 * distance), yc - (2.5 * distance), 2 * distance);
}

void Spiral(int r, int hc, int k, int a) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    drawSpiral(hc, k, x, y, a);

    while (y >= x) {
        x++;

        if (d <= 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y = y - 1;
        }

        drawSpiral(hc, k, x, y, a);
    }
}
void object( int h,int k ,int r)
{
	drawCircle(h, k, r); 
	drawCircle(h, k, r/2);
	
	glBegin(GL_LINE_LOOP);
	glVertex2i(h, k+r);
	glVertex2i(h-(0.866025404*r), k-(r/2));
	glVertex2i(h+(0.866025404*r), k-(r/2));
	glEnd();
	
	
			
}
void display() {
   glClear(GL_COLOR_BUFFER_BIT);
    for (int i = -500; i <= 500; i++) {
        plot(i, 0);
        plot(0, i);
    }
    glFlush();
}

void init() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
    glColor3f(0.0, 0.0, 0.0);
}

void inputKeyboard(unsigned char key, int mouseX, int mouseY) {
    switch (key) {
        case 27:
            exit(0);
    }
}

void inputMouse(int button, int state, int x, int y) {
    static int pt = 0;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        if (pt == 0) {
            if (option == 3) {
                int r = 50;
                int hc = 0;
                for (int i = 0; i < 20; i++) {
                    Spiral(r, hc, 0, i);
                    hc += (i % 2 == 0) ? -10 : 10;
                    r += 10;
                }
                pt = 0;
            } else {
                pt++;
            }
        } else {
            if (pt == 1) {
                xc = -250 + x;
                yc = 250 - y;
                pt++;
            } else if (pt == 2) {
                x2 = -250 + x;
                y2 = 250 - y;
                int distance = sqrt((x2 - xc) * (x2 - xc) + (y2 - yc) * (y2 - yc));

                switch (option) {
                    case 1: // Circle
                        drawCircle(xc, yc, distance);
                        break;
                    case 2: // Concentric Circles
                        drawConcentricCircles(xc, yc, distance);
                        break;
                    case 4: // Olympic Rings
                        drawOlympicRings(xc, yc, distance);
                        break;
                        
                     case 5://object
                         object(xc, yc, distance);
                        break;
                }
                pt = 0;
            }
        }
    }

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Shapes Drawing");
    glutMouseFunc(inputMouse);
    glutKeyboardFunc(inputKeyboard);
    init();
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Circle", 1);
    glutAddMenuEntry("Concentric Circles", 2);
    glutAddMenuEntry("Spiral", 3);
    glutAddMenuEntry("Olympic Rings", 4);
    glutAddMenuEntry("Object", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();

    return 0;
}
