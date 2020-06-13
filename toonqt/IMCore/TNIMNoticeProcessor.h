#ifndef TNIMNOTICEPROCESSOR_H
#define TNIMNOTICEPROCESSOR_H
#include <QString>
#include <QVariantMap>
#include "imcore_global.h"
#include "LocalStorageCommon.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
namespace toonim
{
	class CTNMessage;
}
class TNCMessage;

class IMCORE_EXPORT TNIMNoticeProcessor
{
private:
	TNIMNoticeProcessor();
	~TNIMNoticeProcessor();
public:
	void OnlineMsgToNotice(toonim::CTNMessage* message, TNNoticeInfo& info);
	void OfflineMsgToNotice(const st_BMessage0Ptr bmessage, TNNoticeInfo& info);
	bool ShouldShowNotice(st_BMessage0Ptr bmessage);
	bool ShouldShowNotice(toonim::CTNMessage* bmessage);
	static TNIMNoticeProcessor& GetInstance();
	static void  MessageCastToNotice(const st_BMessage0Ptr bmessage, st_NoticeInfo& data);
	static void  IMMessageCastToNotice(toonim::CTNMessage* bmessage, st_NoticeInfo& data);
private:
	//标题区处理
	void ProcessTitle(TNNoticeInfo& notice, QVariantMap& context);
	//头像区处理
    void ProcessAvaTar(TNNoticeInfo& notice, QVariantMap& context,const QString& to);
	//内容区处理
	void ProcessContent(TNNoticeInfo& notice, QVariantMap& context);
	//操作区处理
	void ProcessOperate(TNNoticeInfo& notice, QVariantMap& context);
    QString GetTitleFromFeedId(const QString& feedId);
};
#endif

