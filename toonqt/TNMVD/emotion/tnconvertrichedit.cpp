#include "tnconvertrichedit.h"
#include "TNEmojiSingleton.h"
#include "tnimagectr.h"
#include "TNPathUtil.h"
#include <QTextEdit>
#include <QTextDocument>
#include <QTextFragment>
#include <QTextFormat>
#include <QDebug>
#include <QFont>
#include <QFileInfo>

//表情宽高
#define EMOJI_WIDTH		30
#define EMOJI_HEIGHT    30
//链接正则表达式
//#define LINK_RegulaString "((http[s]{0,1}|ftp|www)://[a-zA-Z0-9\\.\\-]+\\.([a-zA-Z]{2,4})(:\\d+)?(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>]*)?)|(www.[a-zA-Z0-9\\.\\-]+\\.([a-zA-Z]{2,4})(:\\d+)?(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>]*)?)"
//#define LINK_RegulaString "((http[s]{0,1}://|ftp://|[.]*)[a-zA-Z0-9\\.\\-]+\\.([a-zA-Z]{2,4}|[0-9]{1,3})(:\\d+)?(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>]*)?)|(www.[a-zA-Z0-9\\.\\-]+\\.([a-zA-Z]{2,4}|[0-9]{1,3})(:\\d+)?(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>]*)?)"
//#define LINK_RegulaString "((http[s]{0,1}|ftp)://[a-zA-Z0-9\\.\\-]+\\.([a-zA-Z]{2,4})(:\\d+)?(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>]*)?)|(www.[a-zA-Z0-9\\.\\-]+\\.([a-zA-Z]{2,4})(:\\d+)?(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>]*)?)|(http[s]{0,1}|ftp)://\\d+\\.\\d+\\.\\d+\\.\\d+[^\\s]*"
#define LINK_RegulaString "((http[s]{0,1}://|ftp://|www)[a-zA-Z0-9\\.\\-]+\\.([a-zA-Z]{2,4}|[0-9]{1,3})(:\\d+)?(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>()]*)?)|([a-zA-Z0-9-]{1,20}[.]?[@]?[a-zA-Z0-9-]{1,20}[.](com|cn|org|cx|net|wang|cc|xin|red|pub|ink|info|xyz|win)(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>]*)?)"

TNConvertRichEdit::TNConvertRichEdit(QObject* parent) : QObject(parent)
{

}

TNConvertRichEdit::~TNConvertRichEdit()
{

}

void TNConvertRichEdit::reverseRichEdit(QTextEdit* editText, const QString& data,bool anaLink)
{
    if(!isHaveEmoji(data)){
        setLink(editText,data,anaLink);
        return;
    }
    QString emoji_path;
    QImage emoji_image;
    int start_index = 0;
    int pre_index = 0;
    int end_index;

    while (emojiImage(data, emoji_image, emoji_path, start_index, end_index)){
        if (!emoji_image.isNull()){
            //表情
            QUrl Uri(QString("file://%1").arg(emoji_path));
            QTextDocument * textDocument = editText->document();
            textDocument->addResource(QTextDocument::ImageResource, Uri, QVariant(emoji_image));
            QTextImageFormat imageFormat;
            imageFormat.setWidth(EMOJI_WIDTH);
            imageFormat.setHeight(EMOJI_HEIGHT);
            imageFormat.setName(emoji_path);
            //表情前面的内容
            QString pre_content = data.mid(pre_index, start_index - pre_index);
            if (!pre_content.isEmpty()){
                if (!isHaveEmoji(pre_content)){//文字
                    setLink(editText,pre_content,anaLink);
                }
             }
             QTextCursor cursor = editText->textCursor();
             cursor.insertImage(imageFormat);
             pre_index = end_index + 1;
             start_index = end_index;
        }else{
            start_index = end_index;
            continue;
        }
    }
    //表情后面的文字
    QString last_content = data.mid(end_index + 1);
    if (!last_content.isEmpty()){
        setLink(editText,last_content,anaLink);
    }
}

