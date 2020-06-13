#ifndef LOCALSTORAGECOMMON_H
#define LOCALSTORAGECOMMON_H

#include <QString>
#include <memory>
#include <vector>
#include <QDebug>

#include "localstorage_global.h"

class LOCALSTORAGE_EXPORT TableBase
{
public:
	virtual ~TableBase(){};
	virtual void ID(){};
};

class LOCALSTORAGE_EXPORT NoticelistTable : public TableBase
{
public:
	NoticelistTable()
		:strID("")
		, strName("")
		, strDepartMent("")
		, StrAvatar("")
	{

	};
	~NoticelistTable(){};
private:
	/// <summary>	FeedID号. </summary>
	QString strID;
	/// <summary>	姓名. </summary>
	QString strName;
	/// <summary>	部门. </summary>
	QString strDepartMent;
	/// <summary>	头像. </summary>
	QString StrAvatar;
public:
    void SetID(const QString& id){ strID = id; };
	const QString& GetID(){ return strID; };
    void SetName(const QString& name){ strName = name; };
	const QString& GetName(){ return strName; };
    void SetDepartMent(const QString& department){ strDepartMent = department; };
	const QString& GetDepartMent(){ return strDepartMent; };
    void SetAvatar(const QString& avatar){ StrAvatar = avatar; };
	const QString& GetAvatar(){ return StrAvatar; };
};

class LOCALSTORAGE_EXPORT NoticeDetailTable : public TableBase
{
public:
	NoticeDetailTable()
		:strID("")
		, nRows(-1)
		, cPeople(-1)
		, strContent("")
		, StrAvatar("")
	{

	};
	~NoticeDetailTable(){};
private:
	/// <summary>	ID号. </summary>
	QString strID;
	/// <summary>	行数. </summary>
	int nRows;
	/// <summary>  消息类型. </summary>
	int cPeople;
	/// <summary>	聊天内容. </summary>
	QString strContent;
	/// <summary>	头像. </summary>
	QString StrAvatar;
public:
    void SetID(const QString& id){ strID = id; };
	const QString& GetID(){ return strID; };
	void SetRow(int row){ nRows = row; };
	int GetRow(void){ return nRows; };
	void SetPeople(int people){ cPeople = people; };
	int GetPeople(){ return cPeople; };
    void SetContext(const QString& context){ strContent = context; };
	const QString& GetContext(){ return strContent; };
    void SetAvatar(const QString& avatar){ StrAvatar = avatar; };
	const QString& GetAvatar(){ return StrAvatar; };
};

class LOCALSTORAGE_EXPORT st_Feed : public TableBase
{
public:
	st_Feed()
		:strFeedID("")
		, strAvatarID("")
		, strTitle("")
		, strTitlePinYin("")
		, strSubTile("")
		, strUserID("")
		, strTag("")
		, strSocialLevel("")
		, strConsumeLevel("")
		, strServiceLevel("")
		, strKeyWord("")
		, strSex("")
		, strBirthday("")
		, strVersion("")
		, strComID("")
		, strExt1("")
		, strExt2("")
	{
	};
	~st_Feed(){};
private:
	/// <summary>	FeedID号. </summary>
	QString strFeedID;
	/// <summary> 头像ID. </summary>
	QString strAvatarID;
	/// <summary>	标题. </summary>
	QString strTitle;
	/// <summary>	标题全拼. </summary>
	QString strTitlePinYin;
	/// <summary>	子标题. </summary>
	QString strSubTile;
	/// <summary>	用户ID. </summary>
	QString strUserID;
	/// <summary>	The tag. </summary>
	QString strTag;
	/// <summary>	社会等级. </summary>
	QString strSocialLevel;
	QString strConsumeLevel;
	/// <summary>	The service level. </summary>
	QString strServiceLevel;
	QString strKeyWord;
	QString strSex;
	QString strBirthday;
	QString strVersion;
	QString strComID;
	QString strExt1; //组织名片可沟通能力
	QString strExt2;

public:
    void SetFeedID(const QString& feedID){ strFeedID = feedID; };
	const QString& GetFeedID(){ return strFeedID; };
    void SetAvatarID(const QString& avatarID){ strAvatarID = avatarID; };
	const QString& GetAvatarID(){ return strAvatarID; };
    void SetTitle(const QString& title){ strTitle = title; };
	const QString& GetTitle(){ return strTitle; };
    void SetTitlePinYin(const QString& titlePinYin){ strTitlePinYin = titlePinYin; };
	const QString& GetTitlePinYin(){ return strTitlePinYin; };
    void SetSubTile(const QString& subTile){ strSubTile = subTile; };
	const QString& GetSubTile(){ return strSubTile; };
    void SetUserID(const QString& userID){ strUserID = userID; };
	const QString& GetUserID(){ return strUserID; };
    void SetTag(const QString& tag){ strTag = tag; };
	const QString& GetTag(){ return strTag; };
    void SetSocialLevel(const QString& socialLevel){ strSocialLevel = socialLevel; };
	const QString& GetSocialLevel(){ return strSocialLevel; };
    void SetConsumeLevel(const QString& consumeLevel){ strConsumeLevel = consumeLevel; };
	const QString& GetConsumeLevel(){ return strConsumeLevel; };
    void SetServiceLevel(const QString& serviceLevel){ strServiceLevel = serviceLevel; };
	const QString& GetServiceLevel(){ return strServiceLevel; };
    void SetKeyWord(const QString& keyWord){ strKeyWord = keyWord; };
	const QString& GetKeyWord(){ return strKeyWord; };
    void SetSex(const QString& sex){ strSex = sex; };
	const QString& GetSex(){ return strSex; };
    void SetBirthday(const QString& birthday){ strBirthday = birthday; };
	const QString& GetBirthday(){ return strBirthday; };
    void SetVersion(const QString& version){ strVersion = version; };
	const QString& GetVersion(){ return strVersion; };
    void SetComID(const QString& comID){ strComID = comID; };
	const QString& GetComID(){ return strComID; };

