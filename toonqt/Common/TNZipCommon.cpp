#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <fstream>
#include "TNZipCommon.h"

#include "TNPathUtil.h"
#include "tnwinconvert.h"
using namespace std;
#ifdef WIN32
#include <windows.h>
#elif __linux__
#include <sys/stat.h>
#endif

TNZipCommon::TNZipCommon()
{
}


TNZipCommon::~TNZipCommon()
{
}

/*
bool TNZipCommon::uncompressFile(QString zipFile, QString savePath)
{
    if (zipFile.isEmpty())
    {
        return false;
    }
    if (savePath.isEmpty())
    {
        QFileInfo info(zipFile);
        savePath = info.absolutePath();
    }
    else
    {
        TNPathUtil::CreateFilePath(savePath);
    }
#ifdef _WIN64
    unzFile zFileObject = unzOpen64(zipFile.toStdString().c_str());
#else
    unzFile zFileObject = unzOpen(zipFile.toStdString().c_str());
#endif
    if (nullptr == zFileObject)
    {
        Q_ASSERT(false);
        return false;
    }

#ifdef _WIN64
    unz_global_info64 globalInfo;
    if (unzGetGlobalInfo64(zFileObject, &globalInfo) != UNZ_OK)
#else
    unz_global_info globalInfo;
    if (unzGetGlobalInfo(zFileObject, &globalInfo) != UNZ_OK)
#endif
    {
        qDebug() << "unzGetGlobalInfo erro";
        return false;
    }

    for (int i = 0; i < globalInfo.number_entry; i++)
    {
        char fileName[256] = { 0 };
        char ext[256] = { 0 };
        char com[1024] = { 0 };

#ifdef _WIN64
        unz_file_info64 fileInfo;
        if (unzGetCurrentFileInfo64(zFileObject, &fileInfo, fileName, sizeof(fileName), ext, 256, com, 1024) != UNZ_OK)
#else
        unz_file_info fileInfo;
        if (unzGetCurrentFileInfo(zFileObject, &fileInfo, fileName, sizeof(fileName), ext, 256, com, 1024) != UNZ_OK)
#endif
        {
            qDebug() << "error";
        }

        //区分是目录还是文件
        bool isDir = false;
#ifdef WIN32
        isDir = fileInfo.external_fa & FILE_ATTRIBUTE_DIRECTORY;
#elif __linux__
        isDir = S_ISDIR(fileInfo.external_fa);
#endif
        if (isDir)
        {
            QString dirPath = savePath + QString(fileName);
            TNPathUtil::CreateFilePath(dirPath);
        }
        else
        {
            QString fileFullName = savePath + QString(fileName);
            QFile qFile(fileFullName);
            qFile.open(QFile::WriteOnly);

            unzOpenCurrentFile(zFileObject);
            char data[1024] = { 0 };
            while (true)
            {
                int size = unzReadCurrentFile(zFileObject, data, 1024);
                if (size <= 0)
                {
                    //int d = UNZ_ERRNO;
                    break;
                }
                qFile.write(data, size);
            }
            qFile.close();
            unzCloseCurrentFile(zFileObject);
        }

        if (i < globalInfo.number_entry - 1 && unzGoToNextFile(zFileObject) != UNZ_OK)
        {
            qDebug() << "error2";
        }
    }

    unzClose(zFileObject);
    return true;
}
*/

bool TNZipCommon::unZlibFile(const QString &src, const QString &dest)
{
    std::string sourcePath;
#ifdef Q_OS_WIN
    sourcePath = tnwinconvert::UnicodeToAscii(tnwinconvert::Utf8ToUnicode(src.toStdString()));
#else
    sourcePath = src.toStdString();
#endif
    //打开zip文件
    unzFile zFile = unzOpen64(sourcePath.c_str());
    if (NULL == zFile)
        return false;
    //获取zip文件信息
    unz_global_info64 stGlobalInfo64;
    if (unzGetGlobalInfo64(zFile, &stGlobalInfo64) != UNZ_OK){
        unzClose(zFile);
        return false;
    }
    //解析zip文件
    for (int i = 0; i < stGlobalInfo64.number_entry; i++)//迭代zip中每一个文件/夹
    {
        //解压到目标目录文件夹下
        ///////////////////////
        extract_currentfile(zFile, dest);
        //关闭当前文件
        unzCloseCurrentFile(zFile);
        //指针指向下一个文件
        if (unzGoToNextFile(zFile) != UNZ_OK)
            break;
    }
    unzClose(zFile);
    return true;
}

bool TNZipCommon::extract_currentfile(unzFile zFile, const QString &dstDir)
{
    string sDstDir;
#ifdef Q_OS_WIN
    sDstDir = tnwinconvert::UnicodeToAscii(tnwinconvert::Utf8ToUnicode(dstDir.toStdString()));
#else
    sDstDir = dstDir.toStdString();
#endif
    char sFile[260] = { 0 };//文件名
    char sExt[260] = { 0 };//extrafield
    char sCom[1024] = { 0 };//comment
    unz_file_info64 stFileInfo64;
    //获取当前文件信息
    if (unzGetCurrentFileInfo64(zFile, &stFileInfo64, sFile, sizeof(sFile),
                                sExt, sizeof(sExt), sCom, sizeof(sCom)) != UNZ_OK)
        return false;
    //区分是目录还是文件
    bool isDir = false;
#ifdef WIN32
    isDir = stFileInfo64.external_fa & FILE_ATTRIBUTE_DIRECTORY;
#elif __linux__
    isDir = S_ISDIR(stFileInfo64.external_fa);
#endif
    if (!isDir){ //文件，否则为目录
        //打开当前文件
        if (UNZ_OK != unzOpenCurrentFile(zFile)){
            return false;
        }
        //定义一个fstream对象，用来写入文件
        fstream file;
        string sDstFilePath = sDstDir + "/" + sFile;
        file.open(sDstFilePath.c_str(), ios_base::out | ios_base::binary);
        ZPOS64_T fileLength = stFileInfo64.uncompressed_size;
        //定义一个字符串变量fileData，读取到的文件内容将保存在该变量中
        char *fileData = new char[fileLength];
        //解压缩文件
        int err = unzReadCurrentFile(zFile, (voidp)fileData, fileLength);
        if (err <= 0)
            return false;
        file.write(fileData, fileLength);
        file.close();
        delete[] fileData;
    }else{//目录
        QString sDirName = dstDir + "/" + sFile;
        QDir dir;
        dir.mkdir(sDirName);
    }
    return true;
}
