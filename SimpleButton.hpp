/**
 * @brief     花式按键类
 * @details    
 * @mainpage 
 * @reference https://github.com/Rev-RoastedDuck/QT-material-widgets.git  
 * @reference https://www.bilibili.com/video/BV1jp4y1A7xT/?spm_id_from=333.788.recommend_more_video.5&vd_source=e07ba382c7723740f058bd78a2e85fe7
 * @date 2023-10-28
 */


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

		animationConfig(); // 将一些设置打包
	}

	CSimpleButton::~CSimpleButton() {}

	void CSimpleButton::animationConfig() {
		radius = 0;
		radiusVar = 3;
		max_radius = sqrt(pow(width(), 2) + pow(height(), 2));
		if (timer != nullptr) {
			timer->stop();
			timer->start();
		}
		timer->setInterval(timer_interval);

	}

	// 修改半径:增加
	void CSimpleButton::incRadius() {
		radius += radiusVar;
		if (radius > max_radius) {
			timer->stop();
		}
		update();
	}

	// 修改半径：减少
	void CSimpleButton::decRadius() {
		radius -= radiusVar;
		if (radius < 0) {
			timer->stop();
			font_color = font_anim_start_color;
		}
		update();
	}

	void CSimpleButton::setText(const QString& text) {
		this->text = text;
	}

	void CSimpleButton::paintText() {
		/* 绘制文字 */
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
		timer->disconnect();
		connect(timer, &QTimer::timeout, this, &CSimpleButton::decRadius);
		timer->start();
	}

	void CSimpleButton::showEvent(QShowEvent* event) {
		QPushButton::showEvent(event);
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

	QTimer* timer =   new QTimer(this);
};

 
 
 

#endif   

 