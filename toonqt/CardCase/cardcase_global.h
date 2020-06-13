#ifndef CARDCASE_GLOBAL_H
#define CARDCASE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <memory>
#include <QPixmap>

#ifdef CARDCASE_LIB
# define CARDCASE_EXPORT Q_DECL_EXPORT
#else
# define CARDCASE_EXPORT Q_DECL_IMPORT
#endif

typedef enum secondNodeTreeType
{
	Colleague,
	Group,
	GroupChat
}NodeType;
#endif // CARDCASE_GLOBAL_H
