#include "tnwinconvert.h"

tnwinconvert::tnwinconvert()
{

}

tnwinconvert::~tnwinconvert()
{

}

#ifdef Q_OS_WIN
wstring tnwinconvert::AsciiToUnicode(const string& str) {
    // 预算-缓冲区中宽字节的长度
    int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
    // 给指向缓冲区的指针变量分配内存
    wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);
    // 开始向缓冲区转换字节
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pUnicode, unicodeLen);
    wstring ret_str = pUnicode;
    free(pUnicode);
    return ret_str;
}

string tnwinconvert::UnicodeToAscii(const wstring& wstr) {
    // 预算-缓冲区中多字节的长度
    int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    // 给指向缓冲区的指针变量分配内存
    char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
    // 开始向缓冲区转换字节
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
    string ret_str = pAssii;
    free(pAssii);
    return ret_str;
}

wstring tnwinconvert::Utf8ToUnicode(const string& str) {
    // 预算-缓冲区中宽字节的长度
    int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    // 给指向缓冲区的指针变量分配内存
    wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);
    // 开始向缓冲区转换字节
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, pUnicode, unicodeLen);
    wstring ret_str = pUnicode;
    free(pUnicode);
    return ret_str;
}

string tnwinconvert::UnicodeToUtf8(const wstring& wstr) {
    // 预算-缓冲区中多字节的长度
    int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    // 给指向缓冲区的指针变量分配内存
    char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
    // 开始向缓冲区转换字节
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
    string ret_str = pAssii;
    free(pAssii);
    return ret_str;
}
#endif

