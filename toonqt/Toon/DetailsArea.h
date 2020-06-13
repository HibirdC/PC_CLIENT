#ifndef DETAILSAREA_H
#define DETAILSAREA_H

#include <QStackedWidget>

#include "PluginExportBase.h"

class DetailsArea : public QStackedWidget
{
    Q_OBJECT

public:
    explicit DetailsArea(QWidget *parent = 0);

    void LoadDetailsLibrary(PluginExportBase *tempMenu, int dimension);

public slots:
    void OnTurnPageSlot(int current_page);
    void slotSetMaximumWidth(bool visible);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent*);

Q_SIGNALS:
    void maxMinSet(bool status);

private:
    std::vector<DetailsAreaBase* > _statkedVec;
};

#endif // DETAILSAREA_H
