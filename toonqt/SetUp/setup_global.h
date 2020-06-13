#ifndef SETUP_GLOBAL_H
#define SETUP_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SETUP_LIB
# define SETUP_EXPORT Q_DECL_EXPORT
#else
# define SETUP_EXPORT Q_DECL_IMPORT
#endif

#endif // SETUP_GLOBAL_H
