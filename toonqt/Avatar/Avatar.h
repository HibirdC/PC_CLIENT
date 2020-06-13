#ifndef AVATAR_H
#define AVATAR_H

#include <QPointer>

#include "PluginExportBase.h"
#include "Avatar_global.h"
#include "TNMVD_global.h"
#include "TNNameSpace.h"
#include "download_face_model.h"

class AVATAR_EXPORT Avatar : public PluginExportBase
{
	Q_OBJECT
public:
	Avatar(TNPluginParamPtr pluginParam, QWidget *parent = 0);
	~Avatar();

public:
    QPointer<MenuAreaBase> GetMenu() override;
	int GetID();
	void registerToonCommand() override;
	QPointer<ListAreaBase> GetList() override;
	QPointer<DetailsAreaBase> GetDetails() override;

private:
	QPointer<MenuAreaBase> _AvatarMenuArea;
    DownLoad_Face_Model*   _downLoad_face_model;
	int _ID;
};

extern "C" AVATAR_EXPORT Avatar* getMenu(TNPluginParamPtr pluginParam, QWidget *parent);

#endif // Avatar_H
