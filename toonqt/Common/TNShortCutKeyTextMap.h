#pragma once

#include "common_global.h"

#include <QMap>
#include <QString>
#include <QKeyEvent>

class COMMON_EXPORT TNShortCutKeyTextMap
{
public:
    ~TNShortCutKeyTextMap();

    static QString getTextByKey(int key);
    static QString getTextByMKey(Qt::KeyboardModifiers mkey);
    static QString getUiTextByMKey(Qt::KeyboardModifiers mkey);
    static QString getUiTextByText(const QString &keyText);
    static QString getTextByUiText(const QString &keyUiText);

private:
    TNShortCutKeyTextMap();
    static QMap<Qt::Key, QString> m_keyToText;
    static QMap<Qt::Key, QString> initialKeyToText();
    static QMap<Qt::KeyboardModifiers, QString> m_mkeyToText;
    static QMap<Qt::KeyboardModifiers, QString> initialMKeyToText();
    static QMap<Qt::KeyboardModifiers, QString> m_mkeyToUiText;
    static QMap<Qt::KeyboardModifiers, QString> initialMKeyToUiText();
};

