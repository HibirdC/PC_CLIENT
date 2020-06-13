#ifndef TNCUSTOMTEXTEDIT_H
#define TNCUSTOMTEXTEDIT_H

#include <QTextEdit>
#include <QMenu>
#include "tntextobject.h"
#define MAXTEXTSIZE 2000

class TNCustomTextEdit : public QTextEdit
{
	Q_OBJECT

public:
	TNCustomTextEdit(QWidget *parent = 0);
	~TNCustomTextEdit();
	bool _isActiveByKey;
public slots:
    void customPaste();

Q_SIGNALS:
    void inputUrls(QList<QUrl> urls);
private slots:
	void customCopy();
	void customSelectAll();
	void customCut();
    void onDocmentContentsChange(int position,int charsRemoved,int charsAdded);
protected:
    virtual void contextMenuEvent(QContextMenuEvent *e);
	void init();
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dragMoveEvent(QDragMoveEvent *e);
    virtual void dropEvent(QDropEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);
	virtual void inputMethodEvent(QInputMethodEvent *e);
private:
    //void dealFiles(const QString& filePath);
    bool isFolder(const QString& filePath);
	void InitTextObjectHandler();
private:
	QMenu *_pop_menu;
	TNTextObject* textHandler;
};

#endif // TNCUSTOMTEXTEDIT_H
