#include "misc/Cgdi.h"
#include <cmath>
#include <cassert>

Cgdi* Cgdi::Instance()
{
    static Cgdi instance;
    return &instance;
}

void Cgdi::DrawDot(const Vector2D& position, const LColor& color)  //OK
{
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

    glColorPointer( 4, GL_FLOAT, 0, &color );
    glVertexPointer( 2, GL_DOUBLE, 0, &position );

    glDrawArrays( GL_POINTS, 0, 1 );

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
};

void Cgdi::DrawDot(const int& x, const int& y, const LColor& color) //OK
{
    LVertexPos2D vertex;

    vertex.x = (GLfloat) x;
    vertex.y = (GLfloat) y;

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

    glColorPointer( 4, GL_FLOAT, 0, &color );
    glVertexPointer( 2, GL_FLOAT, 0, &vertex );

    glDrawArrays( GL_POINTS, 0, 1 );

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
};

void Cgdi::Line(const Vector2D& from, const Vector2D& to) //OK
{
    Vector2D vertices[2];

    vertices[0] = from;
    vertices[1] = to;

    glColor4f(m_Color->R, m_Color->G, m_Color->B, m_Color->A);

    glEnableClientState( GL_VERTEX_ARRAY );

    glVertexPointer( 2, GL_DOUBLE, 0, vertices );

    glDrawArrays( GL_LINES, 0, 2 );

    glDisableClientState( GL_VERTEX_ARRAY );
};

void Cgdi::Line(const int& x1, const int& y1, const int& x2, const int& y2) //OK
{
    LVertexPos2D vertices[2];

    vertices[0].x = (GLfloat) x1;
    vertices[0].y = (GLfloat) y1;

    vertices[1].x = (GLfloat) x2;
    vertices[1].y = (GLfloat) y2;

    glColor4f(m_Color->R, m_Color->G, m_Color->B, m_Color->A);

    glEnableClientState( GL_VERTEX_ARRAY );

    glVertexPointer( 2, GL_FLOAT, 0, vertices );

    glDrawArrays( GL_LINES, 0, 2 );

    glDisableClientState( GL_VERTEX_ARRAY );
}

void Cgdi::Line(const double& x1, const double& y1, const double& x2, const double& y2) //OK
{
    LVertexPos2D vertices[2];

    vertices[0].x = (GLfloat) x1;
    vertices[0].y = (GLfloat) y1;

    vertices[1].x = (GLfloat) x2;
    vertices[1].y = (GLfloat) y2;

    glColor4f(m_Color->R, m_Color->G, m_Color->B, m_Color->A);

    glEnableClientState( GL_VERTEX_ARRAY );

    glVertexPointer( 2, GL_FLOAT, 0, vertices );

    glDrawArrays( GL_LINES, 0, 2 );

    glDisableClientState( GL_VERTEX_ARRAY );
}

void Cgdi::Polyline(const std::vector<Vector2D>& points) //OK
{
    glColor4f(m_Color->R, m_Color->G, m_Color->B, m_Color->A);

    glEnableClientState( GL_VERTEX_ARRAY );

    glVertexPointer( 2, GL_DOUBLE, 0, &points[0] );

    glDrawArrays( GL_LINE_STRIP, 0, points.size());

    glDisableClientState( GL_VERTEX_ARRAY );
}

void Cgdi::LineWithArrow(const Vector2D& from, const Vector2D& to, double size)
{
    Vector2D norm = Vec2DNormalize(to-from);

    Vector2D CrossingPoint = to - (norm * size);

    glColor4f(m_Color->R, m_Color->G, m_Color->B, m_Color->A);

    Vector2D vertices[5];
    vertices[0] = from;
    vertices[1] = CrossingPoint;
    vertices[2] = CrossingPoint + (norm.Perp() * 0.4f * size);
    vertices[3] = CrossingPoint - (norm.Perp() * 0.4f * size);
    vertices[4] = to;

    glEnableClientState( GL_VERTEX_ARRAY );

    glVertexPointer( 2, GL_DOUBLE, 0, vertices );

    glDrawArrays( GL_LINES, 0, 2);
    glDrawArrays( GL_POLYGON, 2, 3);

    glDisableClientState( GL_VERTEX_ARRAY );
}

void Cgdi::Cross(const Vector2D& position, int diameter)
{
    Line((int)position.x-diameter, (int)position.y-diameter, (int)position.x+diameter, (int)position.y+diameter);
    Line((int)position.x-diameter,(int)position.y+diameter, (int)position.x+diameter, (int)position.y-diameter);
}

void Cgdi::Rect(const int& left, const int& top, const int& right, const int& bot)
{
    LVertexPos2D vertices[4];

    vertices[0].x = (GLfloat) left;
    vertices[0].y = (GLfloat) top;

    vertices[1].x = (GLfloat) right;
    vertices[1].y = (GLfloat) top;

    vertices[2].x = (GLfloat) right;
    vertices[2].y = (GLfloat) bot;

    vertices[3].x = (GLfloat) left;
    vertices[3].y = (GLfloat) bot;

    glColor4f(m_Color->R, m_Color->G, m_Color->B, m_Color->A);

    glEnableClientState( GL_VERTEX_ARRAY );

    glVertexPointer( 2, GL_FLOAT, 0, vertices );

    glDrawArrays( GL_POLYGON, 0, 4);

    glDisableClientState( GL_VERTEX_ARRAY );
}

