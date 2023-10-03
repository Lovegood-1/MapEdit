#ifndef MAPDISPLAY_H
#define MAPDISPLAY_H

#include "Macro.h"
#include "Graph.h"
#include "SystemData.h"

#include <QPainter>
#include <QWheelEvent>
#include <QMouseEvent>

// 动态 include
#ifdef USE_OPENGL
#include <QOpenGLWidget>
#else
#include <qwidget>
#endif

// 动态定义！！！
#ifdef USE_OPENGL
class CMapDisplay : public QOpenGLWidget
#else
class CMapDisplay : public Qwidget

#endif
{
public:
	CMapDisplay(QWidget* parent = nullptr);
	~CMapDisplay();


	// 所有窗口都有绘画、缩放功能，这里重写他们
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;



private:
	CGraph* m_pGraph;

	double m_dStartX;// ?your propose?
	double m_dStartY;

	bool m_bEditMode;
	bool m_bLBtnPressed;

	QPoint m_VClickPoint;
	QPoint m_VMovePoint;

};

#endif