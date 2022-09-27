#include <QtGlobal>

#include "SysInfo.h"

#ifdef Q_OS_WIN
#include "SysInfoForWindowsImpl.h"
#endif

SysInfo::SysInfo() {}

SysInfo::~SysInfo() {}

SysInfo&
SysInfo::instance()
{
#ifdef Q_OS_WIN
  static SysInfoForWindowsImpl singleton{};
#endif

  return singleton;
}
