#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum State {
        IDLE,
        LINE,
        CIRCLE,
        RECT,
        LINEDRAW,
        CIRCLEDRAW,
        RECTDRAW
    };

    using Line = std::pair<QPoint, QPoint>;
    using Circle = std::pair<QPoint, double>;
    using Rect = std::pair<QPoint, std::pair<int, int>>;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_lineButton_clicked();

    void on_rectangleButton_clicked();

    void on_circleButton_clicked();

private:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *ev) override;

    void retroAction();

    void addLine();
    void addCircle();
    void addRect();
    double getRadius() const;
    QPoint getPos(const QPoint &pos) const;

    Ui::MainWindow *ui;
    State m_state;

    QPoint m_pStart;
    QPoint m_pEnd;

    std::vector<Line> m_blackLines;
    std::vector<Circle> m_blackCircles;
    std::vector<Rect> m_blackRects;
};
#endif // MAINWINDOW_H
