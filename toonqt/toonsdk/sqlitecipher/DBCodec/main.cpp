#include <QtWidgets/QApplication>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QSqlError>

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	if (argc == 1)
	{
		qDebug() << "Usage:";
		qDebug() << "DBCodec -t 0/1 -p path";
		qDebug() << "        -t: 1 encode ,0 decode";
		qDebug() << "        -p: data base path";
		return 0;
	}

	QStringList argvList = QCoreApplication::arguments();
	if (argvList.size() != 5)
	{
		qDebug() << "the parameter is not valid";
		return 0;
	}
	argvList.removeFirst();
	int type = -1;
	QString path;
	if (argvList[0] == "-t")
	{
		type = argvList[1].toInt();
	}
	if (argvList[2] == "-p")
	{
		path = argvList[3];
	}

	QStringList driverList = QSqlDatabase::drivers();
	if (!driverList.contains("SQLITECIPHER"))
	{
		qDebug() << "the driver is not valid,please add sqlitecipher";
		return 0;
	}
	QSqlDatabase dbconn = QSqlDatabase::addDatabase("SQLITECIPHER", path);
	dbconn.setDatabaseName(path);
	dbconn.setPassword("tN8fL3YuD9");
	if (type == 0)
	{
		dbconn.setConnectOptions("QSQLITE_REMOVE_KEY");
	}
	else if (type == 1)
	{
		dbconn.setConnectOptions("QSQLITE_CREATE_KEY");
	}
	else
	{
		qDebug() << "type is not valid . 0 : decode,1 : encode";
		return 0;
	}
	QFile file(path);
	if (!file.exists())
	{
		qDebug() << "DB is not valid .";
		return 0;
	}
	if (!dbconn.open()) {
		qDebug() << "Can not open connection,please confirm the DB is valid .";
		qDebug() << "error: " << dbconn.lastError().driverText();
		return 0;
	}
	qDebug() << "Success";
	return 1;
}
