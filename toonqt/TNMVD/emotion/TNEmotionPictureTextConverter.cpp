#include "TNEmotionPictureTextConverter.h"

#include <QDebug>
#include <QTextBlock>
#include <QTextDocument>

#include "tnconvertrichedit.h"

TNEmotionPictureTextConverter::TNEmotionPictureTextConverter(QObject *parent)
    : QObject(parent)
{

}

TNEmotionPictureTextConverter::~TNEmotionPictureTextConverter()
{

}

QString TNEmotionPictureTextConverter::emotionPictureToText(const QString &htmlText)
{
    const QString emojiDir = ":/Resources/images/";
    QTextDocument *textDocument = new QTextDocument();
    textDocument->setHtml(htmlText);
    QString result;
    QTextBlock textBlock = textDocument->begin();
    while (textBlock.isValid())
    {
        for (QTextBlock::iterator it = textBlock.begin(); it != textBlock.end(); ++it)
        {
            QTextFragment currentFragment = it.fragment();
            if (currentFragment.isValid())
            {
                if (currentFragment.charFormat().isImageFormat()) //图片
                {
                    QTextImageFormat imageFormat = currentFragment.charFormat().toImageFormat();
                    QString imageFileName = imageFormat.name();

                    // 只处理本地的图片资源文件
                    QUrl url(imageFileName);
                    if (url.isValid())
                    {
                        if (url.isLocalFile())
                        {
                            imageFileName = url.fileName();
                        }
                        else
                        {
                            continue;
                        }
                    }

                    // 如果是表情资源图片
                    if (imageFileName.indexOf(emojiDir) != -1)
                    {
                        QStringList fileNamePartList = imageFileName.split("/");
                        imageFileName = fileNamePartList.last();
                        QString emojiData = TNConvertRichEdit::replaceEmoji(imageFileName);
                        result += emojiData;
                        //表情后面的换行
                        int position = currentFragment.position();
                        if (position >= 0 && ((position + 1) < htmlText.size()))
                        {
                            if (htmlText.at(position + 1) == '\n')
                            {
                                result += "\n";
                            }
                        }
                    }
                    else
                    {   // 如果是普通图片，这里暂时不做处理
                        Q_ASSERT(!"error! 图片未处理");
                        qInfo()<<"error! The picture is not allowed to be used as a title.";
                    }
                }
                else if (currentFragment.charFormat().isCharFormat()) //文字
                {
                    QString content = currentFragment.text();
                    int index = htmlText.indexOf(content);
                    if (index != -1)
                    {
                        if (htmlText.mid(index + content.length(), 1) == "\n")
                            content += "\n";
                    }
                    result += content;
                }
            }
        }

        textBlock = textBlock.next();
    }

    return result;
}
