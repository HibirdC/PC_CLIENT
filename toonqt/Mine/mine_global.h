#ifndef MINE_GLOBAL_H
#define MINE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MINE_LIB
# define MINE_EXPORT Q_DECL_EXPORT
#else
# define MINE_EXPORT Q_DECL_IMPORT
#endif

#endif // MINE_GLOBAL_H
