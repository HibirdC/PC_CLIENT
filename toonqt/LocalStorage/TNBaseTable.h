#ifndef TNBaseTable_H
#define TNBaseTable_H
#include <memory>
#include <QSqlDatabase>
#include <QSqlRecord>

class TNBaseTable
{
protected:
	QSqlDatabase* _db;
	QSqlDatabase _poolDb;
    bool _tableExist;

    virtual bool tableIsExist(QString tableName);
	virtual bool keyIsExist(const QString& tableName, const QString& key, const QString& Value);
public:
	TNBaseTable();
	virtual ~TNBaseTable();

	virtual void checkTable() = 0;
	virtual void createTable() = 0;
	virtual void dropTable() = 0;

    bool beginTransaction();

    bool commitTransaction();
	void SetDBConnect(QSqlDatabase* dbConnect);
};
typedef std::shared_ptr<TNBaseTable> TNBaseTablePtr;
#endif // TNBaseTable_H
