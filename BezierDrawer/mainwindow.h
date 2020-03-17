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
        FSTPT,
        IDLEPT,
        POINT
    };

    struct BezierPoint {
        QPoint point;
        QPoint tangent;
    };

    using Line = std::pair<QPoint, QPoint>;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void paintEvent(QPaintEvent *ev) override;

    void addCurve();
    void updateRedCurve();  ///< bezier calculations go here
    void updateTangent();

    Ui::MainWindow *ui;
    State m_state;

    BezierPoint m_pStart;
    BezierPoint m_pEnd;

    Line m_currentTangent;
    std::vector<Line> m_blacklines;
    std::vector<Line> m_redlines;
};
#endif // MAINWINDOW_H
