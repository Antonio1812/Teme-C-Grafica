#include "glos.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

void myinit(void);
void drawPlane(void);
void CALLBACK dayAdd (void);
void CALLBACK daySubtract (void);
void CALLBACK yearAdd (void);
void CALLBACK yearSubtract (void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK day2Add(void);
void CALLBACK day2Subtract(void);
void CALLBACK year2Add(void);
void CALLBACK year2Subtract(void);
void CALLBACK day3Add(void);
void CALLBACK day3Subtract(void);
void CALLBACK year3Add(void);
void CALLBACK year3Subtract(void);
void CALLBACK day4Add(void);
void CALLBACK day4Subtract(void);
void CALLBACK year4Add(void);
void CALLBACK year4Subtract(void);

static int year = 0, day = 0;
static int year2 = 0, day2 = 0;
static int year3 = 0, day3 = 0;
static int year4 = 0, day4 = 0;

void CALLBACK dayAdd (void)
{
    day = (day + 10) % 360;
}

void CALLBACK daySubtract (void)
{
    day = (day - 10) % 360;
}

void CALLBACK day2Add(void) {
    day2 = (day2 + 10) % 360;
}

void CALLBACK day2Subtract(void) {
    day2 = (day2 - 10) % 360;
}

void CALLBACK day3Add(void) {
    day3 = (day3 + 10) % 360;
}

void CALLBACK day3Subtract(void) {
    day3 = (day3 - 10) % 360;
}

void CALLBACK day4Add(void) {
    day4 = (day4 + 10) % 360;
}

void CALLBACK day4Subtract(void) {
    day4 = (day4 - 10) % 360;
}

void CALLBACK yearAdd (void)
{
    year = (year + 5) % 360;
}

void CALLBACK yearSubtract (void)
{
    year = (year - 5) % 360;
}

void CALLBACK year2Add(void) {
    year2 = (year2 + 5) % 360;
}

void CALLBACK year2Subtract(void) {
    year2 = (year2 - 5) % 360;
}

void CALLBACK year3Add(void) {
    year3 = (year3 + 5) % 360;
}

void CALLBACK year3Subtract(void) {
    year3 = (year3 - 5) % 360;
}

void CALLBACK year4Add(void) {
    year4 = (year4 + 5) % 360;
}

void CALLBACK year4Subtract(void) {
    year4 = (year4 - 5) % 360;
}

void CALLBACK display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f (1.0, 1.0, 1.0);
    glPushMatrix();

    glColor3f(1.0, 0.5, 0.0);
    glRotatef((GLfloat)year3, 0.0, 1.0, 0.0);
    glTranslatef(2.0, 0.0, 0.0);
    glRotatef((GLfloat)day3, 0.0, 1.0, 0.0);
    auxWireSphere(1.3);

    glColor3f(0.0, 0.0, 1.0);
    glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)year3, 0.0, 1.0, 0.0);
    glTranslatef (2.0, 0.0, 0.0);
    glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)day3, 0.0, 1.0, 0.0);
    auxWireSphere(0.3);


    glColor3f(0.8, 0.8, 0.8);
    glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)year2, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)year3, 0.0, 1.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);
    glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)day2, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)day3, 0.0, 1.0, 0.0);
    auxWireSphere(0.1);

    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glRotatef((GLfloat)year4, 0.0, 1.0, 0.0);
    glTranslatef(5.5, 0.0, 0.0);
    glRotatef((GLfloat)day4, 0.0, 1.0, 0.0);
    auxWireSphere(0.3);
    glPopMatrix();

    glFlush();
}

void myinit (void) {
    glShadeModel (GL_FLAT);
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
}

int main(int argc, char** argv)
{
    auxInitDisplayMode (AUX_SINGLE | AUX_RGB);
    auxInitPosition (0, 0, 500, 500);
    auxInitWindow ("Composite Modeling Transformations");
    myinit ();
    auxKeyFunc (AUX_LEFT, yearSubtract);
    auxKeyFunc (AUX_RIGHT, yearAdd);
    auxKeyFunc (AUX_UP, dayAdd);
    auxKeyFunc (AUX_DOWN, daySubtract);
    auxKeyFunc(AUX_a, year2Subtract);
    auxKeyFunc(AUX_d, year2Add);
    auxKeyFunc(AUX_w, day2Add);
    auxKeyFunc(AUX_s, day2Subtract);
    auxKeyFunc(AUX_1, year3Subtract);
    auxKeyFunc(AUX_2, year3Add);
    auxKeyFunc(AUX_3, day3Add);
    auxKeyFunc(AUX_4, day3Subtract);
    auxKeyFunc(AUX_j, year4Subtract);
    auxKeyFunc(AUX_l, year4Add);
    auxKeyFunc(AUX_i, day4Add);
    auxKeyFunc(AUX_k, day4Subtract);

    auxReshapeFunc (myReshape);
    auxMainLoop(display);
    return(0);
}
