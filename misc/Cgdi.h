#ifndef CGDI_H_
#define CGDI_H_

#include <QWidget>
#include <vector>

#include "2D/Vector2D.h"
#include "SteeringBehaviors/LColor.h"
#include "SteeringBehaviors/LVertexPos2D.h"

const int NumColors = 15;

const LColor colors[NumColors] =
{
    LColor(1.f, 0.f, 0.f, 1.f),
    LColor(0.f, 0.f, 1.f, 1.f),
    LColor(0.f, 1.f, 0.f, 1.f),
    LColor(0.f, 0.f, 0.f, 1.f),
    LColor(1.f, 0.8f, 0.8f, 1.f),
    LColor(0.8f, 0.8f, 0.8f, 1.f),
    LColor(1.f, 1.f, 0.f, 1.f),
    LColor(1.f, 0.65f, 0.f, 1.f),
    LColor(1.f, 0.f, 0.65f, 1.f),
    LColor(0.8f, 0.35f, 0.f, 1.f),
    LColor(1.f, 1.f, 1.f, 1.f),
    LColor(0.f, 0.35f, 0.f, 1.f),
    LColor(0.f, 1.f, 1.f, 1.f),
    LColor(0.8f, 0.8f, 0.8f, 1.f),
    LColor(1.f, 0.4f, 0.4f, 1.0f)
};

#define gdi Cgdi::Instance()

class Cgdi
{
public:
    int NumPenColors()const{return NumColors;}
    enum
      {
        red,
        blue,
        green,
        black,
        pink,
        grey,
        yellow,
        orange,
        purple,
        brown,
        white,
        dark_green,
        light_blue,
        light_grey,
        light_pink,
        hollow
      };


private:

    Cgdi() {}
    Cgdi(const Cgdi&);
    Cgdi& operator=(const Cgdi&);

    const LColor* m_Color;

public:

    ~Cgdi() {}

    static Cgdi* Instance();

    void SetColor() { m_Color = &colors[white]; }

    void DrawDot(const Vector2D& position, const LColor& color);
    void DrawDot(const int& x, const int& y, const LColor& color);
    void Line(const Vector2D& from, const Vector2D& to);
    void Line(const int& x1, const int& y1, const int& x2, const int& y2);
    void Line(const double& x1, const double& y1, const double& x2, const double& y2);
    void Polyline(const std::vector<Vector2D>& points);
    void LineWithArrow(const Vector2D& from, const Vector2D& to, double size);
    void Cross(const Vector2D& pos, int diameter);
    void Rect(const int& left, const int& top, const int& right, const int& bot);
    void Rect(const double& left, const double& top, const double& right, const double& bot);
    void ClosedShape(const std::vector<Vector2D> &points);
    void Circle(const Vector2D& pos, double radius);
    void Circle(const double& x, const double& y, const double& radius);
    void Circle(const int& x, const int& y, const double& radius);
    void SetPenColor(int color);

    void BlackPen() { if(m_Color) { m_Color = &colors[black]; } }
    void WhitePen() { if(m_Color) { m_Color = &colors[white]; } }
    void RedPen() { if(m_Color) { m_Color = &colors[red]; } }
    void GreenPen() { if(m_Color) { m_Color = &colors[green]; } }
    void BluePen() { if(m_Color) { m_Color = &colors[blue]; } }
    void GreyPen() { if(m_Color) { m_Color = &colors[grey]; } }
    void PinkPen() { if(m_Color) { m_Color = &colors[pink]; } }
    void YellowPen() { if(m_Color) { m_Color = &colors[yellow]; } }
    void OrangePen() { if(m_Color) { m_Color = &colors[grey]; } }
    void PurplePen() { if(m_Color) { m_Color = &colors[pink]; } }
    void BrownPen() { if(m_Color) { m_Color = &colors[yellow]; } }
    void DarkGreenPen() { if(m_Color) { m_Color = &colors[yellow]; } }
    void LightBluePen() { if(m_Color) { m_Color = &colors[grey]; } }
    void LightGreyPen() { if(m_Color) { m_Color = &colors[pink]; } }
    void LightPinkPen() { if(m_Color) { m_Color = &colors[yellow]; } }
};

#endif /* CGDI_H_ */
