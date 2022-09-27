#ifndef SYSINFOFORWINDOWSIMPL_H
#define SYSINFOFORWINDOWSIMPL_H

#include <QVector>
#include <QtGlobal>

#include "SysInfo.h"

typedef struct _FILETIME FILETIME;

class SysInfoForWindowsImpl : public SysInfo
{
public:
  SysInfoForWindowsImpl();

  // SysInfo interface
public:
  void init() override;
  double cpuLoadAverage() override;
  double memoryUsed() override;

private:
  QVector<qulonglong> cpuRawData();
  qulonglong convertFileTime(const FILETIME& filetime) const;

private:
  QVector<qulonglong> mCpuLoadLastValues;
};

#endif // SYSINFOFORWINDOWSIMPL_H
