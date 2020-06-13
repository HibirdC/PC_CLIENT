#include "TNSearchItemWidget.h"

TNSearchItemWidget::TNSearchItemWidget(const QString labelName, bool show, const QModelIndex &index, QWidget *parent)
	: QWidget(parent),
	ui(new Ui::TNSearchItemWidget),
	_index(index)
{
	ui->setupUi(this);
	ui->searchShowAllButton->setFixedWidth(60);
	ui->searchShowAllButton->setVisible(show);
	ui->searchShowAllButton->setCursor(Qt::PointingHandCursor);
	ui->searchLetterName->setText(labelName);
	connect(ui->searchShowAllButton, SIGNAL(clicked(bool)), SLOT(onShowButtonClicked(bool)));
}

TNSearchItemWidget::~TNSearchItemWidget()
{
	delete ui;
}
void TNSearchItemWidget::setShowButtonName(QString text)
{
	ui->searchShowAllButton->setText(text);
}
void TNSearchItemWidget::onShowButtonClicked(bool showType)
{
	QString tag = ui->searchLetterName->text();
	if (tag == tr(QStringLiteral("好友").toUtf8().data()))
	{
		tag = "AFriend";
	}
	else if (tag == tr(QStringLiteral("同事").toUtf8().data()))
	{
		tag = "BColleague";
	}
	else if (tag == tr(QStringLiteral("社区").toUtf8().data()))
	{
		tag = "CGroup";
	}
	else if (tag == tr(QStringLiteral("群聊").toUtf8().data()))
	{
		tag = "DGroupChat";
	}
	emit showButtonClicked(_index, tag, ui->searchShowAllButton->text(), showType);
	if (!showType)
		setShowButtonName(tr(QStringLiteral("显示全部").toUtf8().data()));
	else
		setShowButtonName(tr(QStringLiteral("收起").toUtf8().data()));
}
void TNSearchItemWidget::setShowButtonStatus(bool status)
{
	ui->searchShowAllButton->setChecked(status);
}