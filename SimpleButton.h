#ifndef SIMPLEBUTTON_H
#define SIMPLEBUTTON_H

#include <memory>

#include <QWidget>
#include <QtWidgets>
#include <QPushButton>



class CSimpleButton : public  QPushButton
{
 public:
	CSimpleButton(QWidget * parent = nullptr);
	~CSimpleButton();

	void setParam(std::string str,
		QColor full_color_,
		QColor font_anim_start_color_,
		QColor font_anim_finish_color_,
		int border_radius_,
		int timer_interval_);

	void CSimpleButton::animationConfig();
	void CSimpleButton::incRadius();
	void CSimpleButton::decRadius();
	void setText(const QString& text);
	void paintText();
	void paintEvent(QPaintEvent* event);
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);
	void showEvent(QShowEvent* event);
public:

	int radius;
	int radiusVar;
	double max_radius;
	int border_radius;
	int timer_interval;



	QString text;
	QColor full_color;
	QColor font_color;
	QColor font_anim_start_color;
	QColor font_anim_finish_color;

	//std::unique_ptr<QTimer> timer;

	QTimer* timer =   new QTimer(this);
	;
};

 


#endif   

 