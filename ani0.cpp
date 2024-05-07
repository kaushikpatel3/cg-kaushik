#include <GL/glut.h>
#include <cmath>

float angle = 135;
float inc = 1.0;

void initialize() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);
}

void plot(int a, int b) {
  //glColor3f(0.0, 0.0, 0.0);
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

void timer(int value) {
    glutPostRedisplay(); // Request a redraw
    glutTimerFunc(50, timer, 0); // Set the next timer
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
     glBegin (GL_LINE_LOOP)   ;
     glPointSize(5);
  glColor3f (0.5,0.3,0.1);
 
  glVertex2i (-125, -25);
  glVertex2i (125, -25);
glVertex2i (125, 200);
  glVertex2i (0, 350);
  glVertex2i (-125,200);
  glEnd ();
  
    glBegin (GL_POLYGON)   ;
  glColor3f (0.25,0.88,0.82);
  glVertex2i (-145,180);
  glVertex2i (20, 360);
glVertex2i (20, 390);
  glVertex2i (-145, 210);
  
  glEnd ();
  
     glBegin (GL_POLYGON)   ;
  glColor3f (0.25,0.88,0.82);
  glVertex2i (145,180);
  glVertex2i (-20, 360);
glVertex2i (-20, 390);
  glVertex2i (145, 210);
  
  glEnd ();
  
     glBegin (GL_POLYGON)   ;
  glColor3f (0.25,0.88,0.82);
  glVertex2i (-145,-25);
  glVertex2i (145, -25);
glVertex2i (145, -50);
  glVertex2i (-145, -50);
  
  glEnd ();
  
   glBegin (GL_POLYGON)   ;
  glColor3f (0.65,0.35,0.15);
  glVertex2i (-125,-50);
  glVertex2i (-125, -75);
glVertex2i (-105, -75);
  glVertex2i (-105, -50);
  
  glEnd ();
  
   glBegin (GL_POLYGON)   ;
  glColor3f (0.65,0.35,0.15);
  glVertex2i (125,-50);
  glVertex2i (125, -75);
glVertex2i (105, -75);
  glVertex2i (105, -50);
  
  glEnd ();
  
    glBegin (GL_LINE_LOOP)   ;
   //  glPointSize(5);
  glColor3f (0.5,0.3,0.1);
 
  glVertex2i (0, 225);
  glVertex2i (-25, 225);
glVertex2i (-25, 275);
glVertex2i (0, 275);
  glVertex2i (0, 225);
  glVertex2i (25,225);
  glVertex2i (25, 275);  
glVertex2i (0, 275);
  glEnd ();
  
  glBegin (GL_LINES); 
  glColor3f (0.5,0.3,0.1);
  glVertex2i (-25, 250);
  glVertex2i (25, 250);
  glEnd ();
    glColor3f(1.0, 0.0, 0.0);
    drawCircle(0, 100, 100);
    drawCircle(0, 100, 60);
   
    // Draw clock numbers
    glPointSize(5);
    glBegin(GL_POINTS);
      glColor3f (0  ,0 ,1);
    for (int i = 1; i <= 12; ++i) {
        float theta = (i * 30 * 3.14159) / 180.0;
        float x = 90 * sin(theta);
        float y = 90 * cos(theta);
        glVertex2f(x, y + 100);
    }
    glEnd();

    if (angle > 225) {
        angle = 225;
        inc = -inc;
    }
    if (angle < 135) {
        angle = 135;
        inc = -inc;
    }
    angle += inc;
    double radian = angle * 3.14 / 180;
    float y2 = 300 * cos((double)radian);
    float x2 = 300 * sin((double)radian);
    drawCircle(x2, y2, 30);
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(0,-50);
    glVertex2f(x2, y2);
    glVertex2f(0, 100);
    glVertex2f(0, 150);
    glVertex2f(0, 100);
    glVertex2f(60, 145);
    glEnd();
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Pendulum Clock");
    initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0); // Start the timer immediately
    glutMainLoop();
    return 0;
}

