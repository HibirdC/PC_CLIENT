#include "TNContactModel.h"
#include <QIcon>
#include <QColor>
#include <QDate>
#include <QDebug>
#include <QFontMetrics>
#include <QApplication>

#include "TNCHNHelper.h"
#include "TNHttpCloudApi.h"
#include "TNUserDataHelper.h"
#include "TNPathUtil.h"
#include "tncommondealavator.h"
#include "TNNetAvatarDown.h"

TNContactModel::TNContactModel(QObject *parent)
    : QAbstractTableModel(parent),
      m_columnCount(3),
      m_fontMetrics(QApplication::fontMetrics()),
      m_elidedTextLength(150),
      m_enableBgColor(false)
{
    // 解决Bug47：联系人列表名称长度右侧空出太多
    QFont font("Microsoft Yahei");
    font.setPixelSize(13);
    m_fontMetrics = QFontMetrics(font);
}

TNContactModel::~TNContactModel()
{
}

void TNContactModel::clearModelData()
{
    m_contacts.clear();
    m_feedIdToRowMap.clear();
}

void TNContactModel::setContactList(const QList<ContactModelItem> &contacts)
{
    beginResetModel();
    m_contacts = contacts;
    m_feedIdToRowMap.clear();
    for (int i = 0; i < contacts.size(); i++)
    {
        m_feedIdToRowMap[contacts[i].feedId] = i;
    }
    endResetModel();
}

void TNContactModel::setElidedFontMetrics(const QFontMetrics &fontMetrics)
{
    m_fontMetrics = fontMetrics;
}

void TNContactModel::setElidedTextLength(int length)
{
    m_elidedTextLength = length;
}

void TNContactModel::setEnabledBgColor(bool enabled)
{
    m_enableBgColor = enabled;
}

void TNContactModel::appendContact(const ContactModelItem &aContact)
{
    beginInsertRows(QModelIndex(), m_contacts.size(), m_contacts.size());
    m_contacts.append(aContact);
    m_feedIdToRowMap[aContact.feedId] = m_contacts.size() - 1;
    endInsertRows();
}

void TNContactModel::removeContact(const ContactModelItem &aContact)
{
    int row = m_contacts.indexOf(aContact);
    beginRemoveRows(QModelIndex(), row, row);
    m_contacts.removeOne(aContact);
    m_feedIdToRowMap.remove(aContact.feedId);
    endRemoveRows();
}

int TNContactModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_contacts.size();
}

int TNContactModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_columnCount;
}

QVariant TNContactModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();
    if (role == Qt::UserRole + 1)
    {
        return m_contacts.at(row).isLetter;
    }
    else if (role == Qt::UserRole + 2)
    {
        return m_contacts.at(row).feedId;
    }
    else if (role == Qt::UserRole + 3)
    {
        return m_contacts.at(row).btnState;
    }
    else if (role == Qt::DisplayRole)
    {
        if (col == 1)
        {
            QString displayText = m_contacts.at(row).remark;
            if (displayText.isEmpty())
                displayText = m_contacts.at(row).nickName;
            QString elidedText = m_fontMetrics.elidedText(displayText, Qt::ElideMiddle, m_elidedTextLength, Qt::TextShowMnemonic);
            return elidedText;
        }
    }
    else if (role == Qt::BackgroundColorRole)
    {
        if (m_contacts.at(row).isLetter)
            return QColor(QRgb(0xF7F7F7));
        if (m_enableBgColor && (m_contacts.at(row).btnState == ContactModelItem::SelectedState))
            return QColor(QRgb(0xF1F1F1));
    }
    else if (role == Qt::DecorationRole)
    {
        if (col == 1)
        {
            ContactModelItem &item = m_contacts[row];
            if (item.iconFile.isEmpty())
            {
                QString avatarFileName;
                if (TNPathUtil::isDownloadedAvatarPhoto(item.feedId, avatarFileName))
                {
                    item.iconFile = avatarFileName;
                }
                else
                {
                    item.iconFile = QStringLiteral(":/Resources/toolWidget/defaultNullAvatar.png");
                    asynDownloadAvatar(item.strAvatarURL, item.feedId);
                }
            }

            QString feedID = getFeedId(row);
            if (!feedID.isEmpty())
            {
                Cust_Type custType = TNCommonDealAvator::getCustomType(feedID);
                return QIcon(TNCommonDealAvator::getTypeQIcon(m_contacts.at(row).iconFile, QSize(30, 30), custType, TN::Small));
            }
            else if (!item.isLetter)
            {
                return QIcon(item.iconFile);
            }
        }
        else if (col == 2)
        {
            return QIcon(ContactModelItem::getStateIcon(m_contacts.at(row).btnState));
        }
    }

    return QVariant();
}

