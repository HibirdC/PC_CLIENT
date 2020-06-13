#include "languetools.h"
#include <QDomComment>
#include <QFile>
#include <QList>
#include <QDebug>
#include <QAxObject>
#include <QDir>
#include <Windows.h>
LangueTools::LangueTools(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QString xmlpath = "E:\\project\\new_toon_pc_client\\toon_PC_Client\\toonqt\\Toon\\toon_tc.ts";
	QString importExcelPath = "E:\\langugeset-0207.xlsx";
	//ReadLangueXML(xmlpath);
	SaveLangueXMLFromExcel(xmlpath, importExcelPath);
}

LangueTools::~LangueTools()
{

}

void LangueTools::SaveLangueXMLFromExcel(QString xmlFile, QString ExcelPath)
{
	QMap<QString, QString> langueData;
	ImportExcel(langueData, ExcelPath);
	QDomDocument doc;
	QFile file(xmlFile);
	QString error = "";
	int row = 0, column = 0;
	if (!file.open(QIODevice::ReadOnly)) return ;

	if (!doc.setContent(&file, false, &error, &row, &column)){
		qDebug() << "parse file failed:" << row << "---" << column << ":" << error;
		file.close();
		return;
	}
	file.close();
	QDomElement root = doc.documentElement();
	QDomNode node = root.firstChild();
	while (!node.isNull()) {
		QDomElement element = node.toElement(); // try to convert the node to an element.  
		if (!element.isNull()) {
			qDebug() << element.tagName() << ":" << element.text();
			QDomNode nodeson = element.firstChild();
			while (!nodeson.isNull()) {
				QDomElement ContextElement = nodeson.toElement();
				qDebug() << "---" << ContextElement.tagName();
				if (!ContextElement.isNull())
				{
					QDomNode messageNode = ContextElement.firstChild();
					QString sourceLangue;
					while (!messageNode.isNull()) {
						QDomElement sourceNode = messageNode.toElement();
						qDebug() << "---" << sourceNode.tagName();
						if (sourceNode.tagName() == "source")
						{
							QString sourceValue = sourceNode.text();
							sourceLangue = langueData[sourceValue];
						}
						else if (sourceNode.tagName() == "translation")
						{
							QString transValue = sourceNode.text();
							if (transValue.isEmpty())
							{
								qDebug() << "---" << sourceLangue;
								QDomText strLangueText = doc.createTextNode(sourceLangue);//创建元素文本  
								sourceNode.appendChild(strLangueText);
								//sourceNode.setNodeValue(sourceLangue);
							}
						}
						qDebug() << "---" << sourceNode.tagName();
						messageNode = messageNode.nextSibling();
					}
				}
				nodeson = nodeson.nextSibling();
			}
		}
		node = node.nextSibling();
	}
	QFile filexml(xmlFile);
	if (!filexml.open(QFile::WriteOnly | QFile::Truncate))
	{
	    qWarning("error::ParserXML->writeOperateXml->file.open\n");
	    return ;
	 }
	 QTextStream ts(&filexml);
	 ts.reset();
	 ts.setCodec("utf-8");
	 doc.save(ts, 4, QDomNode::EncodingFromTextStream);
	 filexml.close();
}

int LangueTools::ReadLangueXML(QString xmlFile)
{
	QDomDocument doc;
	QFile file(xmlFile);
	QString error = "";
	int row = 0, column = 0;
	if (!file.open(QIODevice::ReadOnly)) return -2;

	if (!doc.setContent(&file, false, &error, &row, &column)){
		qDebug() << "parse file failed:" << row << "---" << column << ":" << error;
		file.close();
		return -1;
	}
	file.close();
	QList<QString> m_listWord;
	QDomElement root = doc.documentElement();
	QDomNode node = root.firstChild();
	while (!node.isNull()) {
		QDomElement element = node.toElement(); // try to convert the node to an element.  
		if (!element.isNull()) {
			qDebug() << element.tagName() << ":" << element.text();
			QDomNode nodeson = element.firstChild();
			while (!nodeson.isNull()) {
				QDomElement ContextElement = nodeson.toElement();
				qDebug() << "---" << ContextElement.tagName();
				if (!ContextElement.isNull())
				{
					QDomNode messageNode = ContextElement.firstChild();
					while (!messageNode.isNull()) {
						QDomElement sourceNode = messageNode.toElement();
						qDebug() << "---" << sourceNode.tagName();
						if (sourceNode.tagName() == "source")
						{
							m_listWord.append(sourceNode.text());
						}
						qDebug() << "---" << sourceNode.tagName();
						messageNode = messageNode.nextSibling();
					}
				}
				nodeson = nodeson.nextSibling();
			}
		}
		node = node.nextSibling();
	}
	ExportExcel(m_listWord);
	return 0;
}

