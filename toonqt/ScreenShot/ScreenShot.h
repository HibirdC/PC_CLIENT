#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include "screenshot_global.h"
#include "TNNameSpace.h"

class SCREENSHOT_EXPORT TNScreenShot
{
public:
    static TN::ScreenShotExitFlag screenShot();

    static bool getCurrentScreenShot();

private:
    static bool m_screenShoting;
};

#endif // SCREENSHOT_H
