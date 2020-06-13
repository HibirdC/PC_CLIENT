#ifndef TNSEARCHTYPEITEM_H
#define TNSEARCHTYPEITEM_H

#include <QObject>
#include <QList>
#include <QVariant>
#include "search_global.h"
#include "TNSearchTreeItemV2.h"

class SEARCH_EXPORT TNSearchTypeItem : public TNSearchTreeItemV2
{

public:
	explicit TNSearchTypeItem(const QString &TypeName, int itemCount, TNSearchTreeItemV2 *parentItem = 0);
	~TNSearchTypeItem();

	virtual SearchTreeItemEnum getItemGrade() const;

private:
	
};

#endif // TNSEARCHTYPEITEM_H
