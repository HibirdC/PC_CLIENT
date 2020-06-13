#ifndef TNCONVERTRICHEDIT_H
#define TNCONVERTRICHEDIT_H

#include "TNMVD_global.h"
#include <QObject>
#include <list>

class QTextEdit;
class QTextDocument;

struct edit_content{
public:
    enum edit_content_type{
        content_type_text = 1,
        content_type_image,
        content_type_objectAt
    };

    edit_content(){
    }
    edit_content(edit_content_type edit_type,QString cust_content,QString feed_id = "",int at_pos = -1,QString feed_name = ""){
        type = edit_type;
        content = cust_content;
        pos = at_pos;
        at_feedId = feed_id;
        at_feedName = feed_name;
    }

    edit_content_type type = content_type_text;
    QString content;
    int pos = -1;
    QString at_feedId;
    QString at_feedName;
};

class TNMVD_EXPORT TNConvertRichEdit : public QObject
{
    Q_OBJECT
public:
    TNConvertRichEdit(QObject* parent = NULL);
    ~TNConvertRichEdit();
    static void reverseRichEdit(QTextEdit* editText, const QString& data,bool anaLink = true);
    static bool isHaveEmoji(const QString& data);
    /*
    替换表情为字符[]
    */
    static QString replaceEmoji(const QString& image_name);
    /*
    去掉下划线,设置默认字体,颜色...
    */
    static void setRichEditTextStyle(QTextEdit* editText);
    /*
    获取副文本内容,表情转换为[微笑]....
    */
    static std::list<edit_content> getText(QTextDocument* doc, int start, int end);
    /*
    格式化富文本
    */
    static void formatPorcess(QTextEdit* editText,bool anaLink = true,int start = 0,int end = -1);
    /*
     * 将at转成feedid_list
    */
    static QString formatAtList(const std::list<edit_content> list_edit_content, QList<QString>& list_feedId);
    static QString formatAtList(const edit_content& content,QString& feedId);
private:
    static bool emojiImage(const QString& data, QImage& emoji_image,
        QString& image_path, int &start_index, int& end_index);
    static QString getLinkUrl(const QString& urlText);
    static void setLink(QTextEdit* editText, const QString &str, bool anaLink = true);
};

#endif // TNCONVERTRICHEDIT_H
