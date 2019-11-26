#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_state { IDLE }
    , m_counter { 0 }
{
    ui->setupUi(this);
    ui->resultBar->setText(std::to_string(m_counter).c_str());
    ui->resultBar->setEnabled(false);
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
    case PLUS:
        ui->startButton->setEnabled(false);
        ui->stopButton->setEnabled(true);
        ui->plusButton->setEnabled(true);
    }
}

void MainWindow::on_startButton_clicked()
{
    switch (m_state) {
    case IDLE:
        m_state = PLUS;
        m_counter = 0;
        ui->resultBar->setText(std::to_string(m_counter).c_str());
        retroAction();
        break;
    case PLUS:
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
    case PLUS:
        m_state = IDLE;
        ui->resultBar->setText("Pouf");
        retroAction();
    }
}

void MainWindow::on_plusButton_clicked()
{
    switch (m_state) {
    case IDLE:
        //forbidden
        break;
    case PLUS:
        if (m_counter < 2)
            m_state = PLUS;
        else
            m_state = IDLE;
        m_counter++;
        ui->resultBar->setText(std::to_string(m_counter).c_str());
        retroAction();
        break;
    }
}