void LangueTools::ExportExcel(QList<QString>& langueData)
{
	OleInitialize(0);
	QAxObject *pApplication = NULL;

	QAxObject *pWorkBooks = NULL;

	QAxObject *pWorkBook = NULL;

	QAxObject *pSheets = NULL;
	QAxObject *pSheet = NULL;
	//create excel
	pApplication = new QAxObject();

	pApplication->setControl("Excel.Application");//连接Excel控件

	//pApplication->dynamicCall("SetVisible(bool)", false);//false不显示窗体

	//pApplication->setProperty("DisplayAlerts", false);//不显示任何警告信息。

	pWorkBooks = pApplication->querySubObject("Workbooks");
	QString fileName = "E:\\langugeset.xlsx";
	QFile file(fileName);
	if (file.exists())
	{
		pWorkBook = pWorkBooks->querySubObject("Open(const QString &)", fileName);
	}
	else
	{
		pWorkBooks->dynamicCall("Add()");
		pWorkBook = pApplication->querySubObject("ActiveWorkBook");
	}
	pSheets = pWorkBook->querySubObject("WorkSheets");
	pSheet = pSheets->querySubObject("Item(int)", 1);
	pSheet->setProperty("Name", "langueSet");
	//add worksheet
	QAxObject *pRange = pSheet->querySubObject("Cells(int,int)", 1, 1);
	pRange->dynamicCall("Value", "source");
	for (int index = 0; index < langueData.size(); index++)
	{
		QAxObject *pRange = pSheet->querySubObject("Cells(int,int)", index+2, 1);
		pRange->dynamicCall("Value", langueData[index]);
		//读取
		//QVariant ret;
		//ret = range->dynamicCall("Value()");
	}
	//保存excel
	pWorkBook->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(fileName));
	//释放excel
	if (pApplication != NULL)
	{
		pApplication->dynamicCall("Quit()");
		delete pApplication;
		pApplication = NULL;
	}
}

void LangueTools::ImportExcel(QMap<QString, QString>& langueData, QString excelPath)
{
	QAxObject excel("Excel.Application");
	//excel.setProperty("Visible", true);
	QAxObject *work_books = excel.querySubObject("WorkBooks");
	work_books->dynamicCall("Open (const QString&)", excelPath);
	QVariant title_value = excel.property("Caption");  //获取标题  
	qDebug() << QString("excel title : ") << title_value;
	QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
	QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets  

	int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目  
	qDebug() << QString("sheet count : ") << sheet_count;
	for (int i = 1; i <= sheet_count; i++)
	{
		QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", i);  //Sheets(int)也可换用Worksheets(int)  
		QString work_sheet_name = work_sheet->property("Name").toString();  //获取工作表名称  
		QString message = QString("sheet ") + QString::number(i, 10) + QString(" name");
		qDebug() << message << work_sheet_name;
	}
	if (sheet_count > 0)
	{
		QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);
		QAxObject *used_range = work_sheet->querySubObject("UsedRange");
		QAxObject *rows = used_range->querySubObject("Rows");
		QAxObject *columns = used_range->querySubObject("Columns");
		int row_start = used_range->property("Row").toInt();  //获取起始行     
		int column_start = used_range->property("Column").toInt();  //获取起始列  
		int row_count = rows->property("Count").toInt();  //获取行数  
		int column_count = columns->property("Count").toInt();  //获取列数  
		row_start = 2;
		for (int i = row_start; i <= row_count; i++)
		{
			QString key;
			QString value;
			for (int j = column_start; j <=column_count; j++)
			{
				QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", i, j);
				QVariant cell_value = cell->property("Value");  //获取单元格内容  
				QString message = QString("row-") + QString::number(i, 10) + QString("-column-") + QString::number(j, 10) + QString(":");
				if (j == 1)
					key = cell_value.toString();
				else if (j == 2)
				{
					//英文对照value
					//value = cell_value.toString();
				}
				else if (j == 3)
				{
					//繁体对照value
					value = cell_value.toString();
				}
				qDebug() << message << cell_value;
			}
			langueData.insert(key, value);
		}
	}
}
