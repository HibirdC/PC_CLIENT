#pragma once
#include <QLabel>

#include "TNMVD_global.h"

class TNMVD_EXPORT TNElidedLabelV2 : public QLabel
{
	Q_OBJECT
public:
	TNElidedLabelV2(QWidget* parent = 0, Qt::WindowFlags f = 0);
	TNElidedLabelV2(const QString& txt, QWidget* parent = 0, Qt::WindowFlags f = 0);
	TNElidedLabelV2(const QString& txt,
		Qt::TextElideMode elideMode = Qt::ElideRight,
		QWidget* parent = 0,
		Qt::WindowFlags f = 0
		);
	~TNElidedLabelV2();

	void setElideMode(Qt::TextElideMode elideMode) {
		_elideMode = elideMode;
		updateGeometry();
	}

	Qt::TextElideMode elideMode() const { return _elideMode; }
    void setText(const QString &);
    void setToolTip(const QString &);

protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
    void cacheElidedText(int w);

private:
	Qt::TextElideMode _elideMode;
    QString 		  _orignalText;
	QString _cachedElidedText;
};

