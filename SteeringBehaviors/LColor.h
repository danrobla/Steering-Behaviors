#ifndef COLORS_H_
#define COLORS_H_

#include "LOpenGL.h"

struct LColor
{
    GLfloat R;
    GLfloat G;
    GLfloat B;
    GLfloat A;

    LColor() : R(0.f), G(0.f), B(0.f), A(0.f) {}
    LColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) : R(r), G(g), B(b), A(a) {}
};

#endif /* COLORS_H_ */