bool TNConvertRichEdit::emojiImage(const QString& data, QImage& emoji_image,
    QString& image_path, int &start_index, int& end_index)
{
    QString start_mark = "[";
    QString end_mark = "]";

    start_index = data.indexOf(start_mark, start_index);
    if (start_index == -1){
        return false;
    }
    end_index = data.indexOf(end_mark, start_index + start_mark.length());
    if (end_index == -1){
        return false;
    }

    QString key = data.mid(start_index, end_index - start_index +
        end_mark.length());
    emoji_image = TNEmojiSingleton::GetInstance()->_mapEmoji_Image[key];
    QString value = TNEmojiSingleton::GetInstance()->_mapEmojiI[key];
    image_path = ":/Resources/images/" + value;
    return true;
}

bool TNConvertRichEdit::isHaveEmoji(const QString& data)
{
    QString start_mark = "[";
    QString end_mark = "]";

    int start_index = data.indexOf(start_mark);
    if (start_index == -1){
        return false;
    }
    int end_index = data.indexOf(end_mark, start_index + start_mark.length());
    if (end_index == -1){
        return false;
    }
    QString key = data.mid(start_index, end_index - start_index + end_mark.length());
    TNEmojiSingleton* pEmojiSingleton = TNEmojiSingleton::GetInstance();
    if (pEmojiSingleton->_mapEmojiI.find(key) == pEmojiSingleton->_mapEmojiI.end()){
        return false;
    }
    return true;
}

QString TNConvertRichEdit::replaceEmoji(const QString& image_name)
{
    TNEmojiSingleton* pEmoji = TNEmojiSingleton::GetInstance();
    QMap<QString, QString>::const_iterator itera = pEmoji->_mapEmojiI.begin();
    for (; itera != pEmoji->_mapEmojiI.end(); ++itera){
        if (itera.value() == image_name){
            return itera.key();
        }
    }
    return "";
}

QString TNConvertRichEdit::getLinkUrl(const QString &urlText)
{
    return "<a href='" + urlText + "'>" + urlText + "</a>";
}

void TNConvertRichEdit::setLink(QTextEdit* editText, const QString &str,bool anaLink)
{
    QString content = str;
    //不解析链接
    if(!anaLink){
        editText->textCursor().insertText(content);
        return;
    }
    QRegExp regexp(LINK_RegulaString);
    int pos = content.indexOf(regexp);
    if(pos == -1){
        editText->textCursor().insertText(content);
        return;
    }
    while(pos >= 0){
        if(pos == 0){
            QString tmp = content.mid(0,regexp.matchedLength());
            content = content.mid(regexp.matchedLength());
            editText->textCursor().insertHtml(getLinkUrl(tmp));
        }else{
            QString tmp1 = content.mid(0,pos);
            QString tmp2 = content.mid(pos,regexp.matchedLength());
            content = content.mid(pos+regexp.matchedLength());
            //去掉格式
            QTextCharFormat charFormat;
            charFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);
            QFont text_font("Microsoft Yahei");
            text_font.setPixelSize(14);
            charFormat.setFont(text_font);
            charFormat.setForeground(QBrush(QColor("0x333333")));
            editText->textCursor().insertText(tmp1,charFormat);
            //插入links
            editText->textCursor().insertHtml(getLinkUrl(tmp2));
        }
        pos = content.indexOf(regexp);
    }
    if(content.size() > 0){
        QTextCharFormat charFormat;
        charFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);
        QFont text_font("Microsoft Yahei");
        text_font.setPixelSize(14);
        charFormat.setFont(text_font);
        charFormat.setForeground(QBrush(QColor("0x333333")));
        editText->textCursor().insertText(content,charFormat);
    }
}

void TNConvertRichEdit::setRichEditTextStyle(QTextEdit* editText)
{
    QTextCursor cursor = editText->textCursor();
    for (QTextBlock::iterator it = cursor.block().begin(); !(it.atEnd()); ++it){
        QTextCharFormat charFormat = it.fragment().charFormat();
        charFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);
        QFont text_font("Microsoft Yahei");
        text_font.setPixelSize(14);
        charFormat.setFont(text_font);
        charFormat.setForeground(QBrush(QColor("0x333333")));
        QTextCursor tempCursor = cursor;
        tempCursor.setPosition(it.fragment().position());
        tempCursor.setPosition(it.fragment().position() + it.fragment().length(), QTextCursor::KeepAnchor);
        tempCursor.setCharFormat(charFormat);
    }
}

