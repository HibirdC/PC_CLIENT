#ifndef COMMENTTEXTEDIT_H
#define COMMENTTEXTEDIT_H

#include <QTextEdit>
#include <QInputMethodEvent>

class CommentTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    CommentTextEdit(QWidget *parent = 0);
    ~CommentTextEdit();

protected:
    virtual void inputMethodEvent(QInputMethodEvent *e);

};

#endif // COMMENTTEXTEDIT_H
