#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_state { IDLE }
    , m_count { 0 }
{
    ui->setupUi(this);
    retroAction();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::retroAction() {
    switch (m_state) {
    case IDLE:
        ui->startButton->setEnabled(true);
        ui->stopButton->setEnabled(false);
        ui->plusButton->setEnabled(false);
        break;
    case PLUS1:
        ui->startButton->setEnabled(false);
        ui->stopButton->setEnabled(true);
        ui->plusButton->setEnabled(true);
        break;
    }
}

void MainWindow::on_startButton_clicked()
{
    switch (m_state) {
    case IDLE:
        m_state = PLUS1;
        m_count = 0;
        ui->result->display(QString(m_count));
        retroAction();
        break;
    case PLUS1:
        //forbidden
        break;
    }
}

void MainWindow::on_stopButton_clicked()
{
    switch (m_state) {
    case IDLE:
        //forbidden
        break;
    case PLUS1:
        m_state = IDLE;
        ui->result->display("Pouf");
        retroAction();
        break;
    }
}

void MainWindow::on_plusButton_clicked()
{
    switch (m_state) {
    case IDLE:
        //forbidden
        break;
    case PLUS1:
        if (m_count < 2)
            m_state = PLUS1;
        else
            m_state = IDLE;
        ++m_count;
        ui->result->display(QString(m_count));
        retroAction();
    }
}
