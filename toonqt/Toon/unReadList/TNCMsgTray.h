#ifndef TNCMSGTRAY_H
#define TNCMSGTRAY_H

#include <QObject>

#include <windows.h>

class CTrayPos
{
private:
	POINT                m_ptMouse;
	HANDLE               m_hThread;
	HANDLE               m_hExitEvent;
	BOOL                 m_bTrackMouse;
	CRITICAL_SECTION     m_cs;

public:
	CTrayPos();
	virtual ~CTrayPos();

	static UINT CALLBACK TrackMousePt(PVOID pvClass);
	VOID OnMouseMove();
	BOOL IsMouseHover();

protected:
	virtual VOID OnMouseHover() = 0;
	virtual VOID OnMouseLeave() = 0;
};

class TNCMsgTray : public CTrayPos
{
public:
	TNCMsgTray(HWND hwnd = NULL, UINT uID = 0, UINT uCallbackMsg = 0);
	~TNCMsgTray();

	VOID SetNotifyIconInfo(HWND hwnd, UINT uID, UINT uCallbackMsg);

protected:
	VOID OnMouseHover();
	VOID OnMouseLeave();
private:
	HWND    m_hNotifyWnd;
	UINT    m_uID;
	UINT    m_uCallbackMsg;
};

#endif // TNCMSGTRAY_H