	void SetExt1(const QString& ext1){ strExt1 = ext1; };
	const QString& GetExt1(){ return strExt1; };
	void SetExt2(const QString& ext2){ strExt2 = ext2; };
	//const QString& GetExt2(){ return strExt2; };
};

class LOCALSTORAGE_EXPORT st_NewFriend : public TableBase
{
public:
    st_NewFriend()
    {
    }
    ~st_NewFriend()
    {
    }

private:
    QString isRead;
    QString feedId;
    QString myFeedId;
    QString mobilePhone;
    QString fromWhere; // fromWhere 来源 1 手机通讯录 2 群聊 3 查找 4 推荐 5 扫一扫 等
    QString addComment;
    QString status; // 0:删除; 1：已交换; 2: 待接受
    QString applyTime;
    QString expireTime;
    QString Feed_Belong;

public:
    QString getIsRead() const
    {
        return isRead;
    }
    void setIsRead(const QString &value)
    {
        isRead = value;
    }
    QString getFeedID() const
    {
        return feedId;
    }
    void setFeedID(const QString &value)
    {
        feedId = value;
    }
    QString getMyFeedID() const
    {
        return myFeedId;
    }
    void setMyFeedID(const QString &value)
    {
        myFeedId = value;
    }
    QString getMobilePhone() const
    {
        return mobilePhone;
    }
    void setMobilePhone(const QString &value)
    {
        mobilePhone = value;
    }
    QString getFromWhere() const
    {
        return fromWhere;
    }
    void setFromWhere(const QString &value)
    {
        fromWhere = value;
    }
    QString getAddComment() const
    {
        return addComment;
    }
    void setAddComment(const QString &value)
    {
        addComment = value;
    }
    QString getStatus() const
    {
        return status;
    }
    void setStatus(const QString &value)
    {
        status = value;
    }
    QString getApplyTime() const
    {
        return applyTime;
    }
    void setApplyTime(const QString &value)
    {
        applyTime = value;
    }
    QString getExpireTime() const
    {
        return expireTime;
    }
    void setExpireTime(const QString &value)
    {
        expireTime = value;
    }
    QString getFeedBelong() const
    {
        return Feed_Belong;
    }
    void setFeedBelong(const QString &value)
    {
        Feed_Belong = value;
    }
};

class LOCALSTORAGE_EXPORT st_JoinStuff : public TableBase
{
public:
	st_JoinStuff()
		:strFeedBelong("")
		, strFeedID("")
		, strFeedType("")
		, strBelongTo("")
		, strExt1("")
		, strExt2("")
		, strExt3("")
	{
	};
	~st_JoinStuff(){};
private:
	/// <summary>	FeedID号. </summary>
	QString strFeedBelong;
	QString strFeedID;
	QString strFeedType;
	QString strBelongTo;
	QString strExt1;
	QString strExt2;
	QString strExt3;
	QString strReMark;
	QString strReMarkPY;

public:
    void SetFeedBelong(const QString& feedBelong){ strFeedBelong = feedBelong; };
	const QString& GetFeedBelong(){ return strFeedBelong; };
    void SetFeedID(const QString& feedID){ strFeedID = feedID; };
	const QString& GetFeedID(){ return strFeedID; };
    void SetFeedType(const QString& feedType){ strFeedType = feedType; };
	const QString& GetFeedType(){ return strFeedType; };
    void SetBelongTo(const QString& belongTo){ strBelongTo = belongTo; };
	const QString& GetBelongTo(){ return strBelongTo; };
    void SetExt1(const QString& ext){ strExt1 = ext; };
	const QString& GetExt1(){ return strExt1; };

	void SetExt2(const QString& ext){ strExt2 = ext; };
	const QString& GetExt2(){ return strExt2; };

	void SetExt3(const QString& ext){ strExt3 = ext; };
	const QString& GetExt3(){ return strExt3; };

	void SetReMark(const QString& remark){ strReMark = remark; };
	const QString& GetReMark(){ return strReMark; };

	void SetReMarkPY(const QString& py){ strReMarkPY = py; };
	const QString& GetReMarkPY(){ return strReMarkPY; };
};

class LOCALSTORAGE_EXPORT st_MyStuff : public TableBase
{
public:
	st_MyStuff()
		:strFeedID("")
		, strFeedType("")
		, strBelongTo("")
		, strExt("")
		, strContentDict("")
	{

	};
	~st_MyStuff(){};
private:
	/// <summary>	FeedID号. </summary>
	QString strFeedID;
	QString strFeedType;
	QString strBelongTo;
	QString strExt;
	QString strContentDict;
	
public:
    void SetFeedID(const QString& feedID){ strFeedID = feedID; };
	const QString& GetFeedID(){ return strFeedID; };
    void SetFeedType(const QString& feedType){ strFeedType = feedType; };
	const QString& GetFeedType(){ return strFeedType; };
    void SetBelongTo(const QString& belongTo){ strBelongTo = belongTo; };
	const QString& GetBelongTo(){ return strBelongTo; };
    void SetExt(const QString& ext){ strExt = ext; };
	const QString& GetExt(){ return strExt; };
    void SetContentDict(const QString& contentDict){ strContentDict = contentDict; };
	const QString& GetContentDict(){ return strContentDict; };
};

