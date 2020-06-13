#ifndef TNZIPCOMMON_H
#define TNZIPCOMMON_H
#include "common_global.h"
#include "minizip/unzip.h"
class COMMON_EXPORT TNZipCommon
{
public:
    TNZipCommon();
    virtual ~TNZipCommon();

    //!解压zip文件或文件夹:
    //!zipFile 输入zip文件名， savePath 保存路径 
    //!后一个参数为空时，默认输出到原zip文件所在目录下
    //static bool uncompressFile(QString zipFile, QString savePath = "");

    static bool unZlibFile(const QString& src,const QString& dest);
private:
    static bool extract_currentfile(unzFile zFile, const QString& dstDir);
};

#endif
