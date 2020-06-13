#include "tnloadinghository.h"

tnLoadingHository::tnLoadingHository(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	_pMovie = new QMovie(":/Resources/toolWidget/loading_spinner.gif");
	_pMovie->setScaledSize(QSize(40,40));
	ui.label_loading_gif->setMovie(_pMovie);
	_pMovie->start();
}

tnLoadingHository::~tnLoadingHository()
{
	_pMovie->stop();
	delete _pMovie;
	_pMovie = NULL;
} 