bool TNContactModel::isLetterItem(int row) const
{
    if (row >= 0 && row < m_contacts.size())
    {
        return m_contacts.at(row).isLetter;
    }

    Q_ASSERT(row >= 0 && row < m_contacts.size());
    return false;
}

QString TNContactModel::getFeedId(int row) const
{
    if (row >= 0 && row < m_contacts.size())
    {
        return m_contacts.at(row).feedId;
    }

    Q_ASSERT(row >= 0 && row < m_contacts.size());
    return QString::null;
}

int TNContactModel::getRowByFeedId(const QString &feedId) const
{
    if (m_feedIdToRowMap.contains(feedId))
        return m_feedIdToRowMap[feedId];

    return -1;
}

bool TNContactModel::startsWith(int row, const QString &key) const
{    
    Q_ASSERT(row >= 0 && row < m_contacts.size());
    if (row >= 0 && row < m_contacts.size())
    {
        // 对于 + - 等固定按钮不参入搜索匹配
        if (m_contacts.at(row).nickNamePinYin.isEmpty() && m_contacts.at(row).feedId.isEmpty())
            return false;

        // 按备注名字
        if (isMatch(m_contacts.at(row).remark, key))
            return true;

        // 按备注拼音
        if (isMatch(m_contacts.at(row).remarkPinYin, key))
            return true;

        // 按备注拼音首字母
        QString remarkFirstLetters = getFirstLetters(m_contacts.at(row).remarkPinYin);
        if (isMatch(remarkFirstLetters, key))
            return true;

        // 按昵称名字
        if (isMatch(m_contacts.at(row).nickName, key))
            return true;

        // 按昵称拼音
        if (isMatch(m_contacts.at(row).nickNamePinYin, key))
            return true;

        // 按昵称拼音首字母
        QString firstLetters = getFirstLetters(m_contacts.at(row).nickNamePinYin);
        if (isMatch(firstLetters, key))
            return true;
    }

    return false;
}

ContactModelItem TNContactModel::getContact(const QModelIndex &index) const
{
    int row = index.row();
    if (row >= 0 && row < m_contacts.size())
    {
        return m_contacts.at(row);
    }

    Q_ASSERT(row >= 0 && row < m_contacts.size());
    qInfo()<<"[TNMVD][TNContactModel]error! TNContactModel::getContact index is invalid. index="<<index;
    return ContactModelItem();
}

void TNContactModel::updateButtonState(int row, ContactModelItem::ButtonState state)
{
    if (row >= 0 && row < m_contacts.size())
    {
        m_contacts[row].btnState = state;
        QModelIndex topLeft = index(row, 0);
        QModelIndex bottomRight = index(row, 1);
        emit dataChanged(topLeft, bottomRight);
    }
}

void TNContactModel::updateAvatarPhoto(int row, const QString &avatarFileName)
{
    m_mutex.lock();
    if (row >= 0 && row < m_contacts.size())
    {
        m_contacts[row].iconFile = avatarFileName;
    }
    m_mutex.unlock();
    QModelIndex tempindex = index(row, 1);
    emit dataChanged(tempindex, tempindex);
}

void TNContactModel::updateRemarkName(const QString &feedId,const QString &remark)
{
    int row = getRowByFeedId(feedId);
    if (row >= 0 && row < m_contacts.size())
    {
        m_contacts[row].remark = remark;
        m_contacts[row].remarkPinYin = TNCHNHelper::GetPinyins(remark);
        QModelIndex topLeft = index(row, 0);
        QModelIndex bottomRight = index(row, 0);
        emit dataChanged(topLeft, bottomRight);
    }
}

void TNContactModel::asynDownloadAvatar(const QString& url, const QString& feedID) const
{
    bool isOrigal = false;
    if(feedID.startsWith("gc_"))
    {
        isOrigal = true;
    }
    qInfo() << "[TNMVD][TNContactModel] asynDownloadAvatar, url: " << url << " feedId:" << feedID;
    TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(feedID, url,
                                                       TNHttpCloudApi::GetInstance()->GetCloudStoken(TNUserDataHelper::GetInstance()->_pluginParam),
                                                       this,isOrigal);
}

void TNContactModel::onAvatarDownLoadFinish(bool success, QString file_path, QString feedID)
{
    if (success)
    {
        updateAvatarPhoto(m_feedIdToRowMap[feedID], file_path);
    }
}

QString TNContactModel::getFirstLetters(const QString &pinYin)
{
    QString firstLetters;
    QStringList wordList = pinYin.simplified().split(" ");
    foreach (const QString &word, wordList)
    {
        if (!word.isEmpty())
            firstLetters.append(word.at(0));
    }

    return firstLetters;
}

bool TNContactModel::isMatch(const QString &text, const QString &key)
{
    QString title = text;
    return (title.replace(" ", "").contains(key, Qt::CaseInsensitive));
}
