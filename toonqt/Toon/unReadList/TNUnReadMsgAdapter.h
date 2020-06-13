#ifndef TNUNREADMSGADAPTER_H
#define TNUNREADMSGADAPTER_H
#include <QList>
#include <QString>
#include <QPixmap>
#include <QMutex>
#include "TNListModel.h"

class TNUnReadMsgAdapter : public TNModelItemBaseV2
{
public:
	enum ItemType{ Title = 0, normal = 1, buttom = 2 };
public:
	TNUnReadMsgAdapter(int type);
	~TNUnReadMsgAdapter();

	void setSessionId(QString sessionId){ _sessionId = sessionId; }
	const QString  getSessionId(){ return _sessionId; };
	void setFromName(QString fromName){ _fromName = fromName; }
	const QString & getFromName(){ 
		return _fromRemark.isEmpty() ? _fromName : _fromRemark; };

	void setFromFeedId(QString fromFeed){ _fromFeedID = fromFeed; }
	const QString &getFromFeedID(){ return _fromFeedID; }

	void setToFeedID(QString toFeddID){ _toFeedID = toFeddID; }
	const QString &getToFeedID(){ return _toFeedID; }

	void setUnReadCount(int count){ _unRead = count; }
	int  getUnReadCount(){ return _unRead; }

	void setLatestMsgTime(QString latestMsg){ _latestTime = latestMsg; }
	const QString &getLatestMsgTime(){ return _latestTime; }

	void setFromAvator(QString avator){ _fromAvator = avator; }
	const QString &getFromAvator(){ return _fromAvator; }

	int getType(){ return _type; }

	void setNoShowCount(bool status){ _bNoShowCount = status; }
	bool getNoShowCount(){ return _bNoShowCount; }

	void setRemark(QString remark){ _fromRemark = remark; }

private:
	int _type;
	QString _fromName;
	QString _fromFeedID;
	QString _toFeedID;
	int     _unRead;
	QString _latestTime;
	QString _fromAvator;
	QString _sessionId;
	bool    _bNoShowCount;
	QString _fromRemark;
};
class TNUnReadMsgModel : public TNListModel
{
	Q_OBJECT
public:
	explicit TNUnReadMsgModel(QObject *parent = 0);

	Qt::ItemFlags flags(const QModelIndex &index) const;
	void appendData(TNUnReadMsgAdapter *adapter);
	void appendData(QList<TNUnReadMsgAdapter *> adapterList);
	int	 removeRowsExceptKeyword(const QString& keyword);
	bool removeRowByDialogId(const QString& dialogId);
	void insertItem(TNUnReadMsgAdapter * adapter);
	void removeItem(const QString &feedId,int index);
	void resetModel();
	void updateItemInfo(const QString &feedId, const QString &file,
		const QString &name, int count);
private:
	QMutex _mutex;
};
#endif // TNUNREADMSGADAPTER_H
