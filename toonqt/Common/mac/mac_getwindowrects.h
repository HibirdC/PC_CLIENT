#ifndef MAC_GETWINDOWRECTS_H
#define MAC_GETWINDOWRECTS_H

#include <QRect>
#include <QList>
#include "common_global.h"

class COMMON_EXPORT Mac_getWindowRects
{
public:
    Mac_getWindowRects();
    ~Mac_getWindowRects();
    static QList<QRect> getWindowList();
};

#endif // MAC_GETWINDOWRECTS_H
