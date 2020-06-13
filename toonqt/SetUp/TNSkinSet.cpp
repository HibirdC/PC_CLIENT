#include "TNSkinSet.h"
#include "TNDataControlServer.h"
#include "TNSettingData.h"

TNSkinSet::TNSkinSet(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	InitUI();
	connect(ui.skinBlueBtn, SIGNAL(clicked()), this, SLOT(OnClickApplySkinBlueSlot()));
	connect(ui.skinPinkBtn, SIGNAL(clicked()), this, SLOT(OnClickApplySkinPinkSlot()));
	connect(ui.skinGreenBtn, SIGNAL(clicked()), this, SLOT(OnClickApplySkinGreenSlot()));
	connect(ui.skinTeaBtn, SIGNAL(clicked()), this, SLOT(OnClickApplySkinTeaSlot()));
	connect(ui.skinOrangeBtn, SIGNAL(clicked()), this, SLOT(OnClickApplySkinOrangeSlot()));
	connect(ui.skinOrchidBtn, SIGNAL(clicked()), this, SLOT(OnClickApplySkinOrchidSlot()));
	connect(ui.skinBudBtn, SIGNAL(clicked()), this, SLOT(OnClickApplySkinBudSlot()));
	connect(ui.skinPurpleBtn, SIGNAL(clicked()), this, SLOT(OnClickApplySkinPurpleSlot()));
	//connect(ui.skinPurple, SIGNAL(clicked()), this, SLOT(OnClickApplySkinPurpleSlot()));
}

TNSkinSet::~TNSkinSet()
{
	_listSkinBtn.clear();
}

void TNSkinSet::InitUI()
{
	ResetCheck();
	//Æ¤·ô±êÌâ
	//ui.skinLabel->setText(("±±Å·À¶"));
	//ui.skinPink->setText(("ÐÄÌø»ØÒä"));
	//ui.label_2->setText(("°ÙÏãÜø"));
	//ui.skinGreen->setText(("·¼²ÝÂÌ"));
	_listSkinBtn.append(ui.skinBlueBtn);
	_listSkinBtn.append(ui.skinPinkBtn);
	_listSkinBtn.append(ui.skinGreenBtn);
	_listSkinBtn.append(ui.skinTeaBtn);
	_listSkinBtn.append(ui.skinOrangeBtn);
	_listSkinBtn.append(ui.skinPurpleBtn);
	_listSkinBtn.append(ui.skinBudBtn);
	_listSkinBtn.append(ui.skinOrchidBtn);
	SKIN_TYPE curType = TNSettingData::instance()->GetSkinType();
	_listSkinBtn[curType]->setChecked(true);

}


void TNSkinSet::OnClickApplySkinBlueSlot()
{
	OnClickApplySkin(SKIN_TYPE_DEFAULT);
	_listSkinBtn[SKIN_TYPE_DEFAULT]->setChecked(true);
}
void TNSkinSet::OnClickApplySkinPinkSlot()
{
	OnClickApplySkin(SKIN_TYPE_PINK);
	_listSkinBtn[SKIN_TYPE_PINK]->setChecked(true);
}

void TNSkinSet::OnClickApplySkinGreenSlot()
{
	OnClickApplySkin(SKIN_TYPE_GREEN);
	_listSkinBtn[SKIN_TYPE_GREEN]->setChecked(true);
}

void TNSkinSet::OnClickApplySkinTeaSlot()
{
	OnClickApplySkin(SKIN_TYPE_TEA);
	_listSkinBtn[SKIN_TYPE_TEA]->setChecked(true);
}

void TNSkinSet::OnClickApplySkinOrangeSlot()
{
	OnClickApplySkin(SKIN_TYPE_ORANGE);
	_listSkinBtn[SKIN_TYPE_ORANGE]->setChecked(true);
}

void TNSkinSet::OnClickApplySkinOrchidSlot()
{
	OnClickApplySkin(SKIN_TYPE_ORCHID);
	_listSkinBtn[SKIN_TYPE_ORCHID]->setChecked(true);
}

void TNSkinSet::OnClickApplySkinBudSlot()
{
	OnClickApplySkin(SKIN_TYPE_BUD);
	_listSkinBtn[SKIN_TYPE_BUD]->setChecked(true);
}

void TNSkinSet::OnClickApplySkinPurpleSlot()
{
	OnClickApplySkin(SKIN_TYPE_PURPLE);
	_listSkinBtn[SKIN_TYPE_PURPLE]->setChecked(true);
}

void TNSkinSet::OnClickApplySkin(int type)
{
	if (TNSettingData::instance()->GetSkinType() == type)
		return;
	ResetCheck();
	TNSettingData::instance()->ApplySkinType((SKIN_TYPE)type);
	QString value = QString::number(type);
	st_SetUpPtr skinSet = std::make_shared<st_SetUp>();
	skinSet->SetKey(STR_SKIN_KEY);
	skinSet->SetValue(value);
	TNDataControlServer::GetInstance()->InsertDatas(skinSet, DBTYPE_USER);
}

void TNSkinSet::ResetCheck()
{
	ui.skinBlueBtn->setChecked(false);
	ui.skinPinkBtn->setChecked(false);
	ui.skinGreenBtn->setChecked(false);
	ui.skinTeaBtn->setChecked(false);
	ui.skinOrangeBtn->setChecked(false);
	ui.skinBudBtn->setChecked(false);
	ui.skinOrchidBtn->setChecked(false);
	ui.skinPurpleBtn->setChecked(false);
}
