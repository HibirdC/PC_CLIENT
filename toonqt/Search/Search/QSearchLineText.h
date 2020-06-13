#ifndef QSEARCHLINETEXT_H
#define QSEARCHLINETEXT_H

#include <QLineEdit>
#include "CSeachClearLabel.h"
#include "search_global.h"

class SEARCH_EXPORT QSearchLineText : public QLineEdit
{
	Q_OBJECT

public:
	explicit QSearchLineText(QWidget *parent);
	~QSearchLineText();

protected:
	void resizeEvent(QResizeEvent *);
private:
	void initWidgets();
private slots:
	void sltTextChanged(const QString &str);
private:
	CSeachClearLabel   *m_qpClearLbl;
};

#endif // QSEARCHLINETEXT_H