class LOCALSTORAGE_EXPORT st_Version : public TableBase
{
public:
	st_Version()
		:strName("")
		, strVersion("")
	{

	};
	~st_Version(){};
private:
	QString strName;
	QString strVersion;
public:
	void SetName(QString& name){ strName = name; };
	const QString& GetName(){ return strName; };
	void SetVersion(QString& version){ strVersion = version; };
	const QString& GetVersion(){ return strVersion; };
};

class LOCALSTORAGE_EXPORT st_LoginUser : public TableBase
{
public:
	st_LoginUser()
		:strMobile("")
		, strToken("")
        , pwdState(0)
		, checkState(0)
		, strLogDate("")
		, strExt("")
	{

	};
	~st_LoginUser(){};
private:
	QString strMobile;
	QString strToken;
    int     pwdState;
    int     checkState;
	QString strLogDate;
	QString strExt;
public:
    void SetMobile(const QString& mobile){ strMobile = mobile; };
	const QString& GetMobile(){ return strMobile; };
    void SetToken(const QString& token){ strToken = token; };
	const QString& GetToken(){ return strToken; };
    void SetLogDate(const QString& logDate){ strLogDate = logDate; };
	const QString& GetLogState(){ return strLogDate; };
    void SetPwdState(int state){ pwdState = state; };
    int  GetPwdState(){ return pwdState; };
    void SetCheckState(int state){ checkState = state; };
    int  GetCheckState(){ return checkState; };
    void SetExt(const QString& ext){ strExt = ext; };
	const QString& GetExt(){ return strExt; };
};

class LOCALSTORAGE_EXPORT st_BMessage0 : public TableBase
{
public:
	st_BMessage0()
		:strSessionId("")
		, strMsgId("")
		, nType(0)
		, nSeqId(0)
		, strFromId("")
		, strToId("")
		, strFormClientId("")
		, strToClientId("")
		, nTimestamp(0)
		, strPushInfo("")
		, nExpireTime(0)
		, nSendStatus(0)
		, nStatus(0)
		, nPriority(0)
		, nCatalogId(0)
		, strCatalog("")
		, nContentType(0)
		, strContent("")
		, nIsMyself(0)
		, nWidth(0)
		, nHeight(0)
		, strSenderName("")
		, nAtType(0)
		, strAtFeeds("")
		, strFileFormat("")
	{

	};
	~st_BMessage0(){};
private:
	QString strSessionId;
	QString strMsgId;
	int		nType;
	int		nSeqId;
	QString strFromId;
	QString strToId;
	QString strFormClientId;
	QString strToClientId;
	int     nTimestamp;
	QString strPushInfo;
	int		nExpireTime;
	int		nSendStatus;
	int		nStatus;
	int		nPriority;
	int		nCatalogId;
	QString strCatalog;
	int		nContentType;
	QString strContent;
	int 	nIsMyself;
	int		nWidth;
	int		nHeight;
	QString strSenderName;
	int		nAtType;
	QString strAtFeeds;
	QString strFileFormat;
public:
    void SetSessionId(const QString& sessionId){ strSessionId = sessionId; };
	const QString& GetSessionId(){ return strSessionId; };
	const QString& GetMsgId() { return strMsgId; };
    void SetMsgId(const QString& msgId) { strMsgId = msgId; };
	int GetType() const { return nType; };
	void SetType(int type) { nType = type; };
	int GetSeqId() const { return nSeqId; };
	void SetSeqId(int seqId) { nSeqId = seqId; };
	const QString& GetFromId() { return strFromId; };
    void SetFromId(const QString& fromId) { strFromId = fromId; };
	QString GetToId() { return strToId; };
    void SetToId(const QString& toId) { strToId = toId; };
	const QString& GetFormClientId() { return strFormClientId; };
    void SetFormClientId(const QString& formClientId) { strFormClientId = formClientId; };
	const QString& GetToClientId() { return strToClientId; };
    void SetToClientId(const QString& toClientId) { strToClientId = toClientId; };
	qlonglong GetTimestamp() const { return nTimestamp; };
	void SetTimestamp(qlonglong timeStamp) { nTimestamp = timeStamp; };
	const QString& GetPushInfo() { return strPushInfo; };
    void SetPushInfo(const QString& pushInfo) { strPushInfo = pushInfo; };
	int GetExpireTime() { return nExpireTime; };
	void SetExpireTime(int expireTime) { nExpireTime = expireTime; };
	int GetSendStatus() const { return nSendStatus; };
	void SetSendStatus(int sendStatus) { nSendStatus = sendStatus; };
	int GetStatus() const { return nStatus; };
	void SetStatus(int status) { nStatus = status; };
	int GetPriority() const { return nPriority; };
	void SetPriority(int priority) { nPriority = priority; };
	int GetCatalogId() const { return nCatalogId; };
	void SetCatalogId(int catalogId) { nCatalogId = catalogId; };
	const QString& GetCatalog() { return strCatalog; };
    void SetCatalog(const QString& catalog) { strCatalog = catalog; };
	int GetContentType() const { return nContentType; };
	void SetContentType(int contentType) { nContentType = contentType; };
	const QString& GetContent() { return strContent; };
    void SetContent(const QString& content) { strContent = content; };
	int GetIsMyself() const { return nIsMyself; };
	void SetIsMyself(int isMyself) { nIsMyself = isMyself; };
	int GetWidth() const { return nWidth; };
	void SetWidth(int val) { nWidth = val; };
	int GetHeight() const { return nHeight; };
	void SetHeight(int height) { nHeight = height; };
	const QString& GetSenderName() { return strSenderName; };
    void SetSenderName(const QString& senderName) { strSenderName = senderName; };
	int GetAtType() const { return nAtType; };
	void SetAtType(int atType) { nAtType = atType; };
	const QString& GetAtFeeds() { return strAtFeeds; };
    void SetAtFeeds(const QString& atFeeds) { strAtFeeds = atFeeds; };
	const QString& GetFileFormat() { return strFileFormat; };
    void SetFileFormat(const QString& fileFormat) { strFileFormat = fileFormat; };
};

