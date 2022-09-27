#include "SysInfoForWindowsImpl.h"

#include <QDebug>
#include <windows.h>

SysInfoForWindowsImpl::SysInfoForWindowsImpl()
  : SysInfo()
  , mCpuLoadLastValues()
{
}

double
SysInfoForWindowsImpl::memoryUsed()
{
  MEMORYSTATUSEX memoryStatus;
  memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
  GlobalMemoryStatusEx(&memoryStatus);
  qulonglong memoryPhysicalUsed =
    memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys;
  return (double)memoryPhysicalUsed / (double)memoryStatus.ullTotalPhys * 100.0;
}

void
SysInfoForWindowsImpl::init()
{
  mCpuLoadLastValues = cpuRawData();
}

QVector<qulonglong>
SysInfoForWindowsImpl::cpuRawData()
{
  FILETIME idleTime;
  FILETIME kernelTime;
  FILETIME userTime;

  GetSystemTimes(&idleTime, &kernelTime, &userTime);

  QVector<qulonglong> rawData(3);
  rawData.append(convertFileTime(idleTime));
  rawData.append(convertFileTime(kernelTime));
  rawData.append(convertFileTime(userTime));

  return rawData;
}

qulonglong
SysInfoForWindowsImpl::convertFileTime(const FILETIME& filetime) const
{
  ULARGE_INTEGER largeInteger;
  largeInteger.LowPart = filetime.dwLowDateTime;
  largeInteger.HighPart = filetime.dwHighDateTime;

  return largeInteger.QuadPart;
}

double
SysInfoForWindowsImpl::cpuLoadAverage()
{
  QVector<qulonglong> firstSample = mCpuLoadLastValues;
  QVector<qulonglong> secondSample = cpuRawData();
  mCpuLoadLastValues = secondSample;

  qulonglong currentIdle = secondSample[0] - firstSample[0];
  qulonglong currentKernel = secondSample[1] - firstSample[1];
  qulonglong currentUser = secondSample[2] - firstSample[2];
  qulonglong currentSystem = currentKernel + currentUser;

  qDebug() << "firstSample[0]" << firstSample[0];

  double percent = (currentSystem - currentIdle) * 100.0 / currentSystem;

  qDebug() << percent;

  return qBound(0.0, percent, 100.0);
}
