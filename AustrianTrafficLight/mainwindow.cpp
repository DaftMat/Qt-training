#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_red { new ColoredLight(Qt::red, 10, -150, 50) }
    , m_yellow { new ColoredLight(Qt::yellow, 10, 0, 50) }
    , m_green { new ColoredLight(Qt::green, 10, 150, 50) }
    , m_state { IDLE }
    , m_blinkCount { 4 }
{
    ui->setupUi(this);
    connect(&m_mainTimer, SIGNAL(timeout()), this, SLOT(timer_tick()));
    connect(&m_roTimer, SIGNAL(timeout()), this, SLOT(roTimer_tick()));
    initialize();
    retroAction();
}

MainWindow::~MainWindow()
{
    delete m_red;
    delete m_yellow;
    delete m_green;
    delete ui;
}

void MainWindow::initialize() {
    m_red->off();
    m_yellow->off();
    m_green->off();
    ui->graphicsView->setScene(new QGraphicsScene);
    ui->graphicsView->scene()->addItem(m_red);
    ui->graphicsView->scene()->addItem(m_yellow);
    ui->graphicsView->scene()->addItem(m_green);
}

void MainWindow::stoppedRetroAction() {
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->errorButton->setEnabled(false);
}

void MainWindow::startedRetroAction() {
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
    ui->errorButton->setEnabled(true);
}

void MainWindow::erroredRetroAction() {
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(true);
    ui->errorButton->setEnabled(false);
}

void MainWindow::retroAction() {
    switch (m_state) {
    case IDLE:
        stoppedRetroAction();
        m_roTimer.stop();
        m_mainTimer.stop();
        break;
    case RED:
        startedRetroAction();
        m_roTimer.start(2000);
        m_mainTimer.start(3000);
        break;
    case YELLOW:
        startedRetroAction();
        m_roTimer.stop();
        m_mainTimer.start(1500);
        break;
    case GREEN:
        startedRetroAction();
        m_roTimer.stop();
        m_mainTimer.start(3000);
        m_blinkCount = 3;
        break;
    case BLINKGREENON:
        startedRetroAction();
        m_roTimer.stop();
        m_mainTimer.start(1000);
        break;
    case BLINKGREENOFF:
        startedRetroAction();
        m_roTimer.stop();
        m_mainTimer.start(1000);
        break;
    case ERRORON:
        erroredRetroAction();
        m_roTimer.stop();
        m_mainTimer.start(1000);
        break;
    case ERROROFF:
        erroredRetroAction();
        m_roTimer.stop();
        m_mainTimer.start(500);
        break;
    }
}

void MainWindow::timer_tick() {
    switch (m_state) {
    case IDLE:
        //nothing
        break;
    case RED:
        m_state = GREEN;
        m_red->off();
        m_yellow->off();
        m_green->on();
        retroAction();
        break;
    case YELLOW:
        m_state = RED;
        m_yellow->off();
        m_red->on();
        retroAction();
        break;
    case GREEN:
        m_state = BLINKGREENOFF;
        m_green->off();
        retroAction();
        break;
    case BLINKGREENON:
        if (m_blinkCount > 0) {
            m_state = BLINKGREENOFF;
            m_blinkCount--;
        } else {
            m_state = YELLOW;
            m_yellow->on();
        }
        m_green->off();
        retroAction();
        break;
    case BLINKGREENOFF:
        m_state = BLINKGREENON;
        m_green->on();
        retroAction();
        break;
    case ERRORON:
        m_state = ERROROFF;
        m_yellow->off();
        retroAction();
        break;
    case ERROROFF:
        m_state = ERRORON;
        m_yellow->on();
        retroAction();
        break;
    }
}

void MainWindow::roTimer_tick() {
    switch (m_state) {
    case RED:
        m_state = RED;
        m_yellow->on();
        break;
    default:
        //forbidden
        break;
    }
}

void MainWindow::on_startButton_clicked()
{
    switch (m_state) {
    case IDLE:
        m_state = RED;
        m_red->on();
        retroAction();
        break;
    case RED:
        //forbidden
        break;
    case YELLOW:
        //forbidden
        break;
    case GREEN:
        //forbidden
        break;
    case BLINKGREENON:
        //forbidden
        break;
    case BLINKGREENOFF:
        //forbidden
        break;
    case ERRORON:
        m_state = RED;
        m_yellow->off();
        m_red->on();
        retroAction();
        break;
    case ERROROFF:
        m_state = RED;
        m_red->on();
        retroAction();
    }
}

void MainWindow::on_stopButton_clicked()
{
    switch (m_state) {
    case IDLE:
        //forbidden
        break;
    case RED:
        m_state = IDLE;
        m_red->off();
        m_yellow->off();
        retroAction();
        break;
    case YELLOW:
        m_state = IDLE;
        m_yellow->off();
        retroAction();
        break;
    case GREEN:
        m_state = IDLE;
        m_green->off();
        retroAction();
        break;
    case BLINKGREENON:
        m_state = IDLE;
        m_green->off();
        retroAction();
        break;
    case BLINKGREENOFF:
        m_state = IDLE;
        retroAction();
        break;
    case ERRORON:
        m_state = IDLE;
        m_yellow->off();
        retroAction();
        break;
    case ERROROFF:
        m_state = IDLE;
        retroAction();
    }
}

void MainWindow::on_errorButton_clicked()
{
    switch (m_state) {
    case IDLE:
        //forbidden
        break;
    case RED:
        m_state = ERRORON;
        m_red->off();
        m_yellow->on();
        retroAction();
        break;
    case YELLOW:
        m_state = ERRORON;
        retroAction();
        break;
    case GREEN:
        m_state = ERRORON;
        m_green->off();
        m_yellow->on();
        retroAction();
        break;
    case BLINKGREENON:
        m_state = ERRORON;
        m_green->off();
        m_yellow->on();
        retroAction();
        break;
    case BLINKGREENOFF:
        m_state = ERRORON;
        m_yellow->on();
        retroAction();
    case ERRORON:
        //forbidden
        break;
    case ERROROFF:
        //forbidden
        break;
    }
}
