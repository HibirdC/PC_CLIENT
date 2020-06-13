#ifndef TNTEXTOBJECT_H
#define TNTEXTOBJECT_H
#include <QObject>
#include <QTextObjectInterface>
#include <QPainter>
#include <QtPlugin>
#include <QtGui>
#include "TNNameSpace.h"

class TNTextObject : public QObject, public QTextObjectInterface
{
    Q_OBJECT
    Q_INTERFACES(QTextObjectInterface)

public:
    TNTextObject(QObject *parent = 0);
    ~TNTextObject();

    QSizeF intrinsicSize(QTextDocument *doc, int posInDocument,
        const QTextFormat &format)
    {
        /*
        需要计算 非汉字字宽
        */
        QString text = format.property(TN::OP_Text).toString();
        QString fontName = format.property(TN::OP_TextFont).toString();
        QFont curFont;
        curFont.fromString(fontName);
        QFontMetrics fm(curFont);
        return QSizeF(fm.width(text)+4, fm.height());
    }
    void drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc,
        int posInDocument, const QTextFormat &format)
    {
        QString text = format.property(TN::OP_Text).toString();
        QString fontName = format.property(TN::OP_TextFont).toString();
        QFont curFont;
        curFont.fromString(fontName);

        QRectF reRect;
        reRect.setRect(rect.x(), rect.y() + 3, rect.width(), rect.height());
        painter->setFont(curFont);
        painter->save();
        painter->setPen(Qt::blue);
        painter->drawText(reRect, text);
        painter->restore();
    }
    std::size_t utf8_length(std::string const &s) {
        std::size_t len = 0;
        std::string::const_iterator begin = s.begin(), end = s.end();
        while (begin != end) {
            unsigned char c = *begin;
            int n;
            if ((c & 0x80) == 0)    n = 1;
            else if ((c & 0xE0) == 0xC0) n = 2;
            else if ((c & 0xF0) == 0xE0) n = 3;
            else if ((c & 0xF8) == 0xF0) n = 4;
            else throw std::runtime_error("utf8_length: invalid UTF-8");

            if (end - begin < n) {
                throw std::runtime_error("utf8_length: string too short");
            }
            for (int i = 1; i < n; ++i) {
                if ((begin[i] & 0xC0) != 0x80) {
                    throw std::runtime_error("utf8_length: expected continuation byte");
                }
            }
            len += n;
            begin += n;
        }
        return len;
    }
};

#endif // TNTEXTOBJECT_H
