#ifndef LANGUETOOLS_H
#define LANGUETOOLS_H

#include <QtWidgets/QMainWindow>
#include "ui_languetools.h"

class LangueTools : public QMainWindow
{
	Q_OBJECT

public:
	LangueTools(QWidget *parent = 0);
	~LangueTools();
private:
	int ReadLangueXML(QString xmlFile);
	void ExportExcel(QList<QString>& langueData);
	void ImportExcel(QMap<QString, QString>& langueData, QString excelPath);
	void SaveLangueXMLFromExcel(QString xmlFile, QString ExcelPath);
private:
	Ui::LangueToolsClass ui;
};

#endif // LANGUETOOLS_H
