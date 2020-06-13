#ifndef TNCONTACTMODEL_H
#define TNCONTACTMODEL_H

#include <QAbstractTableModel>
#include <QFontMetrics>
#include <QMutex>

#include "TNDbUtil.h"
#include "TNIMNoticeProcessor.h"

struct ContactModelItem
{
    enum ButtonState
    {
        InvalidState = -1,
        NormalState = 0,
        DisableState = 1,
        SelectedState = 2,
        RemovableState = 3
    };

    bool isLetter;
    QString nickName;
    QString nickNamePinYin;
    QString remark;
    QString remarkPinYin;
    QString iconFile;
    QString feedId;
    QString strAvatarURL;

    ButtonState btnState;

    bool operator ==(const ContactModelItem &other)
    {
        return (this->feedId == other.feedId);
    }

    static QString getStateIcon(ContactModelItem::ButtonState btnState)
    {
        static QMap<ContactModelItem::ButtonState, QString> stateToIconMap;
        stateToIconMap[ContactModelItem::InvalidState] = QString::null;
        stateToIconMap[ContactModelItem::NormalState] = QString(":/sysButton/Resources/img/sysButton/group/uncheck.png");
        stateToIconMap[ContactModelItem::DisableState] = QString(":/sysButton/Resources/img/sysButton/group/checked.png");
        stateToIconMap[ContactModelItem::SelectedState] = QString(":/sysButton/Resources/img/sysButton/group/actived.png");
        stateToIconMap[ContactModelItem::RemovableState] = QString(":/sysButton/Resources/img/sysButton/group/cancel-btn.png");

        return stateToIconMap[btnState];
    }

    static QChar wellSymbolLetter()
    {
        return QChar('#');
    }

    static ContactModelItem makeLetterItem(QChar firstLetter)
    {
        ContactModelItem contactItem;
        contactItem.isLetter = true;
        contactItem.nickName = QString(firstLetter);
        contactItem.nickNamePinYin = QString(firstLetter);
        contactItem.btnState = ContactModelItem::InvalidState;

        return contactItem;
    }
};

class TNContactModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TNContactModel(QObject *parent = 0);
    ~TNContactModel();

    void clearModelData();
    void setContactList(const QList<ContactModelItem> &contacts);
    void setElidedFontMetrics(const QFontMetrics &fontMetrics);
    void setElidedTextLength(int length);
    void setEnabledBgColor(bool enabled);

    void appendContact(const ContactModelItem &aContact);
    void removeContact(const ContactModelItem &aContact);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool isLetterItem(int row) const;
    QString getFeedId(int row) const;
    int getRowByFeedId(const QString &feedId) const;
    bool startsWith(int row, const QString &key) const;
    ContactModelItem getContact(const QModelIndex &index) const;

    void updateButtonState(int row, ContactModelItem::ButtonState state);
    void updateAvatarPhoto(int row, const QString &avatarFileName);
    void updateRemarkName(const QString &feedId,const QString &remark);

private slots:
    void onAvatarDownLoadFinish(bool success, QString file_path, QString feedID);
private:
    void asynDownloadAvatar(const QString& url, const QString& feedID) const;

private:
    const int m_columnCount;
    QFontMetrics m_fontMetrics;
    int m_elidedTextLength;
    bool m_enableBgColor;
    mutable QList<ContactModelItem> m_contacts;
    QMutex					m_mutex;
    QMap<QString, int/*在模型中的行号*/> m_feedIdToRowMap; // 记录行号用于更新头像图标

    static QString getFirstLetters(const QString &pinYin);
    static bool isMatch(const QString &text, const QString &key);
};

#endif // TNCONTACTMODEL_H
