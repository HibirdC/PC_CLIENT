#include "download_face_model.h"
#include "TNDataCache.h"
#include "TNPathUtil.h"
#include "TNUserDataHelper.h"
#include "tnfaceid.h"
#include "TNDataControlServer.h"
#include <QDir>

DownLoad_Face_Model::DownLoad_Face_Model(QObject* parent) : QObject(parent)
  ,_httpApi(NULL)
{
    _httpApi = TNHttpCloudApi::GetInstance();
    _faceId_path = TNPathUtil::getFaceModelPath();
}

DownLoad_Face_Model::~DownLoad_Face_Model()
{

}

bool DownLoad_Face_Model::write_db_phone_feed()
{
    TableBaseVec tableBaseVec;
    TNDataControlServer::GetInstance()->GetLatestUserFromCommonDb(tableBaseVec);
    if (tableBaseVec.size() == 1){
        st_LoginUserPtr loginState =
                std::dynamic_pointer_cast<st_LoginUser>(tableBaseVec[0]);
        QList<st_FeedPtr> myAllStuff;
        QList<TableBasePtr> face_id_ptr;
        //删除以前记录的faceId
        delete_pre_faceId(loginState->GetMobile());
        /////////////////////
        TNDataCache::GetInstance()->getMyStuff(myAllStuff);
        for (st_FeedPtr feed : myAllStuff){
            st_FaceIdPtr st_faceid = std::make_shared<st_FaceId>();
            st_faceid->set_phone_num(loginState->GetMobile());
            st_faceid->set_feedId(feed->GetFeedID());
            face_id_ptr.append(st_faceid);
        }
        TNDataControlServer::GetInstance()->InsertDatas(
            face_id_ptr,INSERT_COMMON_FACEID,DBTYPE_COMMON);
    }
    return true;
}

void DownLoad_Face_Model::download_face_avatar()
{
    QList<st_FeedPtr> myAllStuff;
    TNDataCache::GetInstance()->getMyStuff(myAllStuff);
    for (st_FeedPtr feed : myAllStuff){
        //删除以前下载对应的feedid的头像
        QDir dir(_faceId_path);
        QString file_path = _faceId_path + feed->GetFeedID();
        dir.remove(file_path);
        ////////////////////////////
        if(!feed->GetFeedID().startsWith("s_")){
            continue;
        }
        /*
        _httpApi->DownFileFromCloudEx([&](QVector<QVariant> params){
            Q_UNUSED(params);
        },
        TNUserDataHelper::GetInstance()->_pluginParam,
        feed->GetAvatarID(),
        feed->GetFeedID(),
        file_path,
        0,
        "",
        true);
        */
    }
}

bool DownLoad_Face_Model::delete_pre_faceId(const QString& cur_phone_num)
{
    QStringList delete_phone_num;
    TableBaseVec tableBaseVec;
    if(!TNDataControlServer::GetInstance()->GetAllFieldsByTableName("LoginUser",
        tableBaseVec,DBTYPE_COMMON)){
        return false;
    }

    for (TableBaseVec::const_iterator iter = tableBaseVec.begin();
         iter != tableBaseVec.end(); ++iter){
        st_LoginUserPtr st_user_ptr = std::dynamic_pointer_cast<st_LoginUser>(*iter);
        if(cur_phone_num != st_user_ptr->GetMobile()){
            delete_phone_num.append(st_user_ptr->GetMobile());
        }
    }

    if(!TNDataControlServer::GetInstance()->DeleteFromTableNameByField("FaceId",
        "phone_num",delete_phone_num,DBTYPE_COMMON)){
        return false;
    }
    return true;
}
