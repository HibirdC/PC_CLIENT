#ifndef AVATAR_GLOBAL_H
#define AVATAR_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef AVATAR_LIB
# define AVATAR_EXPORT Q_DECL_EXPORT
#else
# define AVATAR_EXPORT Q_DECL_IMPORT
#endif

#endif // AVATAR_GLOBAL_H
