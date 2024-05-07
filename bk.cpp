#include <bits/stdc++.h> // This header includes all other standard C++ headers
#include <GL/glut.h>      // Header for OpenGL Utility Toolkit
#include <cmath>

using namespace std;

// Class to represent a point
class Point {
public:
    int x, y;
    
    // Function to set x and y coordinates of the point
    void setXY(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

int option;

// Variable to store user's choice
static int POINTSNUM = 0; 

// Number of points selected by the user
static Point points[4]; 

// Array to store selected points

// Initialization function
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.5); // Set clear color to white
    glMatrixMode(GL_PROJECTION);       // Set matrix mode to projection
    glLoadIdentity();                   // Load identity matrix
    gluOrtho2D(0.0, 600.0, 0.0, 480.0); // Set orthographic projection
}

// Function to draw a point
void setPoint(Point p) {
    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
    glFlush();
}

// Function to draw a line between two points
void setLine(Point p1, Point p2) {
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
    glFlush();
}

// Function to calculate a point on Bezier curve at parameter t
Point setBezier(Point p1, Point p2, Point p3, Point p4, double t) {
    Point p;
    double a1 = pow((1 - t), 3);
    double a2 = pow((1 - t), 2) * 3 * t;
    double a3 = 3 * t * t * (1 - t);
    double a4 = t * t * t;
    p.x = a1 * p1.x + a2 * p2.x + a3 * p3.x + a4 * p4.x;
    p.y = a1 * p1.y + a2 * p2.y + a3 * p3.y + a4 * p4.y;
    return p;
}

// Function to draw Bezier curve
void drawBezierCurve() {
    glColor3f(0.0, 1.0, 0.0); // Set color to green
    Point p_current = points[0];
    for (double t = 0.0; t <= 1.0; t += 0.05) {
        Point P = setBezier(points[0], points[1], points[2], points[3], t); // Calculate point on curve
        setLine(p_current, P); // Draw line segment
        p_current = P;
    }
    POINTSNUM = 0; // Reset point count
}

// Function to draw Koch curve
void drawKochCurve(Point p1, Point p2, int depth) {
    if (depth == 0) {
        setLine(p1, p2); // Draw line segment
        return;
    }
    Point p3, p4, p5;
    p3.x = p1.x + (p2.x - p1.x) / 3;
    p3.y = p1.y + (p2.y - p1.y) / 3;
    p5.x = p1.x + 2 * (p2.x - p1.x) / 3;
    p5.y = p1.y + 2 * (p2.y - p1.y) / 3;
    double angle = M_PI / 3;
    p4.x = p3.x + (p5.x - p3.x) * cos(angle) + (p5.y - p3.y) * sin(angle);
    p4.y = p3.y - (p5.x - p3.x) * sin(angle) + (p5.y - p3.y) * cos(angle);
    drawKochCurve(p1, p3, depth - 1);
    drawKochCurve(p3, p4, depth - 1);
    drawKochCurve(p4, p5, depth - 1);
    drawKochCurve(p5, p2, depth - 1);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear color buffer
    glFlush();                    // Flush OpenGL pipeline
}

// Mouse function to handle mouse clicks
void myMouseFunction(int button, int state, int x, int y) {
    int n;
    if (state == GLUT_DOWN) {
        if (option == 1) { // If Bezier Curve is selected
            points[POINTSNUM].setXY(x, 480 - y); // Set point coordinates
            glColor3f(1.0, 0.0, 0.0);
            setPoint(points[POINTSNUM]); // Draw point
            glColor3f(1.0, 0.0, 0.0);
            if (POINTSNUM > 0)
                setLine(points[POINTSNUM - 1], points[POINTSNUM]); // Draw line segment between consecutive points
            if (POINTSNUM == 3)
                drawBezierCurve(); // Draw Bezier curve when four points are selected
            POINTSNUM++; // Increment point count
        } else if (option == 2) { // If Koch Curve is selected
            Point p1, p2;
            p1.setXY(x, 480 - y); // Set start point to mouse click position
            p2.setXY(p1.x + 500, p1.y); // Set end point 500 pixels away horizontally
            glClear(GL_COLOR_BUFFER_BIT); // Clear screen
            glColor3f(1.0, 0.0, 0.0);
            cout<<"\nEnter the number of interation\n";
	    cin>>n;
            drawKochCurve(p1, p2, n); // Draw Koch curve with specified depth
        }
    }
}

// Menu function to handle menu selection
void menu(int choice) {
    option = choice; // Store user's choice
}

// Main function
int main(int argc, char *argv[]) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // Set display mode
    glutInitWindowSize(600, 480); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("Bezier and Koch Curves"); // Create window with title
    init(); // Initialize OpenGL settings
    glutDisplayFunc(display); // Register display callback function
    glutMouseFunc(myMouseFunction); // Register mouse callback function
    glutCreateMenu(menu); // Create menu
    glutAddMenuEntry("Bezier Curve", 1); // Add menu entry for Bezier Curve
    glutAddMenuEntry("Koch Curve", 2); // Add menu entry for Koch Curve
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right mouse button
    glutMainLoop(); // Enter GLUT event processing loop
    return 0;
}

