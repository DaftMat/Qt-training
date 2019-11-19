#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_state { SPRING }
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
    case SPRING:
        ui->springButton->setEnabled(true);
        ui->summerButton->setEnabled(false);
        ui->fallButton->setEnabled(false);
        ui->winterButton->setEnabled(false);
        break;
    case SUMMER:
        ui->springButton->setEnabled(false);
        ui->summerButton->setEnabled(true);
        ui->fallButton->setEnabled(false);
        ui->winterButton->setEnabled(false);
        break;
    case FALL:
        ui->springButton->setEnabled(false);
        ui->summerButton->setEnabled(false);
        ui->fallButton->setEnabled(true);
        ui->winterButton->setEnabled(false);
        break;
    case WINTER:
        ui->springButton->setEnabled(false);
        ui->summerButton->setEnabled(false);
        ui->fallButton->setEnabled(false);
        ui->winterButton->setEnabled(true);
        break;
    }
}

void MainWindow::on_springButton_clicked()
{
    switch (m_state) {
    case SPRING:
        m_state = SUMMER;
        retroAction();
        break;
    case SUMMER:
        //forbidden
        break;
    case FALL:
        //forbidden
        break;
    case WINTER:
        //forbidden
        break;
    }
}

void MainWindow::on_summerButton_clicked()
{
    switch (m_state) {
    case SPRING:
        //forbidden
        break;
    case SUMMER:
        m_state = FALL;
        retroAction();
        break;
    case FALL:
        //forbidden
        break;
    case WINTER:
        //forbidden
        break;
    }
}

void MainWindow::on_winterButton_clicked()
{
    switch (m_state) {
    case SPRING:
        //forbidden
        break;
    case SUMMER:
        //forbidden
        break;
    case FALL:
        //forbidden
        break;
    case WINTER:
        m_state = SPRING;
        retroAction();
        break;
    }
}

void MainWindow::on_fallButton_clicked()
{
    switch (m_state) {
    case SPRING:
        //forbidden
        break;
    case SUMMER:
        //forbidden
        break;
    case FALL:
        m_state = WINTER;
        retroAction();
        break;
    case WINTER:
        //forbidden
        break;
    }
}
