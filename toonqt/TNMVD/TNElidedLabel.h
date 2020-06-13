#pragma once
#include <QLabel>

#include "TNMVD_global.h"

class TNMVD_EXPORT TNElidedLabel : public QLabel
{
	Q_OBJECT
public:
    enum ShowColorType{
        em_default = 0,
        em_at,
        em_draft
    };

	TNElidedLabel(QWidget* parent = 0, Qt::WindowFlags f = 0);
	TNElidedLabel(const QString& txt, QWidget* parent = 0, Qt::WindowFlags f = 0);
	TNElidedLabel(const QString& txt,
		Qt::TextElideMode elideMode = Qt::ElideRight,
		QWidget* parent = 0,
		Qt::WindowFlags f = 0
		);
	~TNElidedLabel();

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
    void cacheElidedText(int w,const QString& text);

private:
	Qt::TextElideMode _elideMode;
    QString 		  _orignalText;
	QString _cachedElidedText;
};

