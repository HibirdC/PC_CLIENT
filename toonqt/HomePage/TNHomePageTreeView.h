#ifndef TNHomePageTreeView_H
#define TNHomePageTreeView_H

#include <QObject>
#include <QTreeView>

class TNHomePageTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit TNHomePageTreeView(QWidget *parent = Q_NULLPTR);
    ~TNHomePageTreeView();

protected:
    virtual void updateGeometries();
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // TNHomePageTreeView_H
