#include "CpuWidget.h"
#include "SysInfo.h"
#include <QDebug>
#include <cstdlib>
#include <ctime>

using namespace QtCharts;

CpuWidget::CpuWidget(QWidget* parent)
  : SysInfoWidget(parent)
  , mSeries(new QPieSeries(this))
{
  mSeries->setHoleSize(0.35);
  mSeries->append("CPU Load", 30.0);
  mSeries->append("CPU Free", 70.0);

  QChart* chart = chartView().chart();
  chart->addSeries(mSeries);
  chart->setTitle("CPU average load");
}

void
CpuWidget::updateSeries()
{
  std::default_random_engine eng(
    static_cast<long unsigned int>(static_cast<long unsigned int>(
      std::chrono::high_resolution_clock::now().time_since_epoch().count())));
  std::uniform_real_distribution<double> urd(0, 100);

  double cpuLoadAverage = (double)urd(eng);

  qDebug() << cpuLoadAverage;

  mSeries->clear();
  mSeries->append("Load", cpuLoadAverage);
  mSeries->append("Free", 100.0 - cpuLoadAverage);
}
