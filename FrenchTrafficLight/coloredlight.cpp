#include "coloredlight.h"
#include <QPen>
#include <QBrush>

ColoredLight::ColoredLight(const QColor &color, int x, int y, int radius): QGraphicsEllipseItem(x, y, 2.f*radius, 2.f*radius), lightOn(true), lightColor(color)
{
    QPen pen(lightColor);
    QBrush brush(lightColor);
    setPen(pen);
    setBrush(brush);
}

void ColoredLight::on()
{
    lightOn = true;
    setPen(QPen(lightColor));
    setBrush(QBrush(lightColor));
}

void ColoredLight::off()
{
    lightOn = false;
    QColor col = lightColor.darker(200);
    setPen(QPen(col));
    setBrush(QBrush(col));
}

void ColoredLight::toggle()
{
    if (lightOn)
        off();
    else
        on();
}



