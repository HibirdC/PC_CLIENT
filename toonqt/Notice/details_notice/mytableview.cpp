#include "mytableview.h"
#include <QScrollBar>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>
#include <QApplication>
#include "TNMsgDetailItemWidget.h"


MyTableView::MyTableView(QWidget *parent)
	: QTableView(parent)
	, _isScrollToBottom(true)
{
    setAcceptDrops(true);
    setDragEnabled(true);
    viewport()->setAcceptDrops(true);
	connect(verticalScrollBar(), SIGNAL(rangeChanged(int, int)), this,
		SLOT(VerticalScrollBaScrollToBottom(int, int)));
	connect(verticalScrollBar(), SIGNAL(valueChanged(int)),
		this, SLOT(VerticalScrollbarMoved(int)));
}

MyTableView::~MyTableView()
{

}

void MyTableView::updateGeometries()
{
	QTableView::updateGeometries();
	this->verticalScrollBar()->setSingleStep(10);
}

void MyTableView::VerticalScrollBaScrollToBottom(int min, int max)
{
    Q_UNUSED(min);
	if (_isScrollToBottom)
		verticalScrollBar()->setValue(max);
}

void MyTableView::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);
    int rowCount = this->model()->rowCount();
    for (int i = 0; i < rowCount; i++){
        QModelIndex qindex = this->model()->index(i, 0);
        TNMsgDetailItemWidget* itemWidget = static_cast<TNMsgDetailItemWidget*>
            (this->indexWidget(qindex));
        if (itemWidget != NULL){
            itemWidget->reSize(size());
        }
    }
}

void MyTableView::VerticalScrollbarMoved(int value)
{
	if (value != verticalScrollBar()->maximum()){
		_isScrollToBottom = false;
	}else{
		_isScrollToBottom = true;
	}
}

void MyTableView::setScrollToBottom(bool flag)
{
	_isScrollToBottom = flag;
}

bool MyTableView::getIsScrollToBottom()
{
    return _isScrollToBottom;
}

void MyTableView::dropEvent(QDropEvent *event)
{
    if(QApplication::activeModalWidget()){
        event->ignore();
        return;
    }
    if (event->mimeData()->hasUrls()){
        QList<QUrl> urls = event->mimeData()->urls();
        event->acceptProposedAction();
        event->accept();
        emit dropInUrls(urls);
    }
    return QTableView::dropEvent(event);
}

void MyTableView::dragEnterEvent(QDragEnterEvent *event)
{
    if(QApplication::activeModalWidget()){
        event->ignore();
        return;
    }
    if (event->mimeData()->hasUrls()){
        QString strLog = "[Notice] [MyTableView] dragEnterEvent hasUrls";
        qInfo() << strLog;
        event->acceptProposedAction();
        event->accept();
    }else{
        event->ignore();
    }
}

void MyTableView::dragMoveEvent(QDragMoveEvent *event)
{
    if(QApplication::activeModalWidget()){
        event->ignore();
        return;
    }
    if (event->mimeData()->hasFormat("text/uri-list")){
        event->acceptProposedAction();
        event->accept();
    }else{
       if (event->mimeData()->hasUrls()){
            event->acceptProposedAction();
            event->accept();
            QString strLog = "[Notice] [MyTableView] dragMoveEvent hasUrls";
            qInfo() << strLog;
        }else{
            event->ignore();
        }
    }
}
