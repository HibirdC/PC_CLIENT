#ifndef HOMEPAGEDETAILSAREA_H
#define HOMEPAGEDETAILSAREA_H

#include <QWidget>
#include "DropShadowWidget.h"
#include "DetailsAreaBase.h"

namespace Ui {
class HomePageDetailsArea;
}

class QLabel;
class QStackedWidget;
class QWebEngineView;
class HomePageDetailsArea : public DetailsAreaBase
{
    Q_OBJECT

public:
    HomePageDetailsArea(int id, TNPluginParamPtr pluginParam, QWidget *parent = 0);
    ~HomePageDetailsArea();

    void setCurrentPage(int pageIndex);
    void setUrl(const QString &title, const QString &url);

public Q_SLOTS:
    void slotShowHome(const QString &title, const QString &url);

private Q_SLOTS:
    void slotLoadUrlFinished(bool ok);

private:
    Ui::HomePageDetailsArea *ui;
    QStackedWidget *m_stackedWidget;
    QLabel         *m_titleLabel;
    QWebEngineView *m_webEngineView;

    TNPluginParamPtr m_pluginParam;

    void initHomePageWidget();
    void initDefaultPageWidget();
};

#endif // HOMEPAGEDETAILSAREA_H