std::list<edit_content> TNConvertRichEdit::getText(QTextDocument* doc, int start, int end)
{
    std::list<edit_content> list_edit_content;
    QString emojiDir = ":/Resources/images/";//此目录下全表情
    if (end >= 0 && end <= start) return list_edit_content;

    if (start < 0) start = 0;
    bool full = (start == 0) && (end < 0);

    QTextBlock from = full ? doc->begin() : doc->findBlock(start), till = (end < 0) ? doc->end() : doc->findBlock(end);

    if (till.isValid()) till = till.next();

    int possibleLen = 0;
    for (QTextBlock b = from; b != till; b = b.next()) {
        possibleLen += b.length();
    }
    QString result;
    //result.reserve(possibleLen + 1);
    if (!full && end < 0) {
        end = possibleLen;
    }

    for (QTextBlock b = from; b != till; b = b.next()) {
        for (QTextBlock::Iterator iter = b.begin(); !iter.atEnd(); ++iter) {
            QTextFragment fragment(iter.fragment());
            if (!fragment.isValid()) continue;

            int p = full ? 0 : fragment.position(), e = full ? 0 : (p + fragment.length());
            if (!full) {
                if (p >= end || e <= start) {
                    continue;
                }
            }
            QTextCharFormat f = fragment.charFormat();
            if(f.isCharFormat()){
                QString t(fragment.text());
                if (!full) {
                    if (p < start) {
                        t = t.mid(start - p, end - start);
                    } else if (e > end) {
                        t = t.mid(0, end - p);
                    }
                }
                QChar *ub = t.data(), *uc = ub, *ue = uc + t.size();
                for (int i = 0; uc != ue; ++uc,i++) {
                    switch (uc->unicode()) {
                    case 0xfdd0: // QTextBeginningOfFrame
                    case 0xfdd1: // QTextEndOfFrame
                    case QChar::ParagraphSeparator:
                    case QChar::LineSeparator: {
                        *uc = QLatin1Char('\n');
                    } break;
                    case QChar::Nbsp:
                    case QChar::Null:{
                        *uc = QLatin1Char(' ');
                    } break;
                    case QChar::ObjectReplacementCharacter:
                        if(f.isAnchor()){//ObjectAt
                            if(f.anchorName().startsWith("toon://feedid_")){
                                QString anchorName = f.anchorName();
                                QString feed_id,feed_name,showText;
                                int start = anchorName.indexOf("feedid_");
                                int end = anchorName.indexOf("#");
                                if(start != -1 && end != -1){
                                    int temp = sizeof("feedid_");
                                    feed_id = anchorName.mid(start + temp - 1,end - start - temp + 1);
                                }
                                start = anchorName.indexOf("feedName_");
                                end = anchorName.indexOf("#",start);
                                if(start != -1){
                                    int temp = sizeof("feedName_");
                                    feed_name = anchorName.mid(start + temp - 1,end - start - temp + 1);
                                }
                                start = anchorName.indexOf("showText_");
                                if(start != -1){
                                    int temp = sizeof("showText_");
                                    showText = anchorName.mid(start + temp - 1);
                                }
                                //如果at前有文字,先加入
                                if(!result.isEmpty()){
                                    list_edit_content.push_back(edit_content(edit_content::content_type_text,result));
                                    result.clear();
                                }
                                int pos = fragment.position() + i;
                                list_edit_content.push_back(edit_content(edit_content::content_type_objectAt,showText,feed_id,pos,feed_name));
                            }
                        }else if(f.isImageFormat()){
                            QTextImageFormat imgFmt = f.toImageFormat();
                            QString image_name = imgFmt.name();
                            QUrl url(image_name);
                            if(url.isLocalFile()){
                                image_name = url.toLocalFile();
                            }
                            if (image_name.indexOf(emojiDir) != -1){//表情
                                QStringList qs_list = image_name.split("/");
                                image_name = qs_list[qs_list.size() - 1];
                                QString emojiData = replaceEmoji(image_name);
                                result += emojiData;
                            }else{//图片
                                if(!result.isEmpty()){
                                    list_edit_content.push_back(edit_content(edit_content::content_type_text,result));
                                    result.clear();
                                }
                                //图片
                                list_edit_content.push_back(edit_content(edit_content::content_type_image,image_name));
                            }
                        }
                        ub = uc + 1;
                        break;
                    }
                }
                if (uc > ub) result.append(ub, uc - ub);
            }
        }
        result.append('\n');
    }
    result.chop(1);

    list_edit_content.push_back(edit_content(edit_content::content_type_text,result));
    return list_edit_content;
}

