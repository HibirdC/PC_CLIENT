#ifndef MyTableView_H
#define MyTableView_H
#include <QTableView>
#include <QUrl>

class MyTableView : public QTableView
{
	Q_OBJECT

public:
    MyTableView(QWidget *parent = 0);
    ~MyTableView();

	void setScrollToBottom(bool flag);
    bool getIsScrollToBottom();
Q_SIGNALS:
    void dropInUrls(QList<QUrl> urls);
private slots:
	void VerticalScrollBaScrollToBottom(int, int);
	void VerticalScrollbarMoved(int);
protected:
	virtual void updateGeometries();
    virtual void dropEvent(QDropEvent *event) override;
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
private:
	bool					   _isScrollToBottom;//是否需要滚动条到底部
};

#endif // MyTableView_H