class LOCALSTORAGE_EXPORT st_MessageFault : public TableBase
{
public:
	st_MessageFault()
		:strSessionId("")
		, nMaxSeqId(0)
		, nCount(0)
		, nMinSeqId(0)
	{

	};
	~st_MessageFault(){};
private:
	QString strSessionId;
	int nMaxSeqId;
	int nCount;
	int nMinSeqId;
	
public:
    void SetSessionId(const QString& sessionId){ strSessionId = sessionId; };
	const QString& GetSessionId(){ return strSessionId; };
	void SetMaxSeqId(int MaxSeqId){ nMaxSeqId = MaxSeqId; };
	int GetnMaxSeqId(){ return nMaxSeqId; };
	int GetCount() const { return nCount; };
	void SetCount(int count) { nCount = count; };
	int GetMinSeqId() const { return nMinSeqId; };
	void SetMinSeqId(int minseqId) { nMinSeqId = minseqId; };
};

class LOCALSTORAGE_EXPORT st_MessageOperate : public TableBase
{
public:
	st_MessageOperate()
		:strMsgId("")
		, nSeqId(0)
		, nType(0)
		, strMfrom("")
		, strMto("")
		, nTimestamp(0)
		, nCatalogId(0)
		, strOpMsgId("")
		, strOpFeedId("")
		, strOpName("")
	{

	};
	~st_MessageOperate(){};
private:
	QString strMsgId;
	int nSeqId;
	int nType;
	QString strMfrom;
	QString strMto;
	int nTimestamp;
	int nCatalogId;
	QString strOpMsgId;
	QString strOpFeedId;
	QString strOpName;
	
public:
    void SetMsgId(const QString& msgId){ strMsgId = msgId; };
	const QString& GetMsgId(){ return strMsgId; };
	void SetSeqId(int seqId){ nSeqId = seqId; };
	int GetSeqId(){ return nSeqId; };
	int GetType() const { return nType; };
	void SetType(int type) { nType = type; };
	const QString& GetMfrom() { return strMfrom; };
    void SetMfrom(const QString& mform) { strMfrom = mform; };
	const QString& GetMto() { return strMto; };
    void SetMto(const QString& mto) { strMto = mto; };
	int GetTimestamp() const { return nTimestamp; };
	void SetTimestamp(int timestamp) { nTimestamp = timestamp; };
	int GetCatalogId() const { return nCatalogId; };
	void SetCatalogId(int catalogId) { nCatalogId = catalogId; };
	const QString& GetOpMsgId() { return strOpMsgId; };
    void SetOpMsgId(const QString& opMsgId) { strOpMsgId = opMsgId; };
	const QString& GetOpFeedId()  { return strOpFeedId; };
    void SetOpFeedId(const QString& opFeedId) { strOpFeedId = opFeedId; };
	const QString& GetOpName() { return strOpName; }
	void SetOpName(QString opName) { strOpName = opName; }
};

class LOCALSTORAGE_EXPORT st_MessageAppInfo : public TableBase
{
public:
	st_MessageAppInfo()
		:strAppId("")
		, strAppCode("")
		, strAppTitle("")
		, strAppLittleIcon("")
		, nIsDelete(0)
		, nBtnNumber(0)
		, nChatFlag(0)
	{

	};
	~st_MessageAppInfo(){};
private:
	QString strAppId;
	QString strAppCode;
	QString strAppTitle;
	QString strAppLittleIcon;
	int		nIsDelete;
	int		nBtnNumber;
	int		nChatFlag;
	
public:
    void SetAppId(const QString& appId){ strAppId = appId; };
	const QString& GetAppId(){ return strAppId; };
    void SetAppCode(const QString& appCode){ strAppCode = appCode; };
	const QString& GetAppCode(){ return strAppCode; };
	const QString& GetAppTitle()  { return strAppTitle; };
    void SetAppTitle(const QString& appTitle) { strAppTitle = appTitle; };
	const QString& GetAppLittleIcon() { return strAppLittleIcon; };
    void SetAppLittleIcon(const QString appLittleIcon) { strAppLittleIcon = appLittleIcon; };
	int GetIsDelete() const { return nIsDelete; };
	void SetIsDelete(int isDelete) { nIsDelete = isDelete; };
	int GetBtnNumber() const { return nBtnNumber; };
	void SetBtnNumber(int btnNumber) { nBtnNumber = btnNumber; };
	int GetChatFlag() const { return nChatFlag; };
	void SetChatFlag(int chatFlag) { nChatFlag = chatFlag; };

};

class LOCALSTORAGE_EXPORT st_ChatAppList : public TableBase
{
public:
	st_ChatAppList()
		:strData("")
	{

	};
	~st_ChatAppList(){};
private:
	QString strData;

public:
    void SetData(const QString& data){ strData = data; };
	const QString& GetData(){ return strData; };
};

class LOCALSTORAGE_EXPORT st_ChatSettings : public TableBase
{
public:
	st_ChatSettings()
		:strKey("")
		, strValue("")
		, strComment("")
	{

	};
	~st_ChatSettings(){};
private:
	QString strKey;
	QString strValue;
	QString strComment;

public:
	const QString& GetKey(){ return strKey; };
    void SetKey(const QString& key){ strKey = key; };
	const QString& GetValue() { return strValue; };
    void SetValue(const QString value) { strValue = value; };
	const QString& GetComment() { return strComment; };
    void SetComment(const QString& comment) { strComment = comment; };
};

