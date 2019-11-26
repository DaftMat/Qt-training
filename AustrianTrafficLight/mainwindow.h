#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "coloredlight.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    ///System states
    enum State {
        IDLE,
        RED,
        YELLOW,
        GREEN,
        BLINKGREENON,
        BLINKGREENOFF,
        ERRORON,
        ERROROFF
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void timer_tick();
    void roTimer_tick();
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_errorButton_clicked();

private:
    void initialize();

    ///retro actions
    void startedRetroAction();
    void stoppedRetroAction();
    void erroredRetroAction();
    void retroAction();

    Ui::MainWindow *ui;

    ///Usage of a pointer : so we can modify it while it's printed on the scene
    ColoredLight *m_red;
    ColoredLight *m_yellow;
    ColoredLight *m_green;

    ///event management data
    State m_state;
    QTimer m_mainTimer;
    QTimer m_roTimer;
    int m_blinkCount;
};

#endif //MAINWINDOW_H
