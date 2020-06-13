#ifndef BASEIMAGELIST_H
#define BASEIMAGELIST_H

#include <QObject>
#include <list>
#include <QImage>
#include <mutex>
#include <QVector>

struct FR_data{
    QVector<QRect> faceRects;
    int 		   faceAngle;
    QImage		   imageData;
};

class BaseImageList
{
private:
    BaseImageList();
public:
    static BaseImageList* getInstance();
    static void releaseInstance();
    ~BaseImageList();
    void appendImage(const QImage& image);
    bool getNewestImage(QImage& image);

    void appendFrData(const FR_data& data);
    bool getFrData(FR_data& data);
    void clearFrData();
private:
    std::list<QImage> _face_tracking_list;
    std::mutex _face_tracking_mutex;

    std::list<FR_data> _face_recognition_list;
    std::mutex _face_recognition_mutex;

    static BaseImageList* _baseImageListPtr;
};

#endif // BASEIMAGELIST_H