class LOCALSTORAGE_EXPORT st_GroupInfo : public TableBase
{
public:
	st_GroupInfo()
		:strGroupId("")
		, strCreatorFeedId("")
		, strName("")
		, strNamePinyin("")
		, strPinyinHeader("")
		, strHeaderImage("")
		, strTopic("")
		, strMyFeedId("")
		, nMaxNum(200)
		, nCurrNum(0)
        , nDisturbStatus(0)
		, nGroupType(1)
	{

	};
	~st_GroupInfo(){};
private:
	QString strGroupId;
	QString strCreatorFeedId;
	QString strName;
	QString strNamePinyin;
	QString strPinyinHeader;
	QString strHeaderImage;
	QString strTopic;
	QString strMyFeedId;
	int		nMaxNum;
	int		nCurrNum;
	int     nDisturbStatus;
	int		nGroupType;
	
public:
	const QString& GetGroupId(){ return strGroupId; };
    void SetGroupId(const QString& groupId){ strGroupId = groupId; };
	const QString& GetCreatorFeedId() { return strCreatorFeedId; };
	void SetCreatorFeedId(QString creatorFeedId) { strCreatorFeedId = creatorFeedId; };
	const QString& GetName() { return strName; };
    void SetName(const QString& name) { strName = name; };
	const QString& GetNamePinyin() { return strNamePinyin; };
    void SetNamePinyin(const QString& namePinyin) { strNamePinyin = namePinyin; };
	const QString& GetPinyinHeader() { return strPinyinHeader; };
    void SetPinyinHeader(const QString& pinyinHeader) { strPinyinHeader = pinyinHeader; };
	const QString& GetHeaderImage()  { return strHeaderImage; };
    void SetHeaderImage(const QString& headerImage) { strHeaderImage = headerImage; };
	const QString& GetTopic() { return strTopic; };
    void SetTopic(const QString& topic) { strTopic = topic; };
	const QString& GetMyFeedId() { return strMyFeedId; };
    void SetMyFeedId(const QString& myFeedId) { strMyFeedId = myFeedId; };
	int GetMaxNum() const { return nMaxNum; };
	void SetMaxNum(int maxNum) { nMaxNum = maxNum; };
	int GetCurrNum() const { return nCurrNum; };
	void SetCurrNum(int currNum) { nCurrNum = currNum; };
	int GetDisturbStatus() const { return nDisturbStatus; };
	void SetDisturbStatus(int disturbStatus) { nDisturbStatus = disturbStatus; };
	int GetGroupType() const { return nGroupType; };
	void SetGroupType(int groupType) { nGroupType = groupType; };

};

class LOCALSTORAGE_EXPORT st_GroupMember : public TableBase
{
public:
	st_GroupMember()
		:strGroupId("")
		, strGroupTopic("")
		, strFeedId("")
		, strName("")
		, strHeaderImage("")
		, nStatus(0)
		, nTimestamp(0L)
		, nIsUpdate(0)
	{

	};
	~st_GroupMember(){};
private:
	QString strGroupId;
	QString strGroupTopic;
	QString strFeedId;
	QString strName;
	QString strHeaderImage;
	int		nStatus;
	qint64	nTimestamp;
	int		nIsUpdate;
	QString     permission;

public:
	const QString& GetGroupId(){ return strGroupId; };
    void SetGroupId(const QString& groupId){ strGroupId = groupId; };
	const QString& GetGroupTopic() { return strGroupTopic; };
    void SetGroupTopic(const QString groupTopic) { strGroupTopic = groupTopic; };
	const QString& GetFeedId()  { return strFeedId; }
    void SetFeedId(const QString& feedId) { strFeedId = feedId; };
	const QString& GetName() { return strName; };
    void SetName(const QString& name) { strName = name; };
	const QString& SetHeaderImage() { return strHeaderImage; };
    void GetHeaderImage(const QString& headerImage) { strHeaderImage = headerImage; };
	int GetStatus()  { return nStatus; };
	void SetStatus(int status) { nStatus = status; };
	const QString& GetHeaderImage()  { return strHeaderImage; };
    void SetHeaderImage(const QString& headerImage) { strHeaderImage = headerImage; };
	qint64 GetTimestamp() { return nTimestamp; };
	void SetTimestamp(qint64 timestamp) { nTimestamp = timestamp; };
	int GetIsUpdate() const { return nIsUpdate; };
	void SetIsUpdate(int isUpdate) { nIsUpdate = isUpdate; };
	const QString& GetPermissionType(){ return permission; }
	void SetPermissionType(const QString& type){ permission = type; };
};

