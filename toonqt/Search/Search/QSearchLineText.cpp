#include "QSearchLineText.h"
#include <QEvent>
#include <QPushButton>
#include <QHBoxLayout>

#define CLEAR_BUTTON_WIDTH  14
#define CLEAR_BUTTON_HEIGHT 14
#define CLEAR_BUTTON_MARGIN 5

QSearchLineText::QSearchLineText(QWidget *parent)
: QLineEdit(parent)
{
	initWidgets();
	connect(this, SIGNAL(textChanged(QString)), this, SLOT(sltTextChanged(QString)));
	connect(m_qpClearLbl, SIGNAL(sigClicked()), this, SLOT(clear()));
}

QSearchLineText::~QSearchLineText()
{

}
void QSearchLineText::initWidgets()
{
	QPushButton *searchButton = new QPushButton(this);
	searchButton->setObjectName("searchButton");

	QHBoxLayout *pSearchLayout = new QHBoxLayout();
	pSearchLayout->addWidget(searchButton);
	pSearchLayout->addStretch();
	pSearchLayout->setSpacing(0);
#ifdef Q_OS_WIN
	pSearchLayout->setContentsMargins(4, 0, 0, 0);
#else
	pSearchLayout->setContentsMargins(10, 0, 0, 0);
#endif
	this->setLayout(pSearchLayout);

	//防止文本框输入内容位于按钮之下
	QMargins margins = this->textMargins();
    this->setTextMargins(25, margins.top(), CLEAR_BUTTON_WIDTH + CLEAR_BUTTON_MARGIN, margins.bottom());
	this->setPlaceholderText(tr(QStringLiteral("请输入搜索内容").toUtf8().data()));
	this->setContextMenuPolicy(Qt::NoContextMenu);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setAttribute(Qt::WA_MacShowFocusRect, 0);

	m_qpClearLbl = new CSeachClearLabel(this);
	m_qpClearLbl->setObjectName("searchClearButton");
    m_qpClearLbl->setFixedSize(14, 14);
	m_qpClearLbl->hide();
}

void QSearchLineText::resizeEvent(QResizeEvent *e)
{
    m_qpClearLbl->move(this->width() - CLEAR_BUTTON_WIDTH - CLEAR_BUTTON_MARGIN, (this->height() - CLEAR_BUTTON_HEIGHT) / 2);
	QWidget::resizeEvent(e);
}
void QSearchLineText::sltTextChanged(const QString &str)
{
	if (str.isEmpty())
	{
		m_qpClearLbl->hide();
	}
	else
	{
		m_qpClearLbl->show();
	}
}
