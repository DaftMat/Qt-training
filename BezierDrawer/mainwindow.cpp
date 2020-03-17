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
            m_state = FSTPT;
            m_pEnd.point = ev->pos();
            m_pEnd.tangent = QPoint(0, 0);
            break;
        case FSTPT:
            //impossible
            break;
        case IDLEPT:
            m_state = POINT;
            m_pEnd.point = ev->pos();
            m_pEnd.tangent = QPoint(0, 0);
            break;
        case POINT:
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
        case FSTPT:
            m_state = IDLEPT;
            m_currentTangent = std::make_pair(QPoint(0, 0), QPoint(0, 0));
            m_pStart = m_pEnd;
            update();
            break;
        case IDLEPT:
            //impossible
            break;
        case POINT:
            m_state = IDLEPT;
            m_currentTangent = std::make_pair(QPoint(0, 0), QPoint(0, 0));
            addCurve();
            m_redlines.clear();
            m_pStart = m_pEnd;
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
    case FSTPT:
        m_state = FSTPT;
        m_pEnd.tangent = ev->pos() + m_pEnd.point;
        updateTangent();
        update();
        break;
    case IDLEPT:
        m_state = IDLEPT;
        break;
    case POINT:
        m_state = POINT;
        m_pEnd.tangent = ev->pos() - m_pEnd.point;
        updateTangent();
        updateRedCurve();
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
    case FSTPT:
        p.setPen(Qt::blue);
        p.drawLine(m_currentTangent.first, m_currentTangent.second);
        break;
    case IDLEPT:
        //forbidden
        break;
    case POINT:
        p.setPen(Qt::blue);
        p.drawLine(m_currentTangent.first, m_currentTangent.second);
        p.setPen(Qt::red);
        for (const auto &l : m_redlines) {
            p.drawLine(l.first, l.second);
        }
    }
    p.setPen(Qt::black);
    for (const auto &l : m_blacklines) {
        p.drawLine(l.first, l.second);
    }
}

void MainWindow::addCurve() {
    m_blacklines.insert(m_blacklines.end(), m_redlines.begin(), m_redlines.end());
}

void MainWindow::updateTangent() {
    QPoint p1 = m_pEnd.point + m_pEnd.tangent;
    QPoint p2 = m_pEnd.point - m_pEnd.tangent;
    m_currentTangent = std::make_pair(p1, p2);
}

void MainWindow::updateRedCurve() {
    std::vector<Line> redcurve;
    double h0, h1, h2, h3;
    QPoint cfst, cscd;
    cfst = m_pStart.point;
    for (double u = 0 ; u <= 1 ; u += 0.0001) {
        h0 = ((u - 1) * (u - 1)) * (2 * u + 1);
        h1 = (u * u) * (3 - 2 * u);
        h2 = u * ((u - 1) * (u - 1));
        h3 = (u * u) * (u - 1);
        cscd = h0 * m_pStart.point + h1 * m_pEnd.point + h2 * m_pStart.tangent + h3 * m_pEnd.tangent;
        redcurve.push_back(std::make_pair(cfst, cscd));
        cfst = cscd;
    }
    m_redlines = redcurve;
}
