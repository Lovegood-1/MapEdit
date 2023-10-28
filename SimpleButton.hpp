#ifndef SIMPLEBUTTON_H
#define SIMPLEBUTTON_H

#include <memory>

#include <QWidget>
#include <QtWidgets>
#include <QPushButton>



class CSimpleButton : public  QPushButton
{
 public:

	 CSimpleButton::CSimpleButton()
	 {
		 text = "Hold That";
		 full_color = QColor("#00A97F");
		 border_radius = 5;
		 timer_interval = 8;
		 font_anim_finish_color = QColor("#ffffff");
		 font_anim_start_color = QColor("#00A97F");

		 font_color = full_color.name();
		 QString border_color = full_color.name();
		 setObjectName("SimpleButton");
		 setStyleSheet(QString("CSimpleButton#SimpleButton {"
			 "    border:1px solid %1;"
			 "    background-color: rgba(0, 0, 0,0);"
			 "    border-radius:%2px;"
			 "}").arg(border_color).arg(border_radius));
	 }

	 CSimpleButton::~CSimpleButton() {
 
	 }

 

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
			 timer->start();
		 }
		 //timer = new QTimer(this);
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


	 void CSimpleButton::decRadius() {
		 radius -= radiusVar;
		 if (radius < 0) {
			 timer->stop();
			 return;
		 }
		 update();
	 }

	 void CSimpleButton::setText(const QString& text) {
		 this->text = text;
	 }

 
	 void CSimpleButton::paintText() {
		 /* »æÖÆÎÄ×Ö */
		 QPainterPath path;
		 path.addRoundedRect(0, 0, width(), height(), border_radius, border_radius);

		 QPainter painter(this);
		 painter.setPen(Qt::NoPen);
		 painter.setClipPath(path);
		 painter.setFont(font());
		 painter.setPen(QColor(font_color));
		 painter.setRenderHint(QPainter::Antialiasing);

		 if (!text.isEmpty()) {
			 painter.drawText(rect(), Qt::AlignCenter, text);
		 }
	 }

	 void CSimpleButton::paintEvent(QPaintEvent* event) {
		 QPushButton::paintEvent(event);

		 QPainter painter(this);
		 painter.setRenderHint(QPainter::Antialiasing);

		 QBrush brush(full_color);
		 painter.setBrush(brush);
		 painter.setPen(Qt::NoPen);

		 QPainterPath path;
		 path.addRoundedRect(rect(), border_radius, border_radius);
		 painter.setClipPath(path);

		 painter.drawEllipse(QPoint(0, 0), radius, radius);
		 painter.drawEllipse(QPoint(width(), height()), radius, radius);

		 paintText();
	 }

	 void CSimpleButton::enterEvent(QEvent* event) {
		 font_color = font_anim_finish_color;
		 timer->disconnect();
		 connect(timer, &QTimer::timeout, this, &CSimpleButton::incRadius);
		 timer->start();
	 }

	 void CSimpleButton::leaveEvent(QEvent* event) {
		 font_color = font_anim_finish_color;
		 timer->disconnect();
		 connect(timer, &QTimer::timeout, this, &CSimpleButton::decRadius);
		 timer->start();
	 }

	 void CSimpleButton::showEvent(QShowEvent* event) {
		 QPushButton::showEvent(event);
		 animationConfig();
	 }







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

 