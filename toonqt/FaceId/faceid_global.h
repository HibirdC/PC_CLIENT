#ifndef FACEID_GLOBAL_H
#define FACEID_GLOBAL_H
#include <QtCore/qglobal.h>

#ifdef FACEID_LIB
# define FACEID_EXPORT Q_DECL_EXPORT
#else
# define FACEID_EXPORT Q_DECL_IMPORT
#endif

#define FACET_WORK_BUFFERSIZE 16*1024*1024
#define FACED_WORK_BUFFERSIZE 16*1024*1024
#define FACER_WORK_BUFFERSIZE 40*1024*1024
#define FACE_MAX_NUM 20
#ifdef __linux__
#define FACE_APPID "5YTb95ANrU4eBVPff6zkBA2Uwr1xkC4x3rUCzFZCWeCh"
#define FACE_TRACKING_KEY "2t1qn54Bj5My7pxpUZxd1dojLu4QGTqqFHmQJqsrbzmJ"
#define FACE_DETECTTION_KEY "2t1qn54Bj5My7pxpUZxd1dorWJKZKFD3UuBtspvSwdLL"
#define FACE_RECOGNITION_KEY "2t1qn54Bj5My7pxpUZxd1doyfhakBWJxa3Ntt82QUv5V"
#endif

#ifdef Q_OS_WIN
#ifdef _WIN64
#define FACE_APPID "5YTb95ANrU4eBVPff6zkBA2c7FH867wDhkKFZAjd12Zi"
#define FACE_TRACKING_KEY  "6HUfjxrTrmivHBMQwLSJLTrUkKSbdPF5zXguQzeRJ7Qk"
#define FACE_RECOGNITION_KEY "6HUfjxrTrmivHBMQwLSJLTrj57xxbAe2vSDjjrYhkrwY"
#define FACE_DETECTTION_KEY "6HUfjxrTrmivHBMQwLSJLTrbuihpMB9bH7wydjY7rBPL"
#else
#define FACE_APPID "5YTb95ANrU4eBVPff6zkBA2rS3oSrhFzhd1obUZRCYqR"
#define FACE_TRACKING_KEY  "GZvV4bj7DqZUVx6jm6P3Df2Hnxs9ocrwA2t6yHU8sb1b"
#define FACE_RECOGNITION_KEY "GZvV4bj7DqZUVx6jm6P3Df2Y7mPYY4m4o5EVu4UfPGBz"
#define FACE_DETECTTION_KEY "GZvV4bj7DqZUVx6jm6P3Df2QxN8JGtwe7nTKaDmcn5Vc"
#endif
#endif

enum FaceId_error{
    Face_Succ = 0,
    Face_Device_Error,
    Face_Init_Failed,
    Face_Compare_Failed,
    Face_Model_Failed
};

#endif // FACEID_GLOBAL_H
