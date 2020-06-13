#ifndef SETUPDETAILSAREA_H
#define SETUPDETAILSAREA_H

#include <QWidget>
namespace Ui {
class SetUpDetailsArea;
class backgroundWidget;
}

#include "DropShadowWidget.h"
#include "DetailsAreaBase.h"

class QStackedWidget;
class SetUpDetailsArea : public DetailsAreaBase
{
	Q_OBJECT

public:
	SetUpDetailsArea(int id, TNPluginParamPtr pluginParam, QWidget *parent = 0);
	~SetUpDetailsArea();

public slots:
	void setCurrentWidgetIndex(int index);

Q_SIGNALS:
	void updateSettingStatus(QString, int);

private:
	Ui::SetUpDetailsArea *ui;
    Ui::backgroundWidget *backgroudUi;

	QStackedWidget *_stackedWidget;

	TNPluginParamPtr _pluginParam;
};

#endif // SETUPDETAILSAREA_H
