#include "CommentTextEdit.h"

#include <QDebug>

CommentTextEdit::CommentTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
    setAttribute(Qt::WA_InputMethodEnabled);
}

CommentTextEdit::~CommentTextEdit()
{

}

void CommentTextEdit::inputMethodEvent(QInputMethodEvent *e)
{
    qDebug() << "[TNMVD][CommentTextEdit]inputMethodEvent---preeditString="<<e->preeditString();
    if(e->preeditString().isEmpty())
    {
        this->setPlaceholderText(tr(QStringLiteral("想要交换名片").toUtf8().data()));
    }
    else
    {
        this->setPlaceholderText(QString::null);
    }

    QTextEdit::inputMethodEvent(e);
}
