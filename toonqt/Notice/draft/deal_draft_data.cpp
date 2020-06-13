#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "deal_draft_data.h"

DealDraftData::DealDraftData(){
}

DealDraftData::~DealDraftData(){

}

QString DealDraftData::convertAtToPlainText(const QString& draft_json)
{
    QString draft_plain_txt;
    if(draft_json.isEmpty()){
        return "";
    }

    QJsonParseError jsonError;
    QByteArray array;
    array.append(draft_json);
    QJsonObject jsonObject = QJsonDocument::fromJson(array, &jsonError).object();
    if (jsonError.error != QJsonParseError::NoError)
        return "";
    QJsonArray draftArray;
    if(jsonObject.find("draft") != jsonObject.end()){
        draftArray = jsonObject["draft"].toArray();
        for(QJsonArray::const_iterator itera = draftArray.begin(); itera != draftArray.end(); ++itera){
            if(!itera->isObject())
                continue;
            QJsonObject temp = itera->toObject();
            if(temp.find("at") != temp.end()){
                QJsonObject atObject = temp["at"].toObject();
                QString showText = atObject["showText"].toString();
                draft_plain_txt.append("@" + showText + " ");
            }else if(temp.find("text") != temp.end()){
                QJsonObject textObject = temp["text"].toObject();
                QString text = textObject["text"].toString();
                text = text.replace(QChar::ObjectReplacementCharacter,"");
                draft_plain_txt += text;
            }
        }
    }
    return draft_plain_txt;
}

QString DealDraftData::delAllSpecialChar(QString content){
    QRegExp rx("[\\a\\f\\r\\t\\n\\v]");
    int pos = 0;
    while ((pos = rx.indexIn(content, pos)) != -1){
        content.remove(pos,rx.matchedLength());
    }
    return content;
}
