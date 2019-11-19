#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMouseEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_state { IDLE }
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *ev) {
    if (ev->button() == Qt::LeftButton) {
        switch (m_state) {
        case IDLE:
            m_state = DRAW;
            m_pStart = ev->pos();
            m_pEnd = ev->pos();
            break;
        case DRAW:
            //impossible
            break;
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev) {
    if (ev->button() == Qt::LeftButton) {
        switch (m_state) {
        case IDLE:
            //impossible
            break;
        case DRAW:
            m_state = IDLE;
            addLine();
            m_pEnd = ev->pos();
            update();
            break;
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev) {
    switch (m_state) {
    case IDLE:
        m_state = IDLE;
        break;
    case DRAW:
        m_state = DRAW;
        m_pEnd = ev->pos();
        update();
        break;
    }
}

void MainWindow::paintEvent(QPaintEvent *ev) {
    QPainter p(this);
    switch (m_state) {
    case IDLE:
        //forbidden
        break;
    case DRAW:
        p.setPen(Qt::red);
        p.drawLine(m_pStart, m_pEnd);
        break;
    }
    p.setPen(Qt::black);
    for (auto &l : m_blackLines) {
        p.drawLine(l.first, l.second);
    }
}

void MainWindow::addLine() {
    m_blackLines.push_back(std::make_pair(m_pStart, m_pEnd));
}
