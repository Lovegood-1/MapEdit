#include  "SimpleButton.h"

CSimpleButton::CSimpleButton(QWidget* parent )
{

}

CSimpleButton::~CSimpleButton(){}

void CSimpleButton::setParam(std::string str, QColor full_color_, QColor font_anim_start_color_, QColor font_anim_finish_color_, int border_radius_, int timer_interval_)
{
	text = QString::fromStdString(str);
	full_color = full_color_;
	border_radius = border_radius_;
	timer_interval = timer_interval_;
	font_anim_finish_color = font_anim_finish_color_;
	font_anim_start_color = font_anim_start_color_;

	font_color = full_color.name();


	QString border_color = full_color.name();
	setObjectName("SimpleButton_1");
	setStyleSheet(QString("CSimpleButton#SimpleButton_1 {"
		"    border:1px solid %1;"
		"    background-color: rgba(0, 0, 0,0);"
		"    border-radius:%2px;"
		"}").arg(border_color).arg(border_radius));
}


void CSimpleButton::animationConfig() {
	radius = 0;
	radiusVar = 3;
	max_radius = sqrt(pow(width(), 2) + pow(height(), 2));

	if (timer != nullptr) {
		timer->stop();
		delete timer;
	}
	timer = new QTimer(this);
 	timer->setInterval(timer_interval);
	connect(timer, &QTimer::timeout, this, &CSimpleButton::incRadius);
 
}

void CSimpleButton::incRadius() {
	radius += radiusVar;
	if (radius > max_radius) {
		timer->stop();
		return;
	}
	update();
}



  