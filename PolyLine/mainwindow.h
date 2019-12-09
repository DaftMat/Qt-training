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
        DRAW
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
    void keyPressEvent(QKeyEvent *ev) override;

    Ui::MainWindow *ui;
    State m_state;

    std::vector<QPoint> m_points;
    QPoint m_pEnd;

    std::vector<Line> m_blackLines;
};
#endif // MAINWINDOW_H
