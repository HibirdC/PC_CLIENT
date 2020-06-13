#include "TNEmotionLineEdit.h"

#include <QDebug>
#include <QMimeData>
#include <QClipboard>
#include <QApplication>
#include "TNEmotionPictureTextConverter.h"

TNEmotionLineEdit::TNEmotionLineEdit(QWidget *parent)
    : QLineEdit(parent)
{

}

TNEmotionLineEdit::~TNEmotionLineEdit()
{

}

void TNEmotionLineEdit::focusInEvent(QFocusEvent *e)
{
    QClipboard* board = QApplication::clipboard();
    const QMimeData *mimeData = board->mimeData();
    if (mimeData && mimeData->hasHtml())
    {
        QString htmlText = mimeData->html();
        qInfo() << "[TNMVD][TNEmotionLineEdit]htmlText=" << htmlText;
        QString emotionText = TNEmotionPictureTextConverter::emotionPictureToText(htmlText);
        qInfo() << "[TNMVD][TNEmotionLineEdit]emotionText=" << emotionText;
        board->setText(emotionText);
    }

    QLineEdit::focusInEvent(e);
}
