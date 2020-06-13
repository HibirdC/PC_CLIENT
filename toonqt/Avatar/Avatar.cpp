
#include <QProcessEnvironment>
#include <QAction>
#include "AvatarMenuBase.h"
#include "Avatar.h"
#include "tncommondealavator.h"
#include "TNNameSpace.h"
#include <QLabel>

Avatar::Avatar(TNPluginParamPtr pluginParam, QWidget *parent)
:PluginExportBase(pluginParam,parent)
,_ID(MENU_AVATAR_ID)
,_AvatarMenuArea(nullptr)
,_downLoad_face_model(NULL)
{
	_AvatarMenuArea = new AvatarMenuBase(_ID, QStringLiteral(":/Resources/default_feed_avatar.png"));
    _AvatarMenuArea->setObjectName("Menu_Avatar");
	_AvatarMenuArea->setIconSize(QSize(40, 40));
	_AvatarMenuArea->setContentsMargins(0,0, 0, 0);
    _AvatarMenuArea->setCheckable(true);
    _downLoad_face_model = new DownLoad_Face_Model(this);
    _downLoad_face_model->download_face_avatar();
    _downLoad_face_model->write_db_phone_feed();
}

Avatar::~Avatar()
{
    if(_downLoad_face_model){
        delete _downLoad_face_model;
        _downLoad_face_model = NULL;
    }
}

QPointer<MenuAreaBase> Avatar::GetMenu()
{
	return _AvatarMenuArea;
}
int Avatar::GetID()
{
	return _ID;
}

void Avatar::registerToonCommand()
{

}

Avatar* getMenu(TNPluginParamPtr pluginParam, QWidget *parent)
{
	return new Avatar(pluginParam, parent);
}
QPointer<ListAreaBase> Avatar::GetList()
{
	return NULL;
}

QPointer<DetailsAreaBase> Avatar::GetDetails()
{
	return NULL;
}
