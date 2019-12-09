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
    ui->centralwidget->setMouseTracking(true);
    setMouseTracking(true);
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
            m_pEnd = ev->pos();
            m_points.push_back(ev->pos());
            break;
        case DRAW:
            m_state = DRAW;
            m_pEnd = ev->pos();
            m_points.push_back(ev->pos());
            break;
        }
    } else if (ev->button() == Qt::RightButton) {
        switch (m_state) {
        case IDLE:
            m_state = IDLE;
            //nothing
            break;
        case DRAW:
            if (m_points.size() == 1)
                m_state = IDLE;
            else
                m_state = DRAW;
            m_points.pop_back();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev) {
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev) {
    switch (m_state) {
    case IDLE:
        m_state = IDLE;
        //nothing
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
        p.drawLine(m_points.back(), m_pEnd);
        break;
    }
    p.setPen(Qt::black);
    for (auto &l : m_blackLines) {
        p.drawLine(l.first, l.second);
    }
    for (unsigned long i = 1 ; i < m_points.size() ; ++i) {
        p.drawLine(m_points[i-1], m_points[i]);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *ev) {
    if (m_state == IDLE) return;
    if (ev->key() == Qt::Key_Space) {
        for (unsigned long i = 1 ; i < m_points.size() ; ++i) {
            m_blackLines.push_back(std::make_pair(m_points[i-1], m_points[i]));
        }
        m_points.clear();
    }
}
