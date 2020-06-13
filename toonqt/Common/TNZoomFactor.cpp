#include "TNZoomFactor.h"
#ifdef WIN32
#include <Windows.h>
#endif
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
qreal TNZoomFactor::s_factor = 1;
TNZoomFactor::TNZoomFactor()
{
}


TNZoomFactor::~TNZoomFactor()
{
}

void  TNZoomFactor::InitAPPFactor()
{
#ifdef WIN32
	DEVMODE dm;
	dm.dmSize = sizeof(DEVMODE);
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
	int  dmLogPixels = dm.dmLogPixels;
	qInfo() << "[zoomFactor]: dpi = " << dmLogPixels;
	qreal dpi = dmLogPixels;
	qreal dpiRatio = 1.0;
	if (dpi <= 108) { // 0-96-108
		dpiRatio = 1.0;
	}
	else if (dpi <= 132) { // 108-120-132
		dpiRatio = 1.25;
	}
	else if (dpi <= 168) { // 132-144-168
		dpiRatio = 1.5;
	}
	else { // 168-192-inf
		dpiRatio = 2.0;
	}
	s_factor = dpiRatio;
	QString strFactor = QString::number(s_factor);
	qInfo() << "[zoomFactor]: s_factor = " << strFactor;
	qputenv("QT_SCALE_FACTOR", strFactor.toUtf8());
#endif
}

qreal TNZoomFactor::GetAppFactor()
{
	return s_factor;
}

int TNZoomFactor::GetMaxFrameWidth()
{
	QDesktopWidget* desktop = QApplication::desktop();
	QRect validScreenRect = desktop->availableGeometry();
	return validScreenRect.width();
}
int TNZoomFactor::GetMaxFrameHeight()
{
	QDesktopWidget* desktop = QApplication::desktop();
	QRect validScreenRect = desktop->availableGeometry();
	return validScreenRect.height();
}

