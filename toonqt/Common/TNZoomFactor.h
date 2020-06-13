#ifndef TNZOOMFACTOR_H
#define TNZOOMFACTOR_H
#include <QObject>

#include "common_global.h"

class COMMON_EXPORT TNZoomFactor
{
public:
	TNZoomFactor();
	~TNZoomFactor();
	static void  InitAPPFactor();
	static qreal GetAppFactor();
	static int GetMaxFrameWidth();
	static int GetMaxFrameHeight();
private:
	static qreal s_factor;
};
#endif 
