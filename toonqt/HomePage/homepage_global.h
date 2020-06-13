#ifndef HOMEPAGE_GLOBAL_H
#define HOMEPAGE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef HOMEPAGE_LIB
# define HOMEPAGE_EXPORT Q_DECL_EXPORT
#else
# define HOMEPAGE_EXPORT Q_DECL_IMPORT
#endif

#endif // HOMEPAGE_GLOBAL_H
