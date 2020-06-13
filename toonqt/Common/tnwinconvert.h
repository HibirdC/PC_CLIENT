#ifndef TNWINCONVERT_H
#define TNWINCONVERT_H

#include <QObject>
#include "common_global.h"
#ifdef Q_OS_WIN
#include <Windows.h>
#endif
#include <string>
using namespace std;


class COMMON_EXPORT tnwinconvert
{
public:
    tnwinconvert();
    ~tnwinconvert();
#ifdef Q_OS_WIN
    static wstring AsciiToUnicode(const string& str);
    static string UnicodeToAscii(const wstring& wstr);
    static wstring Utf8ToUnicode(const string& str);
    static string UnicodeToUtf8(const wstring& wstr);
#endif

};

#endif // TNWINCONVERT_H
