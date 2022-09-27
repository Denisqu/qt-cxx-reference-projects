#include <QHBoxLayout>

#include "MainWindow.h"
// #include "SysInfo.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , mCpuWidget(this)
  , mMemoryWidget(this)
{
  ui->setupUi(this);
  ui->centralwidget->setLayout(new QHBoxLayout());
  ui->centralwidget->layout()->addWidget(&mCpuWidget);
  ui->centralwidget->layout()->addWidget(&mMemoryWidget);
}

MainWindow::~MainWindow()
{
  delete ui;
}
