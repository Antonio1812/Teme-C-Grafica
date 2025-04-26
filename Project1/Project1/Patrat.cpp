/*
Programul afiseaza un patrat pe care il translateaza
pe axa x la apasarea sagetilor stanga, dreapta
*/
#include "glos.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <math.h>

void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(int w, int h);
void CALLBACK MutaStanga(void);
void CALLBACK MutaDreapta(void);
void CALLBACK MutaSus(void);
void CALLBACK MutaJos(void);
void CALLBACK rot_z_up(AUX_EVENTREC);
void CALLBACK rot_z_down(AUX_EVENTREC);
void CALLBACK drawCirclePoints(float, float, float);
void CALLBACK drawCircleLines(float, float, float);
void CALLBACK drawCirclePolygons(float, float, float);
void CALLBACK drawCylinder(float, float);


static GLfloat x = 0;
static GLfloat y = 0;
float angle = 0.0f;

void myinit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}


void CALLBACK MutaStanga(void)
{
    x = x - 10;
}

void CALLBACK MutaDreapta(void)
{
    x = x + 10;
}

void CALLBACK MutaSus(void) {
    y = y + 10;
}

void CALLBACK MutaJos(void) {
    y = y - 10;
}

void CALLBACK rot_z_up(AUX_EVENTREC* event) {


    angle += 5.0f;

}

void CALLBACK rot_z_down(AUX_EVENTREC* event) {
    angle -= 5.0f;

}

void CALLBACK drawCirclePoints(float cx, float cy, float r) {
    glBegin(GL_POINTS);
    for (int i = 0; i < 360; i++) {
        float theta = 2 * 3.14159f * i / 360;
        float x = r * cos(theta);
        float y = r * cos(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void CALLBACK drawCircleLines(float cx, float cy, float r) {
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159f / 180.0f;
        float x = cx + r * cos(theta);
        float y = cy + r * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void CALLBACK drawCirclePolygons(float cx, float cy, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159f / 180.0f;
        float x = cx + r * cos(theta);
        float y = cy + r * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

void CALLBACK drawCylinder(float radius, float height) {
    int numSegments = 360;
    float angleStep = 2 * 3.14159f / numSegments;

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= numSegments; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glVertex3f(x, 0.0f, z);
        glVertex3f(x, height, z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= numSegments; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0f, height, 0.0f);
    for (int i = 0; i <= numSegments; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glVertex3f(x, height, z);
    }
    glEnd();
}



void CALLBACK drawParallelepiped(float radius, float height) {
    float angles[] = { 0, 90, 180, 270 }; // Angles in degrees
    glColor3f(1.0, 0.0, 0.0); // Red color for visibility

    glBegin(GL_QUADS);

    for (int i = 0; i < 4; i++) {
        float angle1 = angles[i] * 3.14159f / 180.0f; // Convert to radians
        float angle2 = angles[(i + 1) % 4] * 3.14159f / 180.0f;

        float x1 = radius * cos(angle1);
        float z1 = radius * sin(angle1);
        float x2 = radius * cos(angle2);
        float z2 = radius * sin(angle2);

        // Define the quad for each side
        glVertex3f(x1, 0.0f, z1); // Bottom left
        glVertex3f(x1, height, z1); // Top left
        glVertex3f(x2, height, z2); // Top right
        glVertex3f(x2, 0.0f, z2); // Bottom right
    }

    glEnd();

    // Draw the top and bottom faces
    glBegin(GL_QUADS);

    // Bottom face
    for (int i = 0; i < 4; i++) {
        float angle = angles[i] * 3.14159f / 180.0f;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glVertex3f(x, 0.0f, z);
    }

    glEnd();

    glBegin(GL_QUADS);

    // Top face
    for (int i = 0; i < 4; i++) {
        float angle = angles[i] * 3.14159f / 180.0f;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glVertex3f(x, height, z);
    }

    glEnd();
}

void CALLBACK drawSphere(float radius) {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_LINE);
    glColor3f(0.0, 0.0, 1.0);  // Culoarea sferei
    gluSphere(quad, radius, 36, 18);
    gluDeleteQuadric(quad);
}


void setupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 0.1, 10.0);  // Field of View, Aspect Ratio, Near & Far Planes
    glMatrixMode(GL_MODELVIEW);
}

void CALLBACK display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(x, y, 0.0);
    glRotatef(angle, 1.0f, 1.0f, 1.0f);


    /*glBegin(GL_QUADS);

        glColor3f (1.0, 0.0, 0.0);
        glVertex2f(0.0,0.0);
        glColor3f (1.0, 1.0, 0.0);
        glVertex2f(150.0,100.0);
        glColor3f (0.0, 0.0, 1.0);
        glVertex2f(150.0,150.0);
        glColor3f (0.0, 1.0, 0.0);
        glVertex2f(100.0,150.0);


    glEnd();*/

    float radius = 50.0;
    int numSegments = 360;
    float height = 50.0;

    // ======= Desenare baza conului =======
    //glBegin(GL_TRIANGLE_FAN);
    //glColor3f(0.0, 0.0, 1.0);
    //glVertex3f(0, 0, 0);  // Centrul bazei
    //for (int i = 0; i <= numSegments; i++) {
    //    float theta = 2.0f * 3.14159f * i / numSegments;
    //    float x = radius * cos(theta);
    //    float z = radius * sin(theta);
    //    glVertex3f(x, 0, z);
    //}
    //glEnd();

    // ======= Desenare mantaua conului =======
    //glBegin(GL_TRIANGLE_FAN);
    //glColor3f(1.0, 0.0, 0.0);
    //glVertex3f(0, height, 0);  // Vârful conului
    //for (int i = 0; i <= numSegments; i++) {
    //    float theta = 2.0f * 3.14159f * i / numSegments;
    //    float x = radius * cos(theta);
    //    float z = radius * sin(theta);
    //    glVertex3f(x, 0, z);
    //}
    //glEnd();
    //glColor3f(1.0, 0.0, 0.0);
    //drawCirclePoints(100, 100, 50);
    //drawCircleLines(100, 100, 50);
    //drawCirclePolygons(100, 100, 50);
    //drawCylinder(radius, height);
    //drawCylinder(radius,height);
    drawSphere(radius);
    glFlush();
}

/*void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;			//transformare anizotropica, forma se modifica functie de forma(dimens) viewportului
    glViewport(0, 0, w, h);	//daca w>h stabilim ca baza inaltime, si stab unit logica de dimens in fct de h(h/320, 320 lungime lat patrat)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-160.0, 160.0, -160.0,
        160.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}*/

void CALLBACK myReshape(int w, int h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-160.0, 160.0, 160.0 * (GLfloat)h / (GLfloat)w,
            -160.0 * (GLfloat)h / (GLfloat)w, -100.0, 100.0);
    else
        glOrtho(-160.0 * (GLfloat)w / (GLfloat)h,
            160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -10.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

}



int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
    auxInitPosition(0, 0, 300, 200);
    auxInitWindow("un patrat care se translateaza pe axa x");
    myinit();
    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);
    auxKeyFunc(AUX_UP, MutaSus);
    auxKeyFunc(AUX_DOWN, MutaJos);
    auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_up);
    auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_z_down);

    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}