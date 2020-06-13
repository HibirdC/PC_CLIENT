#ifndef TNCHATDETAILBASE_H
#define TNCHATDETAILBASE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

#include "DetailsAreaBase.h"
#include "model_data/TNModelUserMessage.h"
#include "details_notice/TNMsgDetailModel.h"

class TNChatDetailBase : public DetailsAreaBase
{
	Q_OBJECT

public:
	TNChatDetailBase(int id, QWidget *parent);
	~TNChatDetailBase();

	QWidget* CreateDetailItemFromUserMsg(TNModelUserMessage * userMessage,
		const QModelIndex& index,
        const QSize& parentSize,
		TNMsgDetailModel* detailModel = 0,
		bool is_firstMessage = false,
		bool time_visible = true);
private:
};

#endif // TNCHATDETAILBASE_H
