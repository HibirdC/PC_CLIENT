#ifndef DOWNLOAD_FACE_MODEL_H
#define DOWNLOAD_FACE_MODEL_H

#include <QObject>
#include "TNHttpCloudApi.h"

class DownLoad_Face_Model : public QObject
{
    Q_OBJECT
public:
    DownLoad_Face_Model(QObject* parent=NULL);
    ~DownLoad_Face_Model();
    void download_face_avatar();
    bool write_db_phone_feed();
private:
    bool delete_pre_faceId(const QString& cur_phone_num);
private:
    TNHttpCloudApi* 	_httpApi;
    QString 			_faceId_path;
};

#endif // DOWNLOAD_FACE_MODEL_H
