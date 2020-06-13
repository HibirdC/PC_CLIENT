#include "TNCompanyItem.h"
#include "TNDepartmentItem.h"
#include "TNStaffItem.h"
#include <QStringList>

TNCompanyItem::TNCompanyItem(const QString &companyName, TNCardCaseTreeItem *parent) :
    TNCardCaseTreeItem(QList<QVariant>()<<companyName, parent)
{

}

TNCompanyItem::~TNCompanyItem()
{
}

TNCardCaseTreeItem::ColleagueTreeItem TNCompanyItem::getItemGrade() const
{
    return TNCardCaseTreeItem::Company;
}