void TNConvertRichEdit::formatPorcess(QTextEdit *editText, bool anaLink, int start, int end)
{
    std::list<edit_content> list_edit_content = getText(editText->document(),start,end);
    if(list_edit_content.size() > 0)
        editText->document()->clear();

    for(std::list<edit_content>::const_iterator itera = list_edit_content.begin();
        itera != list_edit_content.end(); ++itera){
        QString content = itera->content;
        bool isHaveImage = itera->type == edit_content::content_type_image;
        bool isHaveObjectAt = itera->type == edit_content::content_type_objectAt;
        if(isHaveImage){//图片
            QString image_path = content;
            QString suffix = TNImageCtr::getImageTypeRetString(image_path);
            QImage image;
            QSize adjust_size = QSize(editText->size().width(),editText->size().height() - 5);
            if(!TNImageCtr::speedLoadImage(image_path,true,image,adjust_size,suffix)){
                continue;
            }
            int path_suffix_index= image_path.lastIndexOf(".");
            if(path_suffix_index != -1){
                QString path_suffix = image_path.mid(path_suffix_index);
                QString file_name = QFileInfo(image_path).fileName();
                if(suffix != path_suffix){
                    QString save_path = TNPathUtil::getUserRecFile()
                        + file_name + suffix;
                    if(image.save(save_path, suffix.mid(1).toStdString().c_str())){
                        image_path = save_path;
                        if(!TNImageCtr::speedLoadImage(image_path,true,image,adjust_size,suffix)){
                            continue;
                        }
                    }
                }
            }

            //insert image
            QUrl Uri("toonpc://image_input.png");
            QTextCursor cursor = editText->textCursor();
            QTextImageFormat imageFormat;
            imageFormat.setWidth(image.width());
            imageFormat.setHeight(image.height());

            QTextDocument * textDocument = editText->document();
            textDocument->addResource(QTextDocument::ImageResource, Uri, QVariant(image));
            imageFormat.setName(image_path);
            cursor.insertImage(imageFormat);
        }else if(isHaveObjectAt){
            QString showText = content;
            QString feedName = itera->at_feedName;
            QString feedId = itera->at_feedId;
            QTextCharFormat format;
            format.setObjectType(TN::TO_ObjectAt);
            format.setProperty(TN::OP_Text, QVariant::fromValue("@" + showText));
            format.setProperty(TN::OP_TextFont, QVariant::fromValue(editText->currentFont().toString()));
            format.setAnchor(true);
            QString tagId = "toon://feedid_" + feedId  + "#" + "feedName_" + feedName + "#" + "showText_" + showText;
            format.setAnchorName(tagId);
            QTextCursor cursor = editText->textCursor();
            cursor.insertText(QString(QChar::ObjectReplacementCharacter), format);
            //将格式置回
            QTextCharFormat charFormat;
            charFormat.setAnchor(false);
            cursor.mergeCharFormat(charFormat);
        }else{//文字
            reverseRichEdit(editText,content,anaLink);
        }
    }
}

QString TNConvertRichEdit::formatAtList(const std::list<edit_content> list_edit_content, QList<QString> &list_feedId)
{
    QString result;
    for(std::list<edit_content>::const_iterator iter = list_edit_content.begin();
        iter != list_edit_content.end();++iter){
        if(iter->type == edit_content::content_type_objectAt){
            QString tmp = "@" + iter->at_feedName + "  ";
            result += tmp;
            list_feedId.push_back(iter->at_feedId);
        }
    }
    return result;
}

QString TNConvertRichEdit::formatAtList(const edit_content &content,QString& feedId)
{
    QString result;
    if(content.type == edit_content::content_type_objectAt){
        result = "@" + content.at_feedName + "  ";
        feedId = content.at_feedId;
    }
    return result;
}
