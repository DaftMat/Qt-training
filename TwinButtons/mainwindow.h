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
        E1,
        E2,
        E3,
        E4,
        E5,
        E6
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button1_clicked();

    void on_button2_clicked();

    void on_button3_clicked();

    void on_button4_clicked();

private:
    void enableUp();
    void enableDown();
    void retroAction();

    Ui::MainWindow *ui;
    State m_state;

};
#endif // MAINWINDOW_H
