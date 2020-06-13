#ifndef FACEID_H
#define FACEID_H
#include <QObject>
#include "faceid_global.h"

class TNShowFaceDialog;
class FACEID_EXPORT FaceId : public QObject
{
	Q_OBJECT
public:
    explicit FaceId(QString phone_num,QObject* parent=NULL);
	~FaceId();
    void start();
    void setPhoneNum(const QString& phone_num){_phone_num = phone_num;}
Q_SIGNALS:
    void compareResult(int nRes);
private slots:
    void slotCompareResult(int nRes);
    void slot_self_close();
private:
    QString 	_phone_num;
    TNShowFaceDialog* 	_showFaceDialog;
};

#endif // FACEID_H
