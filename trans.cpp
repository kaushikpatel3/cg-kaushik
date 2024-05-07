#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace std;
// ALL TRANSFORMATION DONE SUCCESSFULLY !
GLfloat house[3][9] = {
    {50.0, 50.0, 125.0, 200.0, 200.0, 100.0, 100.0, 150.0, 150.0},
    {50.0, 200.0, 300.0, 200.0, 50.0, 50.0, 100.0, 100.0, 50.0},
    {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}
};

GLfloat t_mat[3][3] = {{0}};

GLfloat result[3][9] = {{0}};

GLfloat theta;

int option, h = 0, k = 0;

GLfloat sx, sy, tx, ty, shx,shy; // Changed data type to GLfloat for scaling factors and translation

void multiply() {
    int i, j, l;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 9; j++) {
            result[i][j] = 0;
            for (l = 0; l < 3; l++) {
                result[i][j] += t_mat[i][l] * house[l][j];
            }
        }
    }
}

void translate() {
    t_mat[0][0] = 1;
    t_mat[0][1] = 0;
    t_mat[0][2] = tx;
    t_mat[1][0] = 0;
    t_mat[1][1] = 1;
    t_mat[1][2] = ty;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}

void scale() {
    // Modify scaling matrix to scale about fixed point (h, k)
    t_mat[0][0] = sx;
    t_mat[0][1] = 0;
    t_mat[0][2] = (1 - sx) * h;
    t_mat[1][0] = 0;
    t_mat[1][1] = sy;
    t_mat[1][2] = (1 - sy) * k;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}

void rotate() {
    GLfloat m, n;
    m = -h * (cos(theta) - 1) + k * (sin(theta));
    n = -k * (cos(theta) - 1) - h * (sin(theta));
    t_mat[0][0] = cos(theta);
    t_mat[0][1] = -sin(theta);
    t_mat[0][2] = m;
    t_mat[1][0] = sin(theta);
    t_mat[1][1] = cos(theta);
    t_mat[1][2] = n;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}

void reflectionx() {
    t_mat[0][0] = 1;
    t_mat[0][1] = 0;
    t_mat[0][2] = 0;
    t_mat[1][0] = 0;
    t_mat[1][1] = -1;
    t_mat[1][2] = 0;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}

void reflectiony() {
    t_mat[0][0] = -1;
    t_mat[0][1] = 0;
    t_mat[0][2] = 0;
    t_mat[1][0] = 0;
    t_mat[1][1] = 1;
    t_mat[1][2] = 0;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}

void reflectiono() {
    t_mat[0][0] = -1;
    t_mat[0][1] = 0;
    t_mat[0][2] = 0;
    t_mat[1][0] = 0;
    t_mat[1][1] = -1;
    t_mat[1][2] = 0;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}

void reflectionyx() {
    t_mat[0][0] = 0;
    t_mat[0][1] = 1;
    t_mat[0][2] = 0;
    t_mat[1][0] = 1;
    t_mat[1][1] = 0;
    t_mat[1][2] = 0;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}

void reflectionynx() {
    t_mat[0][0] = 0;
    t_mat[0][1] = -1;
    t_mat[0][2] = 0;
    t_mat[1][0] = -1;
    t_mat[1][1] = 0;
    t_mat[1][2] = 0;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}

void shearX() {
    // Shearing in x-direction
    // (x', y') = (x + k * y, y)
    // Here, k is the shear factor

    t_mat[0][0] = 1;
    t_mat[0][1] = shx;
    t_mat[0][2] = 0;
    t_mat[1][0] = 0;
    t_mat[1][1] = 1;
    t_mat[1][2] = 0;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}

void shearY() {
    // Shearing in y-direction
    // (x', y') = (x, x * k + y)
    // Here, k is the shear factor
   
    t_mat[0][0] = 1;
    t_mat[0][1] = 0;
    t_mat[0][2] = 0;
    t_mat[1][0] = shy;
    t_mat[1][1] = 1;
    t_mat[1][2] = 0;
    t_mat[2][0] = 0;
    t_mat[2][1] = 0;
    t_mat[2][2] = 1;
    multiply();
}

void drawhouse(GLfloat house[3][9]) {
     // Set drawing color to black
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 9; i++) {
        glVertex2f(house[0][i], house[1][i]);
    }
    glEnd();
    
}