class LOCALSTORAGE_EXPORT st_Session : public TableBase
{
public:
	st_Session()
		:strSessionId("")
		, strTopic("")
		, strMyFeedId("")
		, nType(0)
		, nUnreadCount(0)
		, strTitle("")
		, strTitlePinyin("")
		, strPinyinHeader("")
		, strAvatarId("")
		, strDraft("")
		, nLastTime(0)
		, strLastMsg("")
		, strLastMsgId("")
		, nLastMsgSendStatus(0)
		, nTopStatus(0)
		, nSortTime(0)
		, nAtMeStatus(0)
	{

	};
	~st_Session(){};
private:
	QString strSessionId;
	QString strTopic;
	QString strMyFeedId;
	int     nType;
	int	    nUnreadCount;
	QString strTitle;
	QString strTitlePinyin;
	QString strPinyinHeader;
	QString strAvatarId;
	QString strDraft;
	int		nLastTime;
	QString strLastMsg;
	QString strLastMsgId;
	int		nLastMsgSendStatus;
	int		nTopStatus;
	int		nSortTime;
	int		nAtMeStatus;
public:
    QString GetSessionId(){ return strSessionId; };
    void SetSessionId(const QString& sessionId){ strSessionId = sessionId; };
	QString GetTopic() { return strTopic; };
    void SetTopic(const QString topic) { strTopic = topic; };
    QString GetMyFeedId()  { return strMyFeedId; }
    void SetMyFeedId(const QString& myFeedId) { strMyFeedId = myFeedId; }
	int GetType()  { return nType; };
	void SetType(int type) { nType = type; };
	int GetUnreadCount() const { return nUnreadCount; }
	void SetUnreadCount(int unReadCount) { nUnreadCount = unReadCount; }
	QString GetTitle()  { return strTitle; }
    void SetTitle(const QString& title) { strTitle = title; }
	QString GetTitlePinyin() { return strTitlePinyin; }
    void SetTitlePinyin(const QString titlePinyin) { strTitlePinyin = titlePinyin; }
	QString GetPinyinHeader()  { return strPinyinHeader; }
    void SetPinyinHeader(const QString& pinyinHeader ) { strPinyinHeader = pinyinHeader; }
	QString GetAvatarId() { return strAvatarId; }
    void SetAvatarId(const QString& avatarId) { strAvatarId = avatarId; }
	QString GetDraft() { return strDraft; }
	void SetDraft(QString draft) { strDraft = draft; }
	int GetLastTime() const { return nLastTime; }
	void SetLastTime(int lastTime) { nLastTime = lastTime; }
	QString GetLastMsg() { return strLastMsg; }
    void SetLastMsg(const QString& val) { strLastMsg = val; }
	QString GetLastMsgId() { return strLastMsgId; }
	void SetLastMsgId(QString lastMsgId) { strLastMsgId = lastMsgId; }
	int GetLastMsgSendStatus() const { return nLastMsgSendStatus; }
	void SetLastMsgSendStatus(int lastMsgSendStatus) { nLastMsgSendStatus = lastMsgSendStatus; }
	int GetTopStatus() const { return nTopStatus; }
	void SetTopStatus(int topStatus) { nTopStatus = topStatus; }
	int GetSortTime() const { return nSortTime; }
	void SetSortTime(int sortTime) { nSortTime = sortTime; }
	int GetAtMeStatus() const{ return nAtMeStatus; }
	void SetAtMeStatus(int atMeStatus) { nAtMeStatus = atMeStatus; }
};

class LOCALSTORAGE_EXPORT st_SessionBackground : public TableBase
{
public:
	st_SessionBackground()
		:strSessionId("")
		, strBackgroundImagePath("")
	{

	};
	~st_SessionBackground(){};
private:
	QString strSessionId;
	QString strBackgroundImagePath;

public:
	QString GetSessionId(){ return strSessionId; };
    void SetSessionId(const QString& SessionId){ strSessionId = SessionId; };
	QString GetBackgroundImagePath() { return strBackgroundImagePath; };
    void SetBackgroundImagePath(const QString& value) { strBackgroundImagePath = value; };
};
class LOCALSTORAGE_EXPORT st_OwnerData : public TableBase
{
public:
	st_OwnerData()
		:strUserId("")
		, strMobileId("")
	{

	}
	~st_OwnerData(){};

private:
	QString strUserId;
	QString strMobileId;
	QString strExt;

public:

	void setUserId(const QString &userId)
	{
		strUserId = userId;
	}
	const QString &getUserId()
	{
		return strUserId;
	}

	void setMobileId(const QString &mobileId)
	{
		strMobileId = mobileId;
	}
	const QString &getMobileId()
	{
		return strMobileId;
	}

	void setExt(const QString &ext)
	{
		strExt = ext;
	}
	const QString &getExt()
	{
		return strExt;
	}
};
class LOCALSTORAGE_EXPORT st_CompanyInfo : public TableBase
{
public:
	st_CompanyInfo()
		:strComId("")
		, strComName("")
		, strFeedId("")
		, strAddress("")
		, strCardNo("")
		, strCreateTime("")
		, strCreatorId("")
		, strDisplayName("")
		, strDisplayNamePinyin("")
		, strExchangeMode("")
		, strIndustry("")
		, strIntroduction("")
		, strLogo("")
		, strPhone("")
		, strEmail("")
		, strUpdateTime("")
		, strOwnerId("")
		, strOrgCommunication("")
	{

	}
	~st_CompanyInfo(){};

private:
	QString strComId;
	QString strComName;
	QString strFeedId;
	QString strAddress;
	QString strCardNo;
	QString strCreateTime;
	QString strCreatorId;
	QString strDisplayName;
	QString strDisplayNamePinyin;
	QString strExchangeMode;
	QString strIndustry;
	QString strIntroduction;
	QString strLogo;
	QString strPhone;
	QString strEmail;
	QString strUpdateTime;
	QString strOwnerId;
	QString strOrgCommunication;
public:
	void setComId(const QString &comId)
	{
		strComId = comId;
	}
	const QString &getComId()
	{
		return strComId;
	}

	void setComName(const QString &comName)
	{
		strComName = comName;
	}
	const QString &getComName()
	{
		return strComName;
	}

	void setComFeedId(const QString &comFeedId)
	{
		strFeedId = comFeedId;
	}
	const QString &getComFeedId()
	{
		return strFeedId;
	}

	void setComAddress(const QString &comAddress)
	{
		strAddress = comAddress;
	}
	const QString &getComAddress()
	{
		return strAddress;
	}

