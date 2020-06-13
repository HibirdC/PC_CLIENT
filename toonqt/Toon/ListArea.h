#ifndef LISTAREA_H
#define LISTAREA_H

#include <QStackedWidget>

#include "common_global.h"
#include "PluginExportBase.h"

class ListArea : public QStackedWidget
{
    Q_OBJECT

public:
    explicit ListArea(TNPluginParamPtr pluginParam, QWidget *parent = 0);

    void LoadListLibrary(PluginExportBase *tempMenu, int dimension);

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent*);

public slots:
    void turnPage(int current_page);
    void doubleClickPage(int current_page);

Q_SIGNALS:
    void maxMinSet(bool status);
    void turnPageSignal(bool status);
	void sendCurrentSelectedPage(int page);

private:
    void init();

private:
    TNPluginParamPtr _pluginParam;
    int              _latestSelectedPage; //记录上一次选中的模块
};

#endif // LISTAREA_H