void Cgdi::Rect(const double& left, const double& top, const double& right, const double& bot)
{
    LVertexPos2D vertices[4];

    vertices[0].x = (GLfloat) left;
    vertices[0].y = (GLfloat) top;

    vertices[1].x = (GLfloat) right;
    vertices[1].y = (GLfloat) top;

    vertices[2].x = (GLfloat) right;
    vertices[2].y = (GLfloat) bot;

    vertices[3].x = (GLfloat) left;
    vertices[3].y = (GLfloat) bot;

    glColor4f(m_Color->R, m_Color->G, m_Color->B, m_Color->A);

    glEnableClientState( GL_VERTEX_ARRAY );
    //glEnableClientState( GL_COLOR_ARRAY );

    //glColorPointer( 4, GL_FLOAT, 0, color );
    glVertexPointer( 2, GL_FLOAT, 0, vertices );

    glDrawArrays( GL_POLYGON, 0, 4);

    glDisableClientState( GL_VERTEX_ARRAY );
    //glDisableClientState( GL_COLOR_ARRAY );
}

void Cgdi::ClosedShape(const std::vector<Vector2D>& points)
{
    glColor4f(m_Color->R, m_Color->G, m_Color->B, m_Color->A);

    glEnableClientState( GL_VERTEX_ARRAY );

    glVertexPointer( 2, GL_DOUBLE, 0, &points[0] );

    glDrawArrays( GL_LINE_LOOP, 0, points.size());

    glDisableClientState( GL_VERTEX_ARRAY );
}

void Cgdi::Circle(const Vector2D& pos, double radius)
{
    int num_segments = 100*sqrt(radius);

    GLdouble theta = 2*3.1415926 / GLdouble(num_segments);

    GLdouble c = cos(theta);
    GLdouble s = sin(theta);

    GLdouble x = radius;
    GLdouble y = 0;

    Vector2D vertices[num_segments];

    for (int i = 0; i < num_segments; ++i)
    {
        vertices[i].x = pos.x + x;
        vertices[i].y = pos.y + y;

        x = x*c - y*s;
        y = x*s + y*c;
    }

    glColor4f(m_Color->R, m_Color->G, m_Color->B, m_Color->A);

    glEnableClientState( GL_VERTEX_ARRAY );

    glVertexPointer( 2, GL_DOUBLE, 0, vertices );

    glDrawArrays( GL_TRIANGLE_FAN, 0, num_segments);

    glDisableClientState( GL_VERTEX_ARRAY );
}

void Cgdi::Circle(const double& xc, const double& yc, const double& radius)
{
    int num_segments = 100*sqrt(radius);

    GLdouble theta = 2*3.1415926 / GLdouble(num_segments);

    GLdouble c = cos(theta);
    GLdouble s = sin(theta);

    GLdouble x = radius;
    GLdouble y = 0;

    Vector2D vertices[num_segments];

    for (int i = 0; i < num_segments; ++i)
    {
        vertices[i].x = xc + x;
        vertices[i].y = yc + y;

        x = x*c - y*s;
        y = x*s + y*c;
    }

    glColor4f(m_Color->R, m_Color->G, m_Color->B, m_Color->A);

    glEnableClientState( GL_VERTEX_ARRAY );

    glVertexPointer( 2, GL_DOUBLE, 0, vertices );

    glDrawArrays( GL_TRIANGLE_FAN, 0, num_segments);

    glDisableClientState( GL_VERTEX_ARRAY );
}

void Cgdi::Circle(const int& xc, const int& yc, const double& radius)
{
    int num_segments = 100*sqrt(radius);

    GLdouble theta = 2*3.1415926 / GLdouble(num_segments);

    GLdouble c = cos(theta);
    GLdouble s = sin(theta);

    GLdouble x = radius;
    GLdouble y = 0;

    Vector2D vertices[num_segments];

    for (int i = 0; i < num_segments; ++i)
    {
        vertices[i].x = xc + x;
        vertices[i].y = yc + y;

        x = x*c - y*s;
        y = x*s + y*c;
    }

    glColor4f(m_Color->R, m_Color->G, m_Color->B, m_Color->A);

    glEnableClientState( GL_VERTEX_ARRAY );

    glVertexPointer( 2, GL_DOUBLE, 0, vertices );

    glDrawArrays( GL_TRIANGLE_FAN, 0, num_segments);

    glDisableClientState( GL_VERTEX_ARRAY );
}

void Cgdi::SetPenColor(int color)
{
   assert (color < NumColors);

   switch (color)
   {
       case black: BlackPen(); return;
       case white: WhitePen(); return;
       case red: RedPen(); return;
       case green: GreenPen(); return;
       case blue: BluePen(); return;
       case pink: PinkPen(); return;
       case grey: GreyPen(); return;
       case yellow: YellowPen(); return;
       case orange: OrangePen(); return;
       case purple: PurplePen(); return;
       case brown: BrownPen(); return;
       case light_blue: LightBluePen(); return;
       case light_grey: LightGreyPen(); return;
       case light_pink: LightPinkPen(); return;
    }
};


