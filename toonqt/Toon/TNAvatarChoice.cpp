#include "TNAvatarChoice.h"
#include <QLabel>
#include "TNHttpCloudApi.h"
#include "TNNetAvatarDown.h"
#include <QPainter>
#include <QKeyEvent>

TNAvatarChoice::TNAvatarChoice(TNPluginParamPtr param, QWidget *parent)
	: QWidget(parent)
	, m_pluginParam(param)
{
	ui.setupUi(this);
    this->setObjectName("tableListWidget");
	setWindowFlags(Qt::FramelessWindowHint| Qt::Popup | Qt::NoDropShadowWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground, true);
	//setAttribute(Qt::WA_DeleteOnClose);

	_tableWidget = new QWidget(this);
	_listWidgt = new QTableView(this);
	_listWidgt->setObjectName("AvatarChoicelistWidgt");
	_listWidgt->setShowGrid(false);
	_listWidgt->setMouseTracking(true);
	_listWidgt->setEditTriggers(QAbstractItemView::AllEditTriggers);
	_listWidgt->setSelectionMode(QAbstractItemView::SingleSelection);
	_listWidgt->setSelectionBehavior(QAbstractItemView::SelectItems);

	_listWidgt->setFocusPolicy(Qt::WheelFocus);
	_listDelegate = new TNAvatarChoiceListItemDelegate(_listWidgt);
	_listDelegate->setParentWidget(this);
	_listWidgt->setItemDelegate(_listDelegate);
	_listModel = new TNAvatarChoiceListModel(this);
	_listModel->setTableView(_listWidgt);
	_listWidgt->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
	_listWidgt->setModel(_listModel);
	_listWidgt->horizontalHeader()->setDefaultSectionSize(LIST_AVATARCHOICE_WIDTH);
	_listWidgt->verticalHeader()->setDefaultSectionSize(LIST_AVATARCHOICE_HEIGHT);
	_listWidgt->horizontalHeader()->setVisible(false);
	_listWidgt->verticalHeader()->setVisible(false);

	QHBoxLayout *tableLayoutBox = new QHBoxLayout();
	tableLayoutBox->addWidget(_listWidgt);
    tableLayoutBox->setContentsMargins(0, 0, 0, 0);
	_tableWidget->setLayout(tableLayoutBox);

	QHBoxLayout *main_layout = new QHBoxLayout(this);
	main_layout->addWidget(_tableWidget);
	main_layout->setSpacing(0);
    main_layout->setContentsMargins(8, 0, 0, 0);
	this->setLayout(main_layout);

    QLabel *arrowLabel = new QLabel(QString::null,this);
    arrowLabel->setObjectName("AvatarChoiceLabel");
    arrowLabel->raise();
    arrowLabel->setGeometry(1,14,8,12);
    arrowLabel->show();

	connect(_listWidgt, SIGNAL(clicked(const QModelIndex &)), this, SLOT(OnListClickedSlot(const QModelIndex &)));
	connect(_listDelegate, SIGNAL(createWidgetFinished(const QModelIndex&)), this, SLOT(onItemCreateFinished(const QModelIndex&)), Qt::QueuedConnection);//需要队列，因为不一定实时Item 有效
	connect(_listDelegate, SIGNAL(photoButtonClicked(const QModelIndex &)), this, SLOT(OnListClickedSlot(const QModelIndex &)));
}

TNAvatarChoice::~TNAvatarChoice()
{

}
void TNAvatarChoice::showWidget(bool isShow)
{
	if (isShow)
	{
		this->show();
		this->raise();
		this->activateWindow();
	}
	else
		this->hide();
}
void TNAvatarChoice::OnListClickedSlot(const QModelIndex& index)
{
	TNAvatarChoiceAdapter *adapter = (TNAvatarChoiceAdapter*)index.data().toLongLong();

    if (adapter == NULL)
		return;
	this->hide();
	emit ItemClicked(adapter->getName(), adapter->getDialogID(), adapter->getPhotoResID(), adapter->getAvatarUrl());
}
void TNAvatarChoice::onItemCreateFinished(const QModelIndex& index)
{
	TNAvatarChoiceAdapter *adapter = (TNAvatarChoiceAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return;
	if (adapter->getPhotoResID() == QStringLiteral(":/Resources/toolWidget/defaultAvatar.png") || adapter->getIsForeceRefreshAvator())
	{
		DownLoadAvatar(adapter->getDialogID(), adapter->getAvatarUrl());
	}
}
void TNAvatarChoice::DownLoadAvatar(QString feedId, QString url)
{
	qInfo() << "[Toon][TNAvatarChoice]DownLoadAvatar, url: " << url << " feedId:" << feedId;
	TNNetAvatarDown::GetInstance()->DownLoadFeedAvatar(feedId, url, TNHttpCloudApi::GetInstance()->GetCloudStoken(m_pluginParam), this);
}
void TNAvatarChoice::onAvatarDownLoadFinish(bool success, QString url, QString feedId)
{
	_listModel->UpdateItemAvatar(url, feedId);
}
void TNAvatarChoice::setChoiceResult(QList<TNAvatarChoiceAdapter*> result)
{
	_listModel->ResetModel();
	if (result.size() > 0)
	{
		_listModel->appendData(result);
	}
}

void TNAvatarChoice::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}