	void setCardNo(const QString &comCardNo)
	{
		strCardNo = comCardNo;
	}
	const QString &getCardNo()
	{
		return strCardNo;
	}

	void setCreateTime(const QString &comCreateTime)
	{
		strCreateTime = comCreateTime;
	}
	const QString &getCreateTime()
	{
		return strCreateTime;
	}

	void setCreatorId(const QString &comCreatorId)
	{
		strCreatorId = comCreatorId;
	}
	const QString &getCreatorId()
	{
		return strCreatorId;
	}

	void setDisplayName(const QString &comDisplayName)
	{
		strDisplayName = comDisplayName;
	}
	const QString &getDisplayName()
	{
		return strDisplayName;
	}

	void setDisplayNamePinyin(const QString &comDisplayNamePinyin)
	{
		strDisplayNamePinyin = comDisplayNamePinyin;
	}
	const QString &getDisplayNamePinyin()
	{
		return strDisplayNamePinyin;
	}

	void setExchangeMode(const QString &comExchangeMode)
	{
		strExchangeMode = comExchangeMode;
	}
	const QString &getExchangeMode()
	{
		return strExchangeMode;
	}

	void setIndustry(const QString &comIndustry)
	{
		strIndustry = comIndustry;
	}
	const QString &getIndustry()
	{
		return strIndustry;
	}

	void setIntroduction(const QString &comIntroduction)
	{
		strIntroduction = comIntroduction;
	}
	const QString &getIntroduction()
	{
		return strIntroduction;
	}

	void setLogo(const QString &comLogo)
	{
		strLogo = comLogo;
	}
	const QString &getLogo()
	{
		return strLogo;
	}

	void setPhone(const QString &comPhone)
	{
		strPhone = comPhone;
	}
	const QString &getPhone()
	{
		return strPhone;
	}

	void setEmail(const QString &comEmail)
	{
		strEmail = comEmail;
	}
	const QString &getEmail()
	{
		return strEmail;
	}

	void setUpdateTime(const QString &comUpdateTime)
	{
		strUpdateTime = comUpdateTime;
	}
	const QString &getUpdateTime()
	{
		return strUpdateTime;
	}

	void setOwnerId(const QString &comOwnerId)
	{
		strOwnerId = comOwnerId;
	}
	const QString &getOwnerId()
	{
		return strOwnerId;
	}

	void setOrgCommunication(const QString &orgComm)
	{
		strOrgCommunication = orgComm;
	}
	const QString &getOrgCommunication()
	{
		return strOrgCommunication;
	}
};
class LOCALSTORAGE_EXPORT st_ColleagueGroup : public TableBase
{
public:
	st_ColleagueGroup()
		:strComId("")
		, strCreateTime("")
		, strGroupId("")
		, strGroupName("")
		, strOrderValue("")
		, strUpdateTime("")
	{

	};
	~st_ColleagueGroup(){};
private:
	QString strComId;
	QString strCreateTime;
	QString strGroupId;
	QString strGroupName;
	QString strOrderValue;
	QString strUpdateTime;
public:
	const QString& GetComId(){ return strComId; };
    void SetComId(const QString& comId){ strComId = comId; };
	const QString& GetCreateTime() { return strCreateTime; };
    void SetCreateTime(const QString& createTime) { strCreateTime = createTime; };
	const QString& GetGroupId()  { return strGroupId; }
	void SetGroupId(QString groupId) { strGroupId = groupId; }
	const QString& GetGroupName() { return strGroupName; }
	void SetGroupName(QString groupName) { strGroupName = groupName; }
	const QString& GetOrderValue() { return strOrderValue; }
	void SetOrderValue(QString orderValue) { strOrderValue = orderValue; }
	const QString& GetUpdateTime() { return strUpdateTime; }
    void SetUpdateTime(const QString& updateTime) { strUpdateTime = updateTime; }
};

class LOCALSTORAGE_EXPORT st_ColleagueRelation : public TableBase
{
public:
	st_ColleagueRelation()
		:strFeedBelongToGroup("")
		, strFeedId("")
		, strBelongTo("")
		, strGroupId("")
		, strRelationId("")
		, strStaffId("")
		, strUpdateTime("")
		, strCreateTime("")
		, strComId("")
		, strOrderValue("")
	{

	};
	~st_ColleagueRelation(){};
private:
	QString strFeedBelongToGroup;
	QString strFeedId;
	QString strBelongTo;
	QString strGroupId;
	QString strRelationId;
	QString strStaffId;
	QString strUpdateTime;
	QString strCreateTime;
	QString strComId;
	QString strOrderValue;
public:
	const QString& GetFeedBelongToGroup(){ return strFeedBelongToGroup; };
    void SetFeedBelongToGroup(const QString& feedBelongToGroup){ strFeedBelongToGroup = feedBelongToGroup; };
	const QString& GetFeedId() { return strFeedId; }
    void SetFeedId(const QString& feedId) { strFeedId = feedId; }
	const QString& GetBelongTo() { return strBelongTo; }
    void SetBelongTo(const QString& belongTo) { strBelongTo = belongTo; }
	const QString& GetRelationId() { return strRelationId; }
    void SetRelationId(const QString& relationId) { strRelationId = relationId; }
	const QString& GetStaffId() { return strStaffId; }
    void SetStaffId(const QString& staffId) { strStaffId = staffId; }
	const QString& GetCreateTime() { return strCreateTime; };
    void SetCreateTime(const QString& createTime) { strCreateTime = createTime; };
	const QString& GetGroupId()  { return strGroupId; }
	void SetGroupId(QString groupId) { strGroupId = groupId; }
	const QString& GetOrderValue() { return strOrderValue; }
	void SetOrderValue(QString orderValue) { strOrderValue = orderValue; }
	const QString& GetComId() { return strComId; }
	void SetComId(QString comId) { strComId = comId; }
	const QString& GetUpdateTime() { return strUpdateTime; }
    void SetUpdateTime(const QString& updateTime) { strUpdateTime = updateTime; }
};

