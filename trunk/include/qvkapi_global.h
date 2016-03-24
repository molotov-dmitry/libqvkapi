#ifndef QVKAPI_GLOBAL_H
#define QVKAPI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QVKAPI_LIBRARY)
#  define QVKAPISHARED_EXPORT Q_DECL_EXPORT
#else
#  define QVKAPISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QVKAPI_GLOBAL_H
