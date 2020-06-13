#include "tncustomtextedit.h"
#include "common_global.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QDebug>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QUuid>
#include <QTextDocument>
#include <QDebug>
#include "TNPathUtil.h"
#include "tnimagectr.h"
#include "emotion/tnconvertrichedit.h"
#include "TNMVD_global.h"
#include "TNMessageBox.h"


TNCustomTextEdit::TNCustomTextEdit(QWidget *parent)
    : QTextEdit(parent)
    , _isActiveByKey(false)
{
    this->setFontUnderline(false);
    this->setAcceptDrops(true);

    init();
    InitTextObjectHandler();
    setAttribute(Qt::WA_InputMethodEnabled);
    setAcceptDrops(true);
    connect(this->document(),SIGNAL(contentsChange(int,int,int)),
            this,SLOT(onDocmentContentsChange(int,int,int)));
}

TNCustomTextEdit::~TNCustomTextEdit()
{
    if (textHandler != nullptr)
        delete textHandler;
}

void TNCustomTextEdit::contextMenuEvent(QContextMenuEvent *e)
{
    _pop_menu->exec(QCursor::pos());
}

void TNCustomTextEdit::init()
{
    _pop_menu = new QMenu();
    QAction *copy = new QAction(this);
    QAction *paste = new QAction(this);
    QAction *cut = new QAction(this);
    QAction *select_all = new QAction(this);
    copy->setText(tr(QStringLiteral("复制").toUtf8().data()));
	paste->setText(tr(QStringLiteral("粘贴").toUtf8().data()));
	cut->setText(tr(QStringLiteral("剪切").toUtf8().data()));
    select_all->setText(tr(QStringLiteral("全选").toUtf8().data()));

    //清除原有菜单
    _pop_menu->addAction(copy);
    _pop_menu->addAction(paste);
    _pop_menu->addAction(cut);
    _pop_menu->addAction(select_all);

    connect(copy, SIGNAL(triggered()), this, SLOT(customCopy()));
    connect(select_all, SIGNAL(triggered()), this, SLOT(customSelectAll()));
    connect(paste, SIGNAL(triggered()), this, SLOT(customPaste()));
    connect(cut, SIGNAL(triggered()), this, SLOT(customCut()));
}

void TNCustomTextEdit::customCopy()
{
    this->copy();
}

void TNCustomTextEdit::customPaste()
{
    QClipboard* board = QApplication::clipboard();
    if (board->mimeData()->hasUrls()){
        QList<QUrl> urls = board->mimeData()->urls();
        emit inputUrls(urls);

        QList<QUrl>::const_iterator itera = urls.begin();
        for (; itera != urls.end(); ++itera){
            if (!itera->isLocalFile()){
                this->paste();
                break;
            }
        }
        qInfo() << "[Notice] [TNCustomTextEdit] customPaste hasUrls";
    }else if (board->mimeData()->hasImage()){
        QImage image = qvariant_cast<QImage>(board->mimeData()->imageData());
#ifdef Q_OS_WIN
        QString savePath = TNPathUtil::getUserRecFile() + QUuid::createUuid().toString() + ".bmp";
#else
        QString savePath = TNPathUtil::getUserRecFile() + QUuid::createUuid().toString() + ".jpg";
#endif
        savePath.replace("//", "/");
        if(image.save(savePath)){
            QList<QUrl> urls;
            urls.append(QUrl::fromLocalFile(savePath));
            emit inputUrls(urls);
        }
        qInfo() << "[Notice] [TNCustomTextEdit] customPaste hasImage";
    }else if (board->mimeData()->hasHtml()){
        this->paste();
        TNConvertRichEdit::formatPorcess(this,false);
        qInfo() << "[Notice] [TNCustomTextEdit] customPaste hasHtml";
    }else if (board->mimeData()->hasText()){
        this->paste();
        qInfo() << "[Notice] [TNCustomTextEdit] customPaste hasText";
    }else{
        this->paste();
        qInfo() << "[Notice] [TNCustomTextEdit] customPaste other type";
    }
}

void TNCustomTextEdit::customSelectAll()
{
    this->selectAll();
}

void TNCustomTextEdit::customCut()
{
    this->cut();
}

void TNCustomTextEdit::dragEnterEvent(QDragEnterEvent *e)
{
    //notice 日志
    QString strLog = "[Notice] [TNCustomTextEdit] dragEnterEvent ...";
    qInfo() << strLog;
    if(QApplication::activeModalWidget()){
        e->ignore();
        return;
    }
    if (e->mimeData()->hasUrls()){
        //notice 日志
        strLog = "[Notice] [TNCustomTextEdit] dragEnterEvent hasUrls";
        qInfo() << strLog;
        e->acceptProposedAction();
        e->accept();
    }
    return QTextEdit::dragEnterEvent(e);
}

void TNCustomTextEdit::dropEvent(QDropEvent *e)
{
    //notice 日志
    QString strLog = "[Notice] [TNCustomTextEdit] dragEvent ...";
    qInfo() << strLog;
    if(QApplication::activeModalWidget()){
        e->ignore();
        return;
    }
    QTextEdit::dropEvent(e);
    this->undo();
    if (e->mimeData()->hasUrls()){
        QList<QUrl> urls = e->mimeData()->urls();
        emit inputUrls(urls);
        //notice 日志
        strLog = "[Notice] [TNCustomTextEdit] dragEvent hasUrls";
        qInfo() << strLog;
    }
}

bool TNCustomTextEdit::isFolder(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    return fileInfo.isDir();
}

void TNCustomTextEdit::keyPressEvent(QKeyEvent *e)
{
    if (e->key() != Qt::Key_Backspace){
        _isActiveByKey = true;
    }
    if (e->key() == Qt::Key_V && (e->modifiers() & Qt::ControlModifier)){
        customPaste();
    }else{
        return QTextEdit::keyPressEvent(e);
    }
}
void TNCustomTextEdit::InitTextObjectHandler()
{
    QTextDocument* doc = this->document();
    textHandler = new TNTextObject();
    textHandler->setParent(this);

    doc->documentLayout()->registerHandler(TN::TO_ObjectAt, textHandler);
    qDebug() << "register handler complite.";
}
void TNCustomTextEdit::inputMethodEvent(QInputMethodEvent *e)
{
    if(!e->commitString().isEmpty()){
        _isActiveByKey = true;
    }
    QTextEdit::inputMethodEvent(e);
}

void TNCustomTextEdit::dragMoveEvent(QDragMoveEvent *e)
{
    if (e->mimeData()->hasUrls()){
        e->acceptProposedAction();
        e->accept();
    }
    return QTextEdit::dragMoveEvent(e);
}

void TNCustomTextEdit::onDocmentContentsChange(int position, int charsRemoved, int charsAdded)
{
    if(this->document()->characterCount() > MAXTEXTSIZE){
        TNConvertRichEdit::formatPorcess(this,false,0,MAXTEXTSIZE - 1);
    }
}
