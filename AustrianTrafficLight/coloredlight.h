#ifndef COLOREDLIGHT_H
#define COLOREDLIGHT_H

#include <QGraphicsEllipseItem>

class ColoredLight : public QGraphicsEllipseItem
{
public:
    // Color : color of the light when on (luminance divided by 4 when off)
    ColoredLight(const QColor &color, int x=10, int y=10, int radius=10);

    void on();
    void off();
    void toggle();

private :
    bool lightOn;
    QColor lightColor;
};

#endif // COLOREDLIGHT_H