class LOCALSTORAGE_EXPORT st_SetUp : public TableBase
{
public:
	st_SetUp()
		:strKey("")
		, strValue("")
	{

	};
	~st_SetUp(){};
private:
	QString strKey;
	QString strValue;
public:
	void SetKey(const QString& key){ strKey = key; };
	const QString& GetKey(){ return strKey; };
	void SetValue(const QString& value){ strValue = value; };
	const QString& GetValue(){ return strValue; };
};

class LOCALSTORAGE_EXPORT st_BlackList : public TableBase
{
public:
	st_BlackList()
		:strFeedId("")
		, strPassiveFeedId("")
		, iStatus(0)
	{

	};
	~st_BlackList(){};
private:
	QString strFeedId;
	QString strPassiveFeedId;
	int		iStatus;
public:
	QString GetKey(){ return strFeedId + strPassiveFeedId; }
	void SetFeedId(const QString& feedId){ strFeedId = feedId; };
	const QString& GetFeedId(){ return strFeedId; };
	void SetPassiveFeedId(const QString& passiveFeedId){ strPassiveFeedId = passiveFeedId; };
	const QString& GetPassiveFeedId(){ return strPassiveFeedId; };
	void SetStatus(int status){ iStatus = status; }
	const int GetStatus(){ return iStatus; }
};

class LOCALSTORAGE_EXPORT st_FaceId : public TableBase
{
public:
    st_FaceId(){
    }
    ~st_FaceId(){
    }
public:
    QString get_phone_num(){return _phone_num;}
    void set_phone_num(const QString& phone_num){_phone_num = phone_num;}
    void set_feedId(const QString& feedId){_feedId = feedId;}
    QString get_feedId(){return _feedId;}
private:
    QString _phone_num;
    QString _feedId;
};

class LOCALSTORAGE_EXPORT st_ReadSessionReq : public TableBase
{
public:
	st_ReadSessionReq():_type(0), _readSeqId(0){
	}
	~st_ReadSessionReq(){
	}
public:
	QString GetReqId(){ return _reqId; }
	void SetReqId(const QString& reqId){ _reqId = reqId; }
	QString GetSessionId(){ return _sessionId; }
	void SetSessionId(const QString& sessionID){ _sessionId = sessionID; }
	void SetFrom(const QString& from){ _from = from; }
	QString GetFrom(){ return _from; }
	QString	GetTo(){ return _to; }
	void SetTo(const QString& to){ _to = to; }
	int GetType(){ return _type; }
	void SetType(int type){ _type = type; }
	qlonglong GetReadSeqId(){ return _readSeqId; }
	void SetReadSeqId(qlonglong readSeqId){ _readSeqId = readSeqId; }
private:
	QString _reqId;
	QString _sessionId;
	QString _from;
	QString _to;
	int _type;
	qlonglong _readSeqId;
};

typedef std::shared_ptr<TableBase>						TableBasePtr;
typedef std::shared_ptr<NoticelistTable>				NoticelistTablePtr;
typedef std::shared_ptr<NoticeDetailTable>				NoticeDetailTablePtr;
typedef std::shared_ptr<st_Feed>						st_FeedPtr;
typedef std::shared_ptr<st_JoinStuff>					st_JoinStuffPtr;
typedef std::shared_ptr<st_MyStuff>						st_MyStuffPtr;
typedef std::shared_ptr<st_Version>						st_VersionPtr;
typedef std::shared_ptr<st_LoginUser>					st_LoginUserPtr;
typedef std::shared_ptr<st_BMessage0>					st_BMessage0Ptr;
typedef std::shared_ptr<st_MessageFault>				st_MessageFaultPtr;
typedef std::shared_ptr<st_MessageOperate>				st_MessageOperatePtr;
typedef std::shared_ptr<st_MessageAppInfo>				st_MessageAppInfoPtr;
typedef std::shared_ptr<st_ChatAppList>					st_ChatAppListPtr;
typedef std::shared_ptr<st_ChatSettings>				st_ChatSettingsPtr;
typedef std::shared_ptr<st_GroupInfo>					st_GroupInfoPtr;
typedef std::shared_ptr<st_GroupMember>					st_GroupMemberPtr;
typedef std::shared_ptr<st_Session>						st_SessionPtr;
typedef std::shared_ptr<st_SessionBackground>			st_SessionBackgroundPtr;
typedef std::shared_ptr<st_ColleagueGroup>				st_ColleagueGroupPtr;
typedef std::shared_ptr<st_ColleagueRelation>			st_ColleagueRelationPtr;
typedef std::shared_ptr<st_SetUp>						st_SetUpPtr;
typedef std::shared_ptr<st_BlackList>					st_BlackListPtr;
typedef std::vector<TableBasePtr>						TableBaseVec;
typedef std::shared_ptr<st_CompanyInfo>				    st_CompanyInfoPtr;
typedef std::shared_ptr<st_NewFriend>					st_NewFriendPtr;
typedef std::shared_ptr<st_FaceId>						st_FaceIdPtr;
typedef std::shared_ptr<st_ReadSessionReq>				st_ReadSessionReqPtr;
typedef std::shared_ptr<st_OwnerData>				    st_OwnerDataPtr;
#endif

