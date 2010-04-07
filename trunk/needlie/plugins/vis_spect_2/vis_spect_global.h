#ifndef VIS_SPECT_GLOBAL_H
#define VIS_SPECT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(VIS_SPECT_LIBRARY)
#  define VIS_SPECTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define VIS_SPECTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // VIS_SPECT_GLOBAL_H
