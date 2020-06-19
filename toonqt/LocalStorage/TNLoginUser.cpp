#include <memory>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QDebug>


#include "TNLoginUser.h"
#include "TNDataControlServer.h"

TNLoginUser::TNLoginUser()
:TNBaseTable()
{
}


TNLoginUser::~TNLoginUser()
{
}

bool TNLoginUser::InsertDatas(st_LoginUserPtr login)
{
	if (!tableIsExist("LoginUser"))
	{
		return false;
	}
    QString strSql = keyIsExist("LoginUser", "mobile", login->GetMobile()) ? QString("UPDATE LoginUser set token = '%1', pwdState = '%2', checkState = '%3', logDate = '%4', ext = '%5' where mobile = '%6'")
        .arg(login->GetToken()).arg(login->GetPwdState()).arg(login->GetCheckState()).arg(login->GetLogState()).arg(login->GetExt()).arg(login->GetMobile()) : QString("INSERT INTO LoginUser (mobile,token,pwdState,checkState,logDate,ext) VALUES('%1','%2','%3','%4','%5','%6')")
        .arg(login->GetMobile()).arg(login->GetToken()).arg(login->GetPwdState()).arg(login->GetCheckState()).arg(login->GetLogState()).arg(login->GetExt());

	QSqlQuery query(*_db);
	if (!query.exec(strSql))
	{
		QString strLog = query.lastError().text();
		qDebug() << "INSERT/UPDATE INTO Login FAIL" << strLog;
	}
	return true;
}

bool TNLoginUser::Query(TableBaseVec &tableBaseVec, const QString &queryItem, const QString &queryValue)
{
	if (tableIsExist("LoginUser"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec(QString("select *from LoginUser where %1='%2'").arg(queryItem).arg(queryValue));
		if (ret)
		{
			while (query.next())
			{
				st_LoginUserPtr login = std::make_shared<st_LoginUser>();
				login->SetMobile(query.value("mobile").toString());
				login->SetToken(query.value("token").toString());
                login->SetPwdState(query.value("pwdState").toInt());
				login->SetCheckState(query.value("checkState").toInt());
				login->SetLogDate(query.value("logDate").toString());
				login->SetExt(query.value("ext").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(login);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "TNLoginUser::Query FAIL" << strLog;
			return false;
		}
	}
	return false;
}

bool TNLoginUser::GetLatestUser(TableBaseVec &tableBaseVec)
{
	if (!tableIsExist("LoginUser"))
	{
		return false;
	}
	QSqlQuery query(*_db);
	bool ret = query.exec("SELECT * FROM LoginUser order by datetime(logDate) desc limit 0,1");
	if (!ret)
	{
		QString strLog = query.lastError().text();
		qDebug() << "GetLatestUser FAIL" << strLog;
		return false;
	}
	if (query.next())
	{
		st_LoginUserPtr login = std::make_shared<st_LoginUser>();
		login->SetMobile(query.value("mobile").toString());
		login->SetToken(query.value("token").toString());
        login->SetPwdState(query.value("pwdState").toInt());
		login->SetCheckState(query.value("checkState").toInt());
		login->SetLogDate(query.value("logDate").toString());
		login->SetExt(query.value("ext").toString());
		TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(login);
		tableBaseVec.push_back(tempTableBase);
		return true;
	}
	return false;
}
bool TNLoginUser::GetUserIsExist(const QString &userName)
{
	bool result = false;
	if (!tableIsExist("LoginUser"))
	{
		return result;
	}
	QSqlQuery query(*_db);
	QString sql = QString("select * from LoginUser where mobile ='%1'").arg(userName);
	bool ret = query.exec(sql);
	if (ret && query.next())
	{
		result = true;
	}
	return result;
}
bool TNLoginUser::GetAllFields(TableBaseVec &tableBaseVec)
{
	if (tableIsExist("LoginUser"))
	{
		QSqlQuery query(*_db);
		bool ret = query.exec("select *from LoginUser");
		if (ret)
		{
			while (query.next())
			{
				st_LoginUserPtr login = std::make_shared<st_LoginUser>();
				login->SetMobile(query.value("mobile").toString());
				login->SetToken(query.value("token").toString());
                login->SetPwdState(query.value("pwdState").toInt());
				login->SetCheckState(query.value("checkState").toInt());
				login->SetLogDate(query.value("logDate").toString());
				login->SetExt(query.value("ext").toString());
				TableBasePtr tempTableBase = std::dynamic_pointer_cast<TableBase>(login);
				tableBaseVec.push_back(tempTableBase);
			}
			return true;
		}
		else
		{
			QString strLog = query.lastError().text();
			qDebug() << "GetAllFields FAIL" << strLog;
			return false;
		}
	}
	return false;
}


bool TNLoginUser::ClearAll()
{
	if (tableIsExist("LoginUser"))
	{
		QSqlQuery query(*_db);
		query.exec("DELETE FROM LoginUser");
	}
	return true;
}

void TNLoginUser::checkTable()
{

}

void TNLoginUser::createTable()
{
	if (!tableIsExist("LoginUser"))
	{
		QSqlQuery query(*_db);
        query.exec("Create  TABLE MAIN.[LoginUser]([token] varchar(64), [pwdState] int, [checkState] int,[logDate] varchar(24) NOT NULL,[ext] varchar(32),[mobile] varchar(64) PRIMARY KEY UNIQUE NOT NULL)");
	}
    else
    {
        QString strSql = "select * from sqlite_master where name='LoginUser' and sql like '%pwdState%'";
        QSqlQuery query(*_db);
        query.exec(strSql);
        if (!query.next())
        {
            QSqlQuery query(*_db);
            query.exec("ALTER TABLE 'LoginUser' ADD  'pwdState' integer");
        }
    }
}

void TNLoginUser::dropTable()
{
	if (tableIsExist("LoginUser"))
	{
		QSqlQuery query(*_db);
		query.exec("Drop Table MAIN.[LoginUser]");
	}
}
