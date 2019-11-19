#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_state { E1 }
{
    ui->setupUi(this);
    retroAction();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableUp() {
    ui->button1->setEnabled(true);
    ui->button2->setEnabled(true);
    ui->button3->setEnabled(false);
    ui->button4->setEnabled(false);
}

void MainWindow::enableDown() {
    ui->button1->setEnabled(false);
    ui->button2->setEnabled(false);
    ui->button3->setEnabled(true);
    ui->button4->setEnabled(true);
}

void MainWindow::retroAction() {
    switch (m_state) {
    case E1:
        enableUp();
        break;
    case E2:
        enableUp();
        break;
    case E3:
        enableUp();
        break;
    case E4:
        enableDown();
        break;
    case E5:
        enableDown();
        break;
    case E6:
        enableDown();
        break;
    }
}

void MainWindow::on_button1_clicked()
{
    switch (m_state) {
    case E1:
        m_state = E2;
        retroAction();
        break;
    case E2:
        m_state = E2;
        retroAction();
        break;
    case E3:
        m_state = E4;
        retroAction();
        break;
    case E4:
        //forbidden
        break;
    case E5:
        //forbidden
        break;
    case E6:
        //forbidden
        break;
    }
}

void MainWindow::on_button2_clicked()
{
    switch (m_state) {
    case E1:
        m_state = E3;
        retroAction();
        break;
    case E2:
        m_state = E4;
        retroAction();
        break;
    case E3:
        m_state = E3;
        retroAction();
        break;
    case E4:
        //forbidden
        break;
    case E5:
        //forbidden
        break;
    case E6:
        //forbidden
        break;
    }
}

void MainWindow::on_button3_clicked()
{
    switch (m_state) {
    case E1:
        //forbidden
        break;
    case E2:
        //forbidden
        break;
    case E3:
        //forbidden
        break;
    case E4:
        m_state = E5;
        retroAction();
        break;
    case E5:
        m_state = E5;
        retroAction();
        break;
    case E6:
        m_state = E1;
        retroAction();
        break;
    }
}

void MainWindow::on_button4_clicked()
{
    switch (m_state) {
    case E1:
        //forbidden
        break;
    case E2:
        //forbidden
        break;
    case E3:
        //forbidden
        break;
    case E4:
        m_state = E6;
        retroAction();
        break;
    case E5:
        m_state = E1;
        retroAction();
        break;
    case E6:
        m_state = E6;
        retroAction();
        break;
    }
}
