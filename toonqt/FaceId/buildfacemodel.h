#ifndef BUILDFACEMODEL_H
#define BUILDFACEMODEL_H

#include <QObject>
#include "arcsoft_fsdk_face_detection.h"


class BuildFaceModel : public QObject
{
    Q_OBJECT
public:
    BuildFaceModel(QObject* parent=NULL);
    ~BuildFaceModel();

    bool inputFaceModelImage(const QString& path,
                             LPAFD_FSDK_FACERES* faceRes,
                             ASVLOFFSCREEN& offInput);
    bool getInited(){return _inited;}
private:
    bool init();
private:
    MByte*	_pWorkMem;
    MHandle	_hEngine;
    bool 	_inited;
};

#endif // BUILDFACEMODEL_H
