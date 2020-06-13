#ifndef DEAL_DRAFT_DATA_H
#define DEAL_DRAFT_DATA_H
#include <QObject>

class DealDraftData{
public:
    DealDraftData();
    ~DealDraftData();
    static QString convertAtToPlainText(const QString& draft_json);
    static QString delAllSpecialChar(QString content);
};

#endif