void menu(int choice) {
    option = choice;
}

void inputMouse(int button, int state, int x, int y) {
    static int n,pt = 0;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (pt == 0) {
            glColor3f(0.0, 0.0, 0.0);// Draw original house
            drawhouse(house);
            pt++;
        } else {
            // Apply transformation based on selected option
            switch (option) {
                case 1:
                    cout << "Enter translation about x: ";
                    cin >> tx;
                    cout << "Enter translation about y: ";
                    cin >> ty;
                   translate();
                    break;
                case 2:
                    cout<<"Choose 1.Uniform Scaling 2.Differential Scaling ";
                    cin>>n;
                    if (n==1)
                    {
                    	cout<<"Enter scaling factor: ";
                        cin>>sx;
                        sy=sx;
                    }
                    else
                    {	
                    cout << "Enter scaling about x: ";
                    cin >> sx;
                    cout << "Enter scaling about y: ";
                    cin >> sy;
                    }
                   /*  cout << "Enter x coordinate of fixed point: ";
                    cin >> h;
                    cout << "Enter y coordinate of fixed point: ";
                    cin >> k;*/
                    scale();
                    break; 
                case 3:
                    cout << "Enter rotation angle: ";
                    cin >> theta;
                    cout<< "Choose 1.anticlockwise 2.clockwise ";
                    cin>>n;
                    
                    theta = theta * (3.142 / 180.0);
                    h = 0;
                    k = 0;
                    if (n==2)
                    {
                    	theta= -1*theta;	
                    }
                    rotate();
                    break;
                case 4:
                    cout << "Enter rotation angle: ";
                    cin >> theta;
                    theta = theta * (3.142 / 180.0);
                    cout << "Enter x coordinate of arbitrary point: ";
                    cin >> h;
                    cout << "Enter y coordinate of arbitrary point: ";
                    cin >> k;
                    rotate();
                    break;
                case 5:
                    reflectiony();
                    break;
                case 6:
                    reflectionx();
                    break;
                case 7:
                    reflectiono();
                    break;
                case 8:
                    reflectionynx();
                    break;
                case 9:
                    reflectionyx();
                    break;
                case 10: // Shear in x-direction
                 cout << "Enter the shear factor in x-direction: ";
   		 cin >> shx;
                    shearX();
                    break;
                case 11: // Shear in y-direction
                    cout << "Enter the shear factor in y-direction: ";
   		    cin >> shy;
                    shearY();
                    break;
                    
                 case 12:
                    
                    cout << "Enter scaling about x: ";
                    cin >> sx;
                    cout << "Enter scaling about y: ";
                    cin >> sy;
                    cout << "Enter x coordinate of fixed point: ";
                    cin >> h;
                    cout << "Enter y coordinate of fixed point: ";
                    cin >> k;
                    scale();
                    break; 
            }
            // Draw transformed house
           glColor3f(0.0, 1.0, 0.0);
            drawhouse(result);
            pt = 0;
        }
    }
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(-500.0, 0);
    glVertex2i(500.0, 0);
    glVertex2i(0, -500.0);
    glVertex2i(0, 500.0);
    glEnd();
    drawhouse(house);
    glFlush();
}

void init() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
    glColor3f(0.0, 0.0, 0.0); // Set drawing color to black
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("House Transformation");
    init();
    glutDisplayFunc(display);
    glutCreateMenu(menu);
    glutAddMenuEntry("Translation", 1);
    glutAddMenuEntry("Scaling", 2);
    glutAddMenuEntry("Rotation", 3);
    glutAddMenuEntry("Rotation about given point", 4);
    glutAddMenuEntry("Reflection about Y Axis", 5);
    glutAddMenuEntry("Reflection about X Axis", 6);
    glutAddMenuEntry("Reflection about origin", 7);
    glutAddMenuEntry("Reflection about y=-x", 8);
    glutAddMenuEntry("Reflection about y=x", 9);
    glutAddMenuEntry("Shear in x-direction", 10);
    glutAddMenuEntry("Shear in y-direction", 11);
    glutAddMenuEntry("Scaling about fixed point", 12);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(inputMouse);
    glutMainLoop();
    return 0;
}

