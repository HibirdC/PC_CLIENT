#include "faceid.h"
#include "tnshowfacedialog.h"

FaceId::FaceId(QString phone_num,QObject* parent) : QObject(parent)
  ,_phone_num(phone_num)
  ,_showFaceDialog(NULL)
{

}

FaceId::~FaceId()
{
    if(_showFaceDialog){
        delete _showFaceDialog;
        _showFaceDialog = NULL;
    }
}

void FaceId::start()
{
    if(!_showFaceDialog){
        _showFaceDialog = new TNShowFaceDialog();
        connect(_showFaceDialog->_captureVideo,SIGNAL(compareResult(int)),
            this,SLOT(slotCompareResult(int)));
        connect(_showFaceDialog,SIGNAL(self_close()),
                this,SLOT(slot_self_close()));
    }
    if(!_showFaceDialog->init()){
        return;
    }
    _showFaceDialog->_captureVideo->setReconPhoneNum(_phone_num);
    _showFaceDialog->exec();
}

void FaceId::slotCompareResult(int nRes)
{
    switch (nRes) {
    case Face_Succ:
    case Face_Init_Failed:
    case Face_Compare_Failed:
    case Face_Model_Failed:
    case Face_Device_Error:
        delete _showFaceDialog;
        _showFaceDialog = NULL;
        emit compareResult(nRes);
        break;
    default:
        break;
    }
}

void FaceId::slot_self_close()
{
    if(_showFaceDialog){
        delete _showFaceDialog;
        _showFaceDialog = NULL;
    }
}
