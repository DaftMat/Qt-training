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
        SUMMER,
        FALL,
        WINTER,
        SPRING
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_springButton_clicked();

    void on_summerButton_clicked();

    void on_winterButton_clicked();

    void on_fallButton_clicked();

private:
    void retroAction();

    Ui::MainWindow *ui;
    State m_state;


};
#endif // MAINWINDOW_H
