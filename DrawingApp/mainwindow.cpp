#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMouseEvent>
#include <QPainter>

#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_state { IDLE }
{
    ui->setupUi(this);
    retroAction();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *ev) {
    int x, y, w, h;
    ui->frame->frameRect().getRect(&x, &y, &w, &h);
    if (ev->button() == Qt::LeftButton && ev->x() > x && ev->y() > y && ev->x() < x+w && ev->y() < y+h) {
        switch (m_state) {
        case IDLE:
            //do nothing
            break;
        case LINE:
            m_state = LINEDRAW;
            m_pStart = ev->pos();
            m_pEnd = ev->pos();
            retroAction();
            break;
        case CIRCLE:
            m_state = CIRCLEDRAW;
            m_pStart = ev->pos();
            m_pEnd = ev->pos();
            retroAction();
            break;
        case RECT:
            m_state = RECTDRAW;
            m_pStart = ev->pos();
            m_pEnd = ev->pos();
            retroAction();
            break;
        case LINEDRAW:
            //impossible
            break;
        case CIRCLEDRAW:
            //impossible
            break;
        case RECTDRAW:
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
        case LINE:
            //impossible
            break;
        case CIRCLE:
            //impossible
            break;
        case RECT:
            //impossible
            break;
        case LINEDRAW:
            m_state = LINE;
            m_pEnd = getPos(ev->pos());
            addLine();
            update();
            retroAction();
            break;
        case CIRCLEDRAW:
            m_state = CIRCLE;
            m_pEnd = getPos(ev->pos());
            addCircle();
            update();
            retroAction();
            break;
        case RECTDRAW:
            m_state = RECT;
            m_pEnd = getPos(ev->pos());
            addRect();
            update();
            retroAction();
            break;
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev) {
    switch (m_state) {
    case IDLE:
        m_state = IDLE;
        break;
    case LINE:
        //impossible
        break;
    case CIRCLE:
        //impossible
        break;
    case RECT:
        //impossible
        break;
    case LINEDRAW:
        m_state = LINEDRAW;
        m_pEnd = getPos(ev->pos());
        update();
        break;
    case CIRCLEDRAW:
        m_state = CIRCLEDRAW;
        m_pEnd = getPos(ev->pos());
        update();
        break;
    case RECTDRAW:
        m_state = RECTDRAW;
        m_pEnd = getPos(ev->pos());
        update();
        break;
    }
}

void MainWindow::paintEvent(QPaintEvent *ev) {
    QPainter p(this);
    switch (m_state) {
    case IDLE:
        //impossible
        break;
    case LINE:
        //impossible
        break;
    case CIRCLE:
        //impossible
        break;
    case RECT:
        //impossible
        break;
    case LINEDRAW:
        p.setPen(Qt::red);
        p.drawLine(m_pStart, m_pEnd);
        break;
    case CIRCLEDRAW: {
        p.setPen(Qt::red);
        double radius = getRadius();
        QPointF center = m_pStart;
        p.drawEllipse(center, radius, radius);
        break; }
    case RECTDRAW:
        p.setPen(Qt::red);
        int x = m_pStart.x();
        int y = m_pStart.y();
        int w = m_pEnd.x() - x;
        int h = m_pEnd.y() - y;
        p.drawRect(x, y, w, h);
        break;
    }
    p.setPen(Qt::black);
    for (auto &l : m_blackLines) {
        p.drawLine(l.first, l.second);
    }
    for (auto &c : m_blackCircles) {
        QPointF center = c.first;
        p.drawEllipse(center, c.second, c.second);
    }
    for (auto &r : m_blackRects) {
        p.drawRect(r.first.x(), r.first.y(), r.second.first, r.second.second);
    }
}

void MainWindow::retroAction() {
    switch(m_state) {
    case IDLE:
        ui->lineButton->setEnabled(true);
        ui->circleButton->setEnabled(true);
        ui->rectangleButton->setEnabled(true);
        break;
    case LINE:
        ui->lineButton->setEnabled(false);
        ui->circleButton->setEnabled(true);
        ui->rectangleButton->setEnabled(true);
        break;
    case CIRCLE:
        ui->lineButton->setEnabled(true);
        ui->circleButton->setEnabled(false);
        ui->rectangleButton->setEnabled(true);
        break;
    case RECT:
        ui->lineButton->setEnabled(true);
        ui->circleButton->setEnabled(true);
        ui->rectangleButton->setEnabled(false);
        break;
    default:
        ui->lineButton->setEnabled(false);
        ui->circleButton->setEnabled(false);
        ui->rectangleButton->setEnabled(false);
        break;
    }
}

void MainWindow::addLine() {
    m_blackLines.emplace_back(std::make_pair(m_pStart, m_pEnd));
}

void MainWindow::addCircle() {
    m_blackCircles.emplace_back(std::make_pair(m_pStart, getRadius()));
}

void MainWindow::addRect() {
    m_blackRects.emplace_back(std::make_pair(m_pStart, std::make_pair(m_pEnd.x() - m_pStart.x(), m_pEnd.y() - m_pStart.y())));
}

double MainWindow::getRadius() const {
    return std::sqrt((m_pStart.x()-m_pEnd.x())*(m_pStart.x()-m_pEnd.x())+(m_pStart.y()-m_pEnd.y())*(m_pStart.y()-m_pEnd.y()));
}

QPoint MainWindow::getPos(const QPoint &pos) const {
    int x, y, w, h;
    auto ret = pos;
    ui->frame->frameRect().getRect(&x, &y, &w, &h);
    if (ret.x() < x)
        ret.setX(x);
    if (ret.y() < y)
        ret.setY(y);
    if (ret.x() > x+w)
        ret.setX(x+w);
    if (ret.y() > y+h)
        ret.setY(y+h);
    return ret;
}

void MainWindow::on_lineButton_clicked()
{
    switch(m_state) {
    case IDLE:
        m_state = LINE;
        retroAction();
        break;
    case LINE:
        //forbidden
        break;
    case CIRCLE:
        m_state = LINE;
        retroAction();
        break;
    case RECT:
        m_state = LINE;
        retroAction();
        break;
    case LINEDRAW:
        //forbidden
        break;
    case CIRCLEDRAW:
        //forbidden
        break;
    case RECTDRAW:
        //forbidden
        break;
    }
}

void MainWindow::on_rectangleButton_clicked()
{
    switch (m_state) {
    case IDLE:
        m_state = RECT;
        retroAction();
        break;
    case LINE:
        m_state = RECT;
        retroAction();
        break;
    case CIRCLE:
        m_state = RECT;
        retroAction();
        break;
    case RECT:
        //forbidden
        break;
    case LINEDRAW:
        //forbidden
        break;
    case CIRCLEDRAW:
        //forbidden
        break;
    case RECTDRAW:
        //forbidden
        break;
    }
}

void MainWindow::on_circleButton_clicked()
{
    switch (m_state) {
    case IDLE:
        m_state = CIRCLE;
        retroAction();
        break;
    case LINE:
        m_state = CIRCLE;
        retroAction();
        break;
    case CIRCLE:
        //forbidden
        break;
    case RECT:
        m_state = CIRCLE;
        retroAction();
        break;
    case LINEDRAW:
        //forbidden
        break;
    case CIRCLEDRAW:
        //forbidden
        break;
    case RECTDRAW:
        //forbidden
        break;
    }
}
