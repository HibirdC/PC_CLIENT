#ifndef CWQMSGDETAILMODEL_H
#define CWQMSGDETAILMODEL_H

#include <QTableView>
#include <QMutex>
#include "TNTableModel.h"
#include "model_data/TNModelUserMessage.h"
#include "TNHttpCloudApi.h"

class TNChatDetailBase;
typedef QList<TNModelUserMessage*> LIST_MESSAGE;

class TNMsgDetailModel : public TNTableModel
{
    Q_OBJECT
public:
    explicit TNMsgDetailModel(QObject *parent = 0);
    ~TNMsgDetailModel();

    void setChatDetailBase(TNChatDetailBase *chatDetailBase);
    bool insertData(TNModelUserMessage* userMsg);
    bool insertData(int index, TNModelUserMessage *userMsg);
    void insertData(int index, LIST_MESSAGE &listUserMsg);
    void removeData(int index, int count);
    void removeData(TNModelUserMessage *userMsg);
    void updateSendName(const QString& feedId, const QString& remark);
	TNModelUserMessage* updateFileData(const QString& msgId, const QString& fileUrl,
		bool success = false, int progress = 0);
	TNModelUserMessage* updateAudioDataReaded(const QString& msgId,bool isReaded = true);
    TNModelUserMessage* updateMsgFeedback(const QString& msgId, int msg_status);
	TNModelUserMessage* updateAudioDataDownloaded(const QString& msgId, const QString& fileUrl,
		bool success = true);
    TNModelUserMessage* updateAvatorIcon(const QString& msgId, const QString& file_path);
    void updateAvatorIconByFeedId(const QString& feedId, const QString& file_path);
    TNModelUserMessage* updateMsgFileStatus(const QString& msgId, TNMsgFileStatus status);
    TNModelUserMessage* updateMsgStatus(const QString& msgId,TNMsgStatus status);
    TNModelUserMessage* updateMsgFileProgress(const QString& msgId,int progress);
    TNModelUserMessage* lastData();
    QModelIndex getMsgIndex(const QString& msgId);

	void setPluginParam(const TNPluginParamPtr& param) { _pluginParam = param; }
	TNPluginParamPtr getPluginParam() { return _pluginParam; }

	int getModelSize();
protected:
    virtual QStringList mimeTypes() const override;
    virtual Qt::DropActions supportedDragActions() const override;
    virtual QMimeData* mimeData(const QModelIndexList &indexes) const override;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
Q_SIGNALS:
    void reSendData(TNModelUserMessage data);
public:
    QVariant data(const QModelIndex &index, qint32 role = Qt::DisplayRole) const;
	void setTableView(QTableView* tableView);
	int findItemData(const QString& msgId,TNModelUserMessage** itemData);
private:
    TNChatDetailBase *_chatDetailBase;
	QTableView*		  _tableView;
	TNPluginParamPtr  _pluginParam;
	QMutex			  _mutex;
};

#endif // CWQMSGDETAILMODEL_H
