#include "TNShortCutKeyTextMap.h"

#include <QDebug>

QMap<Qt::Key, QString> TNShortCutKeyTextMap::m_keyToText = initialKeyToText();
QMap<Qt::Key, QString> TNShortCutKeyTextMap::initialKeyToText()
{
    QMap<Qt::Key, QString> keyToText;

    // 数字键0-9（上半部特殊字符）
    keyToText.insert(Qt::Key_Exclam, QString("1"));
    keyToText.insert(Qt::Key_At, QString("2"));
    keyToText.insert(Qt::Key_NumberSign, QString("3"));
    keyToText.insert(Qt::Key_Dollar, QString("4"));
    keyToText.insert(Qt::Key_Percent, QString("5"));
    keyToText.insert(Qt::Key_AsciiCircum, QString("6"));
    keyToText.insert(Qt::Key_Ampersand, QString("7"));
    keyToText.insert(Qt::Key_Asterisk, QString("8"));
    keyToText.insert(Qt::Key_ParenLeft, QString("9"));
    keyToText.insert(Qt::Key_ParenRight, QString("0"));

    // 数字键0-9
    for (int i=int(Qt::Key_0); i<=int(Qt::Key_9); ++i)
    {
        keyToText.insert(Qt::Key(i), QChar(int(i)));
    }

    // 字母键A-Z
    for (int i=int(Qt::Key_A); i<=int(Qt::Key_Z); ++i)
    {
        keyToText.insert(Qt::Key(i), QChar(int(i)));
    }

    return keyToText;
}

QMap<Qt::KeyboardModifiers, QString> TNShortCutKeyTextMap::m_mkeyToText = initialMKeyToText();
QMap<Qt::KeyboardModifiers, QString> TNShortCutKeyTextMap::initialMKeyToText()
{
    QMap<Qt::KeyboardModifiers, QString> mKeyTextMap;

#ifdef Q_OS_MAC
    mKeyTextMap.insert(Qt::MetaModifier, QStringLiteral("Meta"));
    mKeyTextMap.insert(Qt::ControlModifier, QStringLiteral("Ctrl"));
    mKeyTextMap.insert((Qt::ShiftModifier | Qt::ControlModifier), QStringLiteral("Ctrl+Shift"));
    mKeyTextMap.insert((Qt::ShiftModifier | Qt::MetaModifier), QStringLiteral("Shift+Meta"));
    mKeyTextMap.insert((Qt::ShiftModifier | Qt::AltModifier), QStringLiteral("Shift+Alt"));
    mKeyTextMap.insert((Qt::ControlModifier | Qt::AltModifier), QStringLiteral("Ctrl+Alt"));
    mKeyTextMap.insert((Qt::ControlModifier | Qt::MetaModifier), QStringLiteral("Ctrl+Meta"));
    mKeyTextMap.insert((Qt::AltModifier | Qt::MetaModifier), QStringLiteral("Alt+Meta"));
#else
    mKeyTextMap.insert(Qt::ControlModifier, QStringLiteral("Ctrl"));
    mKeyTextMap.insert(Qt::AltModifier , QStringLiteral("Alt"));
    mKeyTextMap.insert((Qt::ShiftModifier | Qt::ControlModifier), QStringLiteral("Ctrl+Shift"));
    mKeyTextMap.insert((Qt::ShiftModifier | Qt::AltModifier), QStringLiteral("Shift+Alt"));
    mKeyTextMap.insert((Qt::ControlModifier | Qt::AltModifier), QStringLiteral("Ctrl+Alt"));
#endif

    return mKeyTextMap;
}

QMap<Qt::KeyboardModifiers, QString> TNShortCutKeyTextMap::m_mkeyToUiText = initialMKeyToUiText();
QMap<Qt::KeyboardModifiers, QString> TNShortCutKeyTextMap::initialMKeyToUiText()
{
    QMap<Qt::KeyboardModifiers, QString> mKeyUiTextMap;

#ifdef Q_OS_MAC
    mKeyUiTextMap.insert(Qt::MetaModifier, QStringLiteral("^"));
    mKeyUiTextMap.insert(Qt::ControlModifier, QStringLiteral("⌘"));
    mKeyUiTextMap.insert((Qt::ShiftModifier | Qt::ControlModifier), QStringLiteral("Shift+⌘"));
    mKeyUiTextMap.insert((Qt::ShiftModifier | Qt::MetaModifier), QStringLiteral("Shift+^"));
    mKeyUiTextMap.insert((Qt::ShiftModifier | Qt::AltModifier), QStringLiteral("Shift+⌥"));
    mKeyUiTextMap.insert((Qt::ControlModifier | Qt::AltModifier), QStringLiteral("⌘+⌥"));
    mKeyUiTextMap.insert((Qt::ControlModifier | Qt::MetaModifier), QStringLiteral("⌘+^"));
    mKeyUiTextMap.insert((Qt::AltModifier | Qt::MetaModifier), QStringLiteral("⌥+^"));
#else
    mKeyUiTextMap.insert(Qt::ControlModifier, QStringLiteral("Ctrl"));
    mKeyUiTextMap.insert(Qt::AltModifier , QStringLiteral("Alt"));
    mKeyUiTextMap.insert((Qt::ShiftModifier | Qt::ControlModifier), QStringLiteral("Ctrl+Shift"));
    mKeyUiTextMap.insert((Qt::ShiftModifier | Qt::AltModifier), QStringLiteral("Shift+Alt"));
    mKeyUiTextMap.insert((Qt::ControlModifier | Qt::AltModifier), QStringLiteral("Ctrl+Alt"));
#endif

    return mKeyUiTextMap;
}

QString TNShortCutKeyTextMap::getTextByKey(int key)
{
    return m_keyToText[Qt::Key(key)];
}

QString TNShortCutKeyTextMap::getTextByMKey(Qt::KeyboardModifiers mkey)
{
    return m_mkeyToText[mkey];
}

QString TNShortCutKeyTextMap::getUiTextByMKey(Qt::KeyboardModifiers mkey)
{
    return m_mkeyToUiText[mkey];
}

QString TNShortCutKeyTextMap::getUiTextByText(const QString &keyText)
{
    if (!keyText.contains("+"))
    {
        qDebug()<<"error! TNShortCutKeyTextMap-keyText="<<keyText;
        return QString::null;
    }

    int index = keyText.lastIndexOf("+");
    QString mKeyText = keyText.left(index);
    //qDebug()<<"mKeyText="<<mKeyText;
    Qt::KeyboardModifiers mkey = m_mkeyToText.key(mKeyText);
    return m_mkeyToUiText[mkey] + "+" + keyText.right(1);
}

QString TNShortCutKeyTextMap::getTextByUiText(const QString &keyUiText)
{
    if (!keyUiText.contains("+"))
    {
        qDebug()<<"error! TNShortCutKeyTextMap-keyUiText="<<keyUiText;
        return QString::null;
    }

    int index = keyUiText.lastIndexOf("+");
    QString mKeyUiText = keyUiText.left(index);
    //qDebug()<<"mKeyUiText="<<mKeyUiText;
    Qt::KeyboardModifiers mkey = m_mkeyToUiText.key(mKeyUiText);
    return m_mkeyToText[mkey] + "+" + keyUiText.right(1);
}